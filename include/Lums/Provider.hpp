/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Provider.hpp                                   oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROVIDER_HPP
#define PROVIDER_HPP

#include <iostream>
#include <cstdint>
#include <Lums/ShaderProgram.hpp>
#include <Lums/Singleton.hpp>

namespace lm
{

    template <std::size_t N, typename T>
    class Provider
    {
    public:
        T&
        get(int i)
        {
            return *(reinterpret_cast<T*>(_buffer + i * sizeof(T)));
        }

        T&
        set(int i)
        {
            std::cout << "toto " << (void*)(_buffer + i * sizeof(T)) << std::endl;
            return *(new(_buffer + i * sizeof(T)) T);
        }

    protected:
        unsigned char   _buffer[N * sizeof(T)];
    };

    template <std::size_t N>
    class ShaderProvider : public Provider<N, ShaderProgram>, public Singleton<ShaderProvider<N>>
    {

    };

}

#endif