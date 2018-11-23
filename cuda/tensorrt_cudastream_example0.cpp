#include "cuda_runtime.h"  
#include "cuda/include/cuda_runtime_api.h"
#include "tensorrt/include/NvInfer.h"
#include "tensorrt/include/NvUffParser.h"
#include "cuda_runtime.h"  

// CUDA: various checks for different function calls.
#define CUDA_CHECK(condition) \
  /* Code block avoids redefinition of cudaError_t error */ \
  do { \
    cudaError_t error = condition; \
    CHECK_EQ(error, cudaSuccess) << " " << cudaGetErrorString(error); \
  } while (0)
#define MAX_WORKSPACE (1 << 30)

int main(){
  int m_gpu = 0; // GPU id
  int m_mebs = 512; // most efficient batch size
  bool m_half_precision = true; // whether use half_precision or single
  std::vector<void*> m_cuda_buf_dev; // device momery
  std::vector<float*> m_cuda_buf_host; // page-locked host memory

  cudaStream_t stream[2];
  nvinfer1::IBuilder* builder;
  nvinfer1::INetworkDefinition* network;
  nvuffparser::IUffParser* parser;
  nvinfer1::ICudaEngine *m_engine;
  nvinfer1::IExecutionContext *m_context;

  // set device
  cudaSetDevice(m_gpu);
  // cuda stream
  CUDA_CHECK(cudaStreamCreate(&stream[0]));
  CUDA_CHECK(cudaStreamCreate(&stream[1]));
  // uff parser
  parser = nvuffparser::createUffParser();
  // register Inputs and Outputs
  parser->registerInput("pos_tensor", nvinfer1::DimsCHW(GoFeature::SIZE_HISTORYEACHSIDE+1, GoComm::BORDER_SIZE, GoComm::BORDER_SIZE), nvuffparser::UffInputOrder::kNCHW);
  parser->registerOutput("policy_output");
  parser->registerOutput("value_output");
  builder = nvinfer1::createInferBuilder(g_logger);
  network = builder->createNetwork();
  if (m_half_precision){
    if (!parser->parse(uff_path.string().c_str(), *network, nvinfer1::DataType::kHALF)){
      PLOG(ERROR) << "fail to parse";
      return -1;
    }
    builder->setFp16Mode(true);
  } else {
    if (!parser->parse(uff_path.string().c_str(), *network, nvinfer1::DataType::kFLOAT)){
      PLOG(ERROR) << "fail to parse";
      return -1;
    }
  }
  builder->setMaxBatchSize(m_mebs);
  builder->setMaxWorkspaceSize(MAX_WORKSPACE);
  m_engine = builder->buildCudaEngine(*network);
  if (m_engine == nullptr) {
      PLOG(ERROR) << "load cuda engine error";
      return -2;
  }
  m_context = m_engine->createExecutionContext();
  cout << "Model Loaded" << endl;

  /// allocate and bind
  for (int i = 0; i < m_engine->getNbBindings(); ++i) { // number of binding tensors
      auto dim = m_engine->getBindingDimensions(i);
      std::string dim_str = "(";
      int size = 1;
      for (int i = 0; i < dim.nbDims; ++i) {
          if (i) dim_str += ", ";
          dim_str += std::to_string(dim.d[i]);
          size *= dim.d[i];
      }
      dim_str += ")";
      LOG(INFO) << "tensorrt binding: " << m_engine->getBindingName(i) << " " << dim_str;

      void *dev_buf;
      CUDA_CHECK(cudaMalloc(&dev_buf, max_batch_size * size * sizeof(float)));
      m_cuda_buf_dev.push_back(dev_buf);
      float *host_buf;
      CUDA_CHECK(cudaHostAlloc(&host_buf, max_batch_size * size * sizeof(float), cudaHostAllocDefault));
      m_cuda_buf_host.push_back(host_buf);
  }

  // write pinned host memory
  for (int i = 0; i < batch_size; ++i) {
      for (int j = 0; j < INPUT_DIM; ++j) {
          m_cuda_buf_host[0][i * INPUT_DIM + j] = inputs[i][j];
      }
  }

  void* bindings[3];
  int batch_size_kernel;
  bindings[0] = m_cuda_buf_dev[0];
  bindings[1] = m_cuda_buf_dev[1];
  bindings[2] = m_cuda_buf_dev[2];
  for (int i = 0; i < batch_size; i += m_mebs){
      batch_size_kernel = batch_size - i < m_mebs ? batch_size - i : m_mebs;
      if (i % (m_mebs*2) < m_mebs){
          CUDA_CHECK(cudaMemcpyAsync(m_cuda_buf_dev[0] +i*INPUT_DIM*sizeof(float), m_cuda_buf_host[0] +i*INPUT_DIM, batch_size_kernel*INPUT_DIM*sizeof(float), cudaMemcpyHostToDevice, stream[0]));
          m_context->enqueue(batch_size_kernel, bindings, stream[0], nullptr);
          CUDA_CHECK(cudaMemcpyAsync(m_cuda_buf_host[1] +i*OUTPUT_DIM, m_cuda_buf_dev[1] +i*OUTPUT_DIM*sizeof(float), batch_size_kernel*OUTPUT_DIM*sizeof(float), cudaMemcpyDeviceToHost, stream[0]));
          CUDA_CHECK(cudaMemcpyAsync(m_cuda_buf_host[2] +i, m_cuda_buf_dev[2] +i*sizeof(float), batch_size_kernel*sizeof(float), cudaMemcpyDeviceToHost, stream[0]));
      } else {
          CUDA_CHECK(cudaMemcpyAsync(m_cuda_buf_dev[0] +i*INPUT_DIM*sizeof(float), m_cuda_buf_host[0] +i*INPUT_DIM, batch_size_kernel*INPUT_DIM*sizeof(float), cudaMemcpyHostToDevice, stream[1]));
          m_context->enqueue(batch_size_kernel, bindings, stream[1], nullptr);
          CUDA_CHECK(cudaMemcpyAsync(m_cuda_buf_host[1] +i*OUTPUT_DIM, m_cuda_buf_dev[1] +i*OUTPUT_DIM*sizeof(float), batch_size_kernel*OUTPUT_DIM*sizeof(float), cudaMemcpyDeviceToHost, stream[1]));
          CUDA_CHECK(cudaMemcpyAsync(m_cuda_buf_host[2] +i, m_cuda_buf_dev[2] +i*sizeof(float), batch_size_kernel*sizeof(float), cudaMemcpyDeviceToHost, stream[1]));
      }
      bindings[0] += batch_size_kernel * INPUT_DIM * sizeof(float);
      bindings[1] += batch_size_kernel * OUTPUT_DIM * sizeof(float);
      bindings[2] += batch_size_kernel * sizeof(float);
  }
  CUDA_CHECK(cudaStreamSynchronize(stream[0]));
  CUDA_CHECK(cudaStreamSynchronize(stream[1]));

  // destroy
  network->destroy();
  builder->destroy();
  parser->destroy();
  m_context->destroy();
  m_engine->destroy();
  for (auto buf: m_cuda_buf_dev) {
      CUDA_CHECK(cudaFree(buf));
  }
  for (auto buf: m_cuda_buf_host) {
      CUDA_CHECK(cudaFreeHost(buf));
  }
  CUDA_CHECK(cudaStreamDestroy(stream[0]));
  CUDA_CHECK(cudaStreamDestroy(stream[1]));
  cout << "Model deleted" << endl;
  return 0;
}
