#pragma once

#include "device_launch_parameters.h"
#include "cuda_runtime.h"

#include <cuda_runtime_api.h>
#include <cuda.h>

#include <cstdint>

#include <memory>

namespace fatpound::cuda
{
    class CudaPtr final
    {
    public:
        template <typename T>
        static std::unique_ptr<T, CudaPtr> make_unique_cuda(std::size_t count)
        {
            T* ptr = nullptr;

            cudaMalloc(&ptr, sizeof(T) * count);

            return std::unique_ptr<T, CudaPtr>(ptr);
        }

        template <typename T>
        void operator () (T* ptr) const
        {
            cudaFree(ptr);
            ptr = nullptr;
        }


    protected:


    private:
    };

    template <typename T>
    using UniqueCudaPtr = std::unique_ptr<T, CudaPtr>;
}
