/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    PoolAllocator.hpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_POOL_ALLOCATOR_HPP
#define LUMS_POOL_ALLOCATOR_HPP

#include <cstdlib>
#include <cstdint>

namespace lm
{
    namespace internal
    {
        template <typename T>
        struct AllocPool
        {
            enum { count = 32768 };
            enum { size = sizeof(T) * count };

            AllocPool() : lastBit(0), freeSpace(count), next(nullptr) {}

            T*
            alloc()
            {
                size_t i;

                if (!freeSpace)
                    return nullptr;

                for (i = lastBit; i < count; ++i)
                {
                    if (bitmap[i] == false)
                        goto found;
                }
                for (i = 0; i < lastBit; ++i)
                {
                    if (bitmap[i] == false)
                        goto found;
                }
                return nullptr;
                
                found:
                bitmap[i] = true;
                lastBit = i + 1;
                freeSpace--;
                return reinterpret_cast<T*>(data + (sizeof(T) * i));
            }

            bool
            dealloc(T* ptr)
            {
                char* cptr = (char*)ptr;
                if (cptr < data || cptr >= data + size)
                    return false;
                std::ptrdiff_t diff = cptr - data;
                size_t slot = diff / sizeof(T);
                assert("Should not dealloc a non-allocated block" && bitmap[slot]);
                bitmap[slot] = false;
                lastBit = slot;
                freeSpace++;
                return true;
            }

            char                        data[size];
            std::bitset<count>          bitmap;
            size_t                      lastBit;
            size_t                      freeSpace;
            AllocPool<T>*               next;
        };

        template <typename T>
        struct PoolAllocatorData
        {
            PoolAllocatorData()
            {
                pool = (AllocPool<T>*)(malloc(sizeof(AllocPool<T>)));
                ::new (pool) AllocPool<T>;
                lastPool = pool;
            }

            T*
            alloc()
            {
                T* ptr = lastPool->alloc();
                if (ptr)
                    return ptr;
                AllocPool<T>* p = pool;
                for (;;)
                {
                    if (p != lastPool)
                    {
                        ptr = p->alloc();
                        if (ptr)
                        {
                            lastPool = p;
                            return ptr;
                        }
                    }
                    if (p->next)
                        p = p->next;
                    else
                    {
                        AllocPool<T>* np = ((AllocPool<T>*)(malloc(sizeof (AllocPool<T>))));
                        ::new (np) AllocPool<T>;
                        p->next = np;
                        lastPool = np;
                        return np->alloc();
                    }
                }
            }

            void
            dealloc(T* ptr)
            {
                AllocPool<T>* p = pool;
                for (;;)
                {
                    if (p->dealloc(ptr))
                    {
                        lastPool = p;
                        return;
                    }
                    assert("Should not dealloc outside the pool" && p->next);
                    p = p->next;
                }
            }

            AllocPool<T>*   pool;
            AllocPool<T>*   lastPool;
        };
    }

    template <typename T>
    struct PoolAllocator
    {
        T*          address(T& x) const noexcept { return &x; }
        const T*    address(const T& x) const noexcept { return &x; }
        T*          allocate(size_t n, void* hint = 0) { return allocator.alloc(); }
        void        deallocate(T* p, size_t n) { allocator.dealloc(p); }
        size_t      max_size() const noexcept { return 1; }

        template <typename U, typename... Args>
        void
        construct(U* p, Args&&... args)
        {
            ::new ((void*)p) U(std::forward<Args>(args)...);
        }

        template <typename U>
        void
        destroy(U* p)
        {
            p->~U();
        }

        static internal::PoolAllocatorData<T> allocator;
    };

    template <typename T>
    internal::PoolAllocatorData<T> PoolAllocator<T>::allocator;
}

#endif
