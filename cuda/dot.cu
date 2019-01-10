#include <cuda_runtime.h>
#include <iostream>

using std::cin;
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

#define LEN 8192
#define BLOCKDIM 256
#define GRIDDIM 8

// kernel function
__global__ void dot_kernel(int N, int *a, int *b, int *c ) { 
    __shared__ int cache[BLOCKDIM]; // 512 >= thread_id in block
    int tid = threadIdx.x + blockIdx.x * blockDim.x; // thread_id in grid
    int cacheIndex = threadIdx.x; // thread_id in block
    // thread_num in grid

    int temp = 0;
    while (tid < N) {
        temp += a[tid] * b[tid];
        tid += blockDim.x * gridDim.x;
    }

    cache[cacheIndex] = temp;//if blockDim == 1, then result = the sum of cache[].

    //同步
    __syncthreads();//make sure that all the threads in a block finish the procedure above

    //规约求和
    int i = blockDim.x/2;
    while (i != 0) {
        if (cacheIndex < i) {
            cache[cacheIndex] += cache[cacheIndex + i];
        }

        __syncthreads();
        i /= 2;
    }

    if (cacheIndex == 0) {
        c[blockIdx.x] = cache[0];
    }
}

int main() {
    // host memory malloc & initial
    int* host_a = new int[LEN];
    int* host_b = new int[LEN];
    int* host_c = new int[GRIDDIM];
    for (int i = 0; i < LEN; ++i) {
        host_a[i] = 1;
        host_b[i] = i;
    }
    for (int i = 0; i < GRIDDIM; ++i) {
        host_c[i] = 0;
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
    CUDA_CHECK(cudaMalloc((void**)&dev_c, GRIDDIM * sizeof(int)));
    CUDA_CHECK(cudaMemcpy(dev_a, host_a, LEN * sizeof(int), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(dev_b, host_b, LEN * sizeof(int), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemset(dev_c, 0, GRIDDIM * sizeof(int)));

    // add_kernel & result copy & print
    dim3 grid_dim(GRIDDIM, 1, 1);   // gridDim.x,  gridDim.y,  gridDim.z
    dim3 block_dim(BLOCKDIM, 1, 1); // blockDim.x, blockDim.y, blockDim.z
    const int blocksPerGrid = grid_dim.x * grid_dim.y * grid_dim.z;
    dot_kernel<<<grid_dim, block_dim>>>(LEN, dev_a, dev_b, dev_c);
    CUDA_CHECK(cudaMemcpy(host_c, dev_c, GRIDDIM * sizeof(int), cudaMemcpyDeviceToHost));
    int c = 0;
    for (int i = 0; i < blocksPerGrid; ++i) {
        cout << "host_c[" << i << "]: " << host_c[i] << endl;
        c += host_c[i];
    }
    cout << "dot_kernel results: " << c << endl;        

    // Free gpu memory & free cpu memory
    CUDA_CHECK(cudaFree(dev_a));
    CUDA_CHECK(cudaFree(dev_b));
    CUDA_CHECK(cudaFree(dev_c));
    delete[] host_a;
    delete[] host_b;
    delete[] host_c;
    return 0;
}
