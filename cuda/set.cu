#include <cuda_runtime.h>
#include <iostream>

using std::cout;
using std::endl;

#define CUDA_CHECK(x) \
    { cudaError_t cuda_error = x; \
        if (cuda_error != cudaSuccess) \
            cout << "cudaError_t: " << cuda_error << " != 0 " \
                 << cudaGetErrorString(cuda_error) << endl; \
    }

#define VECTOR_PRINT(head_str, vec, len) \
    cout << head_str << ": {"; \
    for (int i = 0; i < len - 1; ++i){ \
        cout << vec[i] << ", "; \
    } \
    cout << vec[len - 1] << "}" << endl;

#define LEN 32

// kernel functions
template<typename Dtype>
__global__ void set_kernel(const int N, Dtype* c){
    int bid = blockIdx.y * gridDim.x + blockIdx.x;
    int tid = threadIdx.z + threadIdx.y * blockDim.z + threadIdx.x * blockDim.z * blockDim.y + bid * blockDim.x * blockDim.y * blockDim.z;
    c[tid] = blockIdx.x * 10000
         + blockIdx.y * 1000
         + threadIdx.x * 100
         + threadIdx.y * 10
         + threadIdx.z * 1;
}

int main(){
    // host memory malloc & initial
    int* host_a = new int[LEN];
    for (int i = 0; i < LEN; ++i){
        host_a[i] = 0;
    }
    
    // GPU device start
    int device_id = 1;
    CUDA_CHECK(cudaSetDevice(device_id));
    cout << "Using GPU " << device_id << "." << endl;
    
    // cudaMalloc & cudaMemcpy & cudaMemset
    int* dev_a;
    CUDA_CHECK(cudaMalloc((void**)&dev_a, LEN * sizeof(int)));
    CUDA_CHECK(cudaMemcpy(dev_a, host_a, LEN * sizeof(int), cudaMemcpyHostToDevice));

    // set_kernel & result copy & print
    dim3 grid_dim(2, 2, 1);   // gridDim.x,  gridDim.y,  gridDim.z (always 1)
    dim3 block_dim(2, 2, 2); // blockDim.x, blockDim.y, blockDim.z
    set_kernel<int><<<grid_dim, block_dim>>>(LEN, dev_a);
    CUDA_CHECK(cudaMemcpy(host_a, dev_a, LEN * sizeof(int), cudaMemcpyDeviceToHost));
    VECTOR_PRINT("set_kernel results", host_a, LEN);

    // Free gpu memory & free cpu memory
    CUDA_CHECK(cudaFree(dev_a));
    delete[] host_a;
    return 0;
}
