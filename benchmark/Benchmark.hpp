/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Benchmark.hpp                                  oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <functional>
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <Lums>

namespace Benchmark
{
    void    poolAlloc();
}

inline void
timeReport(const char* name, void (*func)())
{
    auto t0 = std::chrono::high_resolution_clock::now();
    func();
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> d = t1 - t0;
    //auto dd = std::chrono::duration_cast<std::chrono::milliseconds>(d);
    printf("%s, took %lf ms\n", name, d.count() * 1000);
}

#endif
