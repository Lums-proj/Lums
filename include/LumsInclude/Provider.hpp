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
#if 0

#ifndef PROVIDER_HPP
#define PROVIDER_HPP

#include <bitset>
#include <cstdint>
#include <LumsInclude/Graphics/ShaderProgram.hpp>
#include <LumsInclude/Singleton.hpp>

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
            return *(new(_buffer + i * sizeof(T)) T);
        }

    protected:
        unsigned char   _buffer[N * sizeof(T)];
    };

    template <std::size_t N, typename T>
    class StreamProvider : public Provider<N, ShaderProgram>
    {
    public:
        T&
        get(int i)
        {
            if (!_allocTable[i])
                return load(i);
            return Provider::get(i);
        }

        T&
        load(int i)
        {
            _allocTable[i] = 1;
            return Provider::set(i);
        }

    private:
        std::bitset<N>  _allocTable;
    };

    template<std::size_t N>
    class ImageProvider : public StreamProvider<N, Image>, public Singleton<Image<N>>
    {
    public:
        Image&
        set(int i, const& std::string path)
        {

        }

        Image&
        load(int i)
        {
            Image& img = StreamProvider::load(i);

        }

    private:
        struct data
        {
            std::string     path;
            
        };
    };

    template <std::size_t N>
    class ShaderProvider : public Provider<N, ShaderProgram>, public Singleton<ShaderProvider<N>>
    {

    };

}

#endif

#endif