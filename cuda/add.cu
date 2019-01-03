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

#define LEN 34

// kernel functions
template<typename Dtype>
__global__ void add_kernel(const int N, const Dtype* a, const Dtype* b, Dtype* c){
    int i = threadIdx.x; // thread index in block
    // c[i] = a[i] + b[i];
    
    for (int i = threadIdx.x; i < N; i += gridDim.x * blockDim.x){
        c[i] = a[i] + b[i];
    }
}

int main(){
    // host memory malloc & initial
    int* host_a = new int[LEN];
    int* host_b = new int[LEN];
    int* host_c = new int[LEN];
    for (int i = 0; i < LEN; ++i){
        host_a[i] = i;
        host_b[i] = i * 100;
        host_c[i] = -1;
    }
    
    // GPU device start
    int device_id = 1;
    CUDA_CHECK(cudaSetDevice(device_id));
    cout << "Using GPU " << device_id << "." << endl;
    
    // cudaMalloc & cudaMemcpy & cudaMemset
    int* dev_a;
    int* dev_b;
    int* dev_c;
    CUDA_CHECK(cudaMalloc((void**)&dev_a, LEN * sizeof(int)));
    CUDA_CHECK(cudaMalloc((void**)&dev_b, LEN * sizeof(int)));
    CUDA_CHECK(cudaMalloc((void**)&dev_c, LEN * sizeof(int)));
    CUDA_CHECK(cudaMemcpy(dev_a, host_a, LEN * sizeof(int), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(dev_b, host_b, LEN * sizeof(int), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemset(dev_c, 0, LEN * sizeof(int))); // Set value by byte

    // add_kernel & result copy & print
    dim3 grid_dim(1, 1, 1);   // gridDim.x,  gridDim.y,  gridDim.z (always 1)
    dim3 block_dim(16, 1, 1); // blockDim.x, blockDim.y, blockDim.z
    add_kernel<int><<<grid_dim, block_dim>>>(LEN, dev_a, dev_b, dev_c);
    //add_kernel<<<1, 16>>>(LEN, dev_a, dev_b, dev_c); // Set gridDim.x & blockDim.x
    CUDA_CHECK(cudaMemcpy(host_c, dev_c, LEN * sizeof(int), cudaMemcpyDeviceToHost));
    VECTOR_PRINT("add_kernel results", host_c, LEN);

    // Free gpu memory & free cpu memory
    CUDA_CHECK(cudaFree(dev_a));
    CUDA_CHECK(cudaFree(dev_b));
    CUDA_CHECK(cudaFree(dev_c));
    delete[] host_a;
    delete[] host_b;
    delete[] host_c;
    return 0;
}
