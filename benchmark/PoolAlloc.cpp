/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    PoolAlloc.cpp                                  oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include "Benchmark.hpp"

template <int S>
struct dummy
{
    char d[S];
};

template <template <typename> class T, int Count, int Size>
void
checkAlloc()
{
    dummy<Size>* v[Count];
    T<dummy<Size>> alloc;

    for (int i = 0; i < Count; ++i)
        v[i] = alloc.allocate(1);
    for (int i = 0; i < Count; ++i)
        alloc.deallocate(v[i], 1);
}

void
Benchmark::poolAlloc()
{
    char bar[80];
    bar[79] = 0;
    for (int i = 0; i < 79; ++i)
        bar[i] = '*';
    puts(bar);
    timeReport("std::allocator alloc then dealloc (10k, 100B)", checkAlloc<std::allocator, 10000, 100>);
    timeReport("std::allocator alloc then dealloc (50k, 100B)", checkAlloc<std::allocator, 50000, 100>);
    timeReport("std::allocator alloc then dealloc (200k, 100B)", checkAlloc<std::allocator, 200000, 100>);
    timeReport("std::allocator alloc then dealloc (1M, 100B)", checkAlloc<std::allocator, 100000, 100>);
    timeReport("std::allocator alloc then dealloc (10k, 10k)", checkAlloc<std::allocator, 10000, 10000>);
    timeReport("std::allocator alloc then dealloc (50k, 10k)", checkAlloc<std::allocator, 50000, 10000>);
    timeReport("std::allocator alloc then dealloc (200k, 10k)", checkAlloc<std::allocator, 200000, 10000>);
    timeReport("std::allocator alloc then dealloc (1M, 10k)", checkAlloc<std::allocator, 1000000, 10000>);
    puts(bar);
    timeReport("lm::PoolAllocator alloc then dealloc (10k, 100B)", checkAlloc<lm::PoolAllocator, 10000, 100>);
    timeReport("lm::PoolAllocator alloc then dealloc (50k, 100B)", checkAlloc<lm::PoolAllocator, 50000, 100>);
    timeReport("lm::PoolAllocator alloc then dealloc (200k, 100B)", checkAlloc<lm::PoolAllocator, 200000, 100>);
    timeReport("lm::PoolAllocator alloc then dealloc (1M, 100B)", checkAlloc<lm::PoolAllocator, 100000, 100>);
    timeReport("lm::PoolAllocator alloc then dealloc (10k, 10k)", checkAlloc<lm::PoolAllocator, 10000, 10000>);
    timeReport("lm::PoolAllocator alloc then dealloc (50k, 10k)", checkAlloc<lm::PoolAllocator, 50000, 10000>);
    timeReport("lm::PoolAllocator alloc then dealloc (200k, 10k)", checkAlloc<lm::PoolAllocator, 200000, 10000>);
    timeReport("lm::PoolAllocator alloc then dealloc (1M, 10k)", checkAlloc<lm::PoolAllocator, 1000000, 10000>);
    puts(bar);
}
