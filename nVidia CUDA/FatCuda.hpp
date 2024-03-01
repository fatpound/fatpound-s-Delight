#pragma once

#if (defined(__DEVICE_LAUNCH_PARAMETERS_H__) || \
     defined(__CUDA_RUNTIME_API_H__)         || \
     defined(__CUDA_RUNTIME_H__)             || \
     defined(__cuda_cuda_h__))

#ifndef __DEVICE_LAUNCH_PARAMETERS_H__
#include "device_launch_parameters.h"
#endif // ! __DEVICE_LAUNCH_PARAMETERS_H__

#ifndef __CUDA_RUNTIME_API_H__
#include <cuda_runtime_api.h>
#endif // ! __CUDA_RUNTIME_API_H__

#ifndef __CUDA_RUNTIME_H__
#include "cuda_runtime.h"
#endif // ! __CUDA_RUNTIME_H__

#ifndef __cuda_cuda_h__
#include <cuda.h>
#endif // ! __cuda_cuda_h__


#ifndef _MEMORY_
#include <memory>
#endif // ! _MEMORY_

namespace fatpound::cuda
{
    class FatCuda
    {
    public:
        template <typename T>
        static std::unique_ptr<T, FatCuda> make_unique_cuda(size_t count)
        {
            T* ptr = nullptr;

            cudaMalloc(&ptr, sizeof(T) * count);

            return std::unique_ptr<T, FatCuda>(ptr);
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
    using CudaPtr = std::unique_ptr<T, FatCuda>;
}
#endif // defined(__DEVICE_LAUNCH_PARAMETERS_H__) || defined(__CUDA_RUNTIME_API_H__) || defined(__CUDA_RUNTIME_H__) || define (__cuda_cuda_h__)
