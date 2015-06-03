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

#include <vector>
#include <cstdint>
#include <LumsInclude/Graphics/ShaderProgram.hpp>
#include <LumsInclude/Graphics/Image.hpp>
#include <LumsInclude/Graphics/Texture.hpp>
#include <LumsInclude/Graphics/Font.hpp>
#include <LumsInclude/Singleton.hpp>

namespace lm
{
    /**
     * @cond
     */
    namespace internal
    {
        template <typename T>
        class ProviderImpl
        {
        public:
            T&
            get(int i)
            {
                return *_buffer[i];
            }

            T&
            set(int i)
            {
                if (i >= _buffer.size())
                    _buffer.resize(i + 1);
                if (_buffer[i] == nullptr)
                    _buffer[i] = new T();
                return *_buffer[i];
            }

            std::size_t
            size() const
            {
                return _buffer.size();
            }

        protected:
            std::vector<T*> _buffer;
        };
    }
    /**
     * @endcond
     */

    /**
     * @brief A provider for assets that are loaded once
     *
     * This is a template used to create custom providers for assets.
     */
    template <typename T>
    class Provider : public internal::ProviderImpl<T>, public Singleton<Provider<T>>
    {

    };

    /**
     * @brief A provider for assets that are loaded and unloaded at runtime
     *
     * This is a template used to create custom providers for dynamic assets.
     * Assets should implement load(), unload() and loaded().
     */
    template <typename T>
    class StreamProvider : public internal::ProviderImpl<T>, public Singleton<StreamProvider<T>>
    {
    public:
        T&
        get(int i)
        {
            if (!internal::ProviderImpl<T>::_buffer[i]->loaded())
                return load(i);
            return internal::ProviderImpl<T>::get(i);
        }

        T&
        load(int i)
        {
            internal::ProviderImpl<T>::_buffer[i]->load();
            return internal::ProviderImpl<T>::get(i);
        }

        T&
        unload(int i)
        {
            internal::ProviderImpl<T>::_buffer[i]->unload();
            return internal::ProviderImpl<T>::get(i);
        }

        void
        reload(int i)
        {
            unload(i);
            load(i);
        }

        void
        reloadAll()
        {
            for (std::size_t i = 0; i < internal::ProviderImpl<T>::size(); ++i)
            {
                if (internal::ProviderImpl<T>::_buffer[i]->loaded())
                    reload(i);
            }
        }

        void
        unloadAll()
        {
            for (std::size_t i = 0; i < internal::ProviderImpl<T>::size(); ++i)
                unload(i);
        }

    };

    using ShaderProvider = Provider<ShaderProgram>;
    using ImageProvider = StreamProvider<Image>;
    using TextureProvider = StreamProvider<Texture>;
    using FontProvider = StreamProvider<Font>;
    using SfxProvider = StreamProvider<Sfx>;
    using MusicProvider = StreamProvider<Music>;
}

#endif
