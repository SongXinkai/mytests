#include <cuda_runtime.h>
#include <thrust/sort.h>
#include <thrust/device_ptr.h>
#include <iostream>
#include <algorithm>

using thrust::sort;
using thrust::device_ptr;
using std::cout;
using std::endl;

#define CUDA_CHECK(x) \
    { cudaError_t cuda_error = x; \
        if (cuda_error != cudaSuccess) \
            cout << "cudaError_t: " << cuda_error << " != 0 " \
                 << cudaGetErrorString(cuda_error) << endl; \
    }

#define VECTOR_PRINT(head_str, vec, LEN) \
    cout << head_str << ": {"; \
    for (int i = 0; i < LEN - 1; ++i){ \
        cout << vec[i] << ", "; \
    } \
    cout << vec[LEN - 1] << "}" << endl;

#define LEN 32

int main(){
    // host memory malloc & initial
    float* host_a = new float[LEN];
    for (int i = 0; i < LEN; ++i){
        host_a[i] = LEN - i;
    }
    
    // GPU device start
    int device_id = 1;
    CUDA_CHECK(cudaSetDevice(device_id));
    cout << "Using GPU " << device_id << "." << endl;
    
    // cudaMalloc & cudaMemcpy & cudaMemset
    float* dev_a;
    CUDA_CHECK(cudaMalloc((void**)&dev_a, LEN * sizeof(float)));
    CUDA_CHECK(cudaMemcpy(dev_a, host_a,  LEN * sizeof(float), cudaMemcpyHostToDevice));

    // thrust reduction max
    device_ptr<float> dp(dev_a);
    thrust::plus<float> add_op;
    cout << "sum: " << thrust::reduce(dp, dp + LEN, float(100), add_op) << endl;

    // Free gpu memory & free cpu memory
    CUDA_CHECK(cudaFree(dev_a));
    delete[] host_a;
    return 0;
}
