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

#ifndef LUMS_PROVIDER_HPP
#define LUMS_PROVIDER_HPP

#include <unordered_map>
#include <iterator>
#include <cstdint>
#include <string>
#include <LumsInclude/Graphics/ShaderProgram.hpp>
#include <LumsInclude/Audio/Sfx.hpp>
#include <LumsInclude/Audio/Music.hpp>
#include <LumsInclude/Graphics/Image.hpp>
#include <LumsInclude/Graphics/Texture.hpp>
#include <LumsInclude/Graphics/Font.hpp>
#include <LumsInclude/Binary/BFile.hpp>
#include <LumsInclude/Binary/BObject.hpp>
#include <LumsInclude/Singleton.hpp>
#include <LumsInclude/Common.hpp>
#include <LumsInclude/GameObject/GameObjectTemplate.hpp>

namespace lm
{
    /**
     * @brief A basic abstract class for providers
     */
    template <typename T>
    class BaseProvider
    {
    public:
        using iterator = typename std::unordered_map<int, T*>::iterator;

        /**
         * Get a resource by name
         * @param str The resource name
         * @return A reference to the resource
         */
        T&
        get(const char* str)
        {
            return get(sym(str));
        }

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
         * Allocate and return a resource using it's name
         * @param str The resource identifier
         * @return A reference to the resource
         */
        T&
        set(const char* str)
        {
            return set(sym(str));
        }

        /**
         * Allocate and return a resource using it's ID
         * @param i The resource identifier
         * @return A reference to the resource
         */
        T&
        set(int i)
        {
            if (buffer[i] == nullptr)
                buffer[i] = new T();
            return *buffer[i];
        }

        /**
         * Get the begin iterator.
         * @return An iterator to the first resource.
         */
        iterator
        begin()
        {
            return buffer.begin();
        }

        /**
         * Get the end iterator.
         * @return An iterator past the last resource.
         */
        iterator
        end()
        {
            return buffer.end();
        }

        void
        loadBinary(const std::string& path, bool resource = true)
        {
            BFile file;

            file.open(path, resource);
            for (auto& o : file)
            {
                T& res = set(o["name"].asString());
                res.loadBinary(o.asObject());
            }
        }

    protected:
        /**
         * The resource container
         */
        std::unordered_map<int, T*> buffer;
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
         * @brief Get a resource by name
         * 
         * If the resource is not currently loaded, a call to load()
         * will be isued.
         * @param str The resource name
         * @return A reference to the resource
         */
        T&
        get(const char* str)
        {
            return get(sym(str));
        }

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
            this->buffer[i]->unload();
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
            for (auto r : this->buffer)
            {
                if (r.second->loaded())
                    reload(r.first);
            }
        }

        /**
         * Unload every resource
         */
        void
        unloadAll()
        {
            for (auto r : this->buffer)
                unload(r.first);
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

    /**
     * A provider for game object templates
     */
    using GameObjectProvider = Provider<GameObjectTemplate>;
}

#endif
