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
     * @brief A basic abstract class for providers
     */
    template <typename T>
    class BaseProvider
    {
    public:
        /**
         * Get a resource by ID
         * @param i The resource identifier
         * @return A reference to the resource
         */
        T&
        get(int i)
        {
            return *buffer[i];
        }

        /**
         * Allocate and return a resource using it's ID
         * @param i The resource identifier
         * @return A reference to the resource
         */
        T&
        set(int i)
        {
            if (i >= buffer.size())
                buffer.resize(i + 1);
            if (buffer[i] == nullptr)
                buffer[i] = new T();
            return *buffer[i];
        }

        /**
         * Get the resource count
         * @return The number of resources loaded into the allocator
         */
        std::size_t
        size() const
        {
            return buffer.size();
        }

    protected:
        /**
         * The resource container
         */
        std::vector<T*> buffer;
    };

    /**
     * @brief A provider for assets that are loaded once
     *
     * This is a template used to create custom providers for assets.
     */
    template <typename T>
    class Provider : public BaseProvider<T>, public Singleton<Provider<T>>
    {

    };

    /**
     * @brief A provider for assets that are loaded and unloaded at runtime
     *
     * This is a template used to create custom providers for dynamic assets.
     * Assets should implement load(), unload() and loaded().
     */
    template <typename T>
    class StreamProvider : public BaseProvider<T>, public Singleton<StreamProvider<T>>
    {
    public:

        /**
         * @brief Get a resource by ID
         * 
         * If the resource is not currently loaded, a call to load()
         * will be isued.
         * @param i The resource identifier
         * @return A reference to the resource
         */
        T&
        get(int i)
        {
            if (!BaseProvider<T>::buffer[i]->loaded())
                return load(i);
            return BaseProvider<T>::get(i);
        }

        /**
         * Load a resource
         *
         * @param i The resource ID
         * @return A reference to the resource
         */
        T&
        load(int i)
        {
            BaseProvider<T>::buffer[i]->load();
            return BaseProvider<T>::get(i);
        }

        /**
         * Unload a resource
         *
         * @param i The resource ID
         * @return A reference to the resource
         */
        T&
        unload(int i)
        {
            BaseProvider<T>::buffer[i]->unload();
            return BaseProvider<T>::get(i);
        }

        /**
         * Reload a resource
         *
         * @param i The resource ID
         * @return A reference to the resource
         */
        T&
        reload(int i)
        {
            unload(i);
            return load(i);
        }

        /**
         * Reload every resource
         */
        void
        reloadAll()
        {
            for (std::size_t i = 0; i < BaseProvider<T>::size(); ++i)
            {
                if (BaseProvider<T>::buffer[i]->loaded())
                    reload(i);
            }
        }

        /**
         * Unload every resource
         */
        void
        unloadAll()
        {
            for (std::size_t i = 0; i < BaseProvider<T>::size(); ++i)
                unload(i);
        }

    };

    /**
     * A provider for shader programs
     */
    using ShaderProvider = Provider<ShaderProgram>;

    /**
     * A stream provider for images
     */
    using ImageProvider = StreamProvider<Image>;

    /**
     * A stream provider for textures
     */
    using TextureProvider = StreamProvider<Texture>;

    /**
     * A stream provider for fonts
     */
    using FontProvider = StreamProvider<Font>;

    /**
     * A stream provider for sound effects
     */
    using SfxProvider = StreamProvider<Sfx>;

    /**
     * A stream provider for musics
     */
    using MusicProvider = StreamProvider<Music>;
}

#endif
