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
    float* host_b = new float[LEN];
    for (int i = 0; i < LEN; ++i){
        host_a[i] = LEN - i;
        host_b[i] = LEN - i;
    }
    
    // GPU device start
    int device_id = 1;
    CUDA_CHECK(cudaSetDevice(device_id));
    cout << "Using GPU " << device_id << "." << endl;
    
    // cudaMalloc & cudaMemcpy & cudaMemset
    float* dev_a;
    CUDA_CHECK(cudaMalloc((void**)&dev_a, LEN * sizeof(float)));
    CUDA_CHECK(cudaMemcpy(dev_a, host_a,  LEN * sizeof(float), cudaMemcpyHostToDevice));

    // thrust device sort
    device_ptr<float> dp(dev_a);
    sort(dp, dp + LEN);
    CUDA_CHECK(cudaMemcpy(host_a, dev_a, LEN * sizeof(float), cudaMemcpyDeviceToHost));
    VECTOR_PRINT("thrust sort", host_a, LEN);

    // std::sort
    for (int i = 0; i < LEN; ++i){
        host_b[i] = float(LEN) - float(i);
    }
    std::sort(host_b, host_b+ LEN);
    VECTOR_PRINT("std sort", host_b, LEN);

    // Free gpu memory & free cpu memory
    CUDA_CHECK(cudaFree(dev_a));
    delete[] host_a;
    delete[] host_b;
    return 0;
}
