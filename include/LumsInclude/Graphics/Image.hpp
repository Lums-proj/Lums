/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Image.hpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_IMAGE_HPP
#define LUMS_IMAGE_HPP

#include <string>
#include <LumsInclude/Graphics/OpenGL.hpp>
#include <LumsInclude/ExportDll.hpp>

namespace lm
{
    /**
     * @cond
     */
    namespace ImageFormat
    {
        unsigned char*  png(FILE* file, unsigned int& width, unsigned int& height, GLenum& format);
    }
    /**
     * @endcond
     */

    /**
     * @brief This class represents an image in memory
     */
    class Image
    {
    public:
        /**
         * Create an empty Image.
         */
        LUMS_EXPORTED Image();

        /**
         * Deleted copy ctor
         */
        Image(const Image&) = delete;

        /**
         * Move-copy an Image.
         * @param rhs The image to be moved from.
         */
        LUMS_EXPORTED Image(Image&& rhs);

        /**
         * Deleted assignment operator
         */
        Image&  operator=(const Image&) = delete;

        /**
         * Move-assign an Image.
         * @param rhs The image to be moved from.
         */
        LUMS_EXPORTED Image&  operator=(Image&& rhs);

        /**
         * Get the image width.
         * @return The image width.
         */
        unsigned int
        width() const
        {
            return _width;
        }

        /**
         * Get the image height.
         * @return The image height.
         */
        unsigned int
        height() const
        {
            return _height;
        }

        /**
         * Get the image buffer width.
         * @return The image buffer width.
         */
        unsigned int
        bufferWidth() const
        {
            return _bufferWidth;
        }

        /**
         * Get the image buffer height.
         * @return The image buffer height.
         */
        unsigned int
        bufferHeight() const
        {
            return _bufferHeight;
        }

        /**
         * Get the image format, as an opengl enum.
         * Can be GL_RGB or GL_RGBA
         * @return The image format
         */
        GLenum
        format() const
        {
            return _format;
        }

        /**
         * Get a direct pointer to the buffer
         * @return A pointer to the buffer
         */
        const unsigned char*
        data() const
        {
            return _data;
        }

        /**
         * Check wether the image is loaded
         * @return True if the image is loaded, false otherwise
         */
        bool
        loaded() const
        {
            return _data != nullptr;
        }

        /**
         * Set the load path.
         * @param path The load path
         * @param resource If true, path is relative to the resource path
         */
        LUMS_EXPORTED void  setPath(const std::string path, bool resource = true);

        /**
         * Set the image buffer
         * @param buffer The new buffer
         * @param w The new buffer width
         * @param h The new buffer height
         * @param format The image format
         */
        LUMS_EXPORTED void  setBuffer(unsigned char* buffer, unsigned int w, unsigned int h, GLenum format);

        /**
         * Set the image scale when loaded.
         * Images are interpolated using nearest pixel.
         * @param scale The scale
         */
        LUMS_EXPORTED void  setScale(float scale);

        /**
         * Set the image scale hint.
         * This should be done when atlasing.
         * @param x The x hint
         * @param y The y hint
         */
        LUMS_EXPORTED void  setScaleHint(unsigned int x, unsigned int y);

        /**
         * Load the image
         */
        LUMS_EXPORTED void  load();

        /**
         * Unload the image
         */
        LUMS_EXPORTED void  unload();

        /**
         * Destructor
         */
        LUMS_EXPORTED ~Image();

    private:
        LUMS_EXPORTED void  resize();
        
        unsigned int    _width;
        unsigned int    _height;
        unsigned int    _bufferWidth;
        unsigned int    _bufferHeight;
        unsigned int    _xScaleHint;
        unsigned int    _yScaleHint;
        std::string     _path;
        GLenum          _format;
        unsigned char*  _data;
        float           _scale;
    };
}

#endif
