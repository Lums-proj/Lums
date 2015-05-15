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
    namespace ImageFormat
    {
        unsigned char*  png(FILE* file, unsigned int& width, unsigned int& height, GLenum& format);
    }

    /**
     * This class represents an Image, stored in the most efficient way speed-wise.
     */
    class Image
    {
    public:
        /**
         * Create an empty Image.
         */
        LUMS_EXPORTED Image();

        Image(const Image&) = delete;

        /**
         * Move-copy an Image.
         * @param rhs The image to be moved from.
         */
        LUMS_EXPORTED Image(Image&& rhs);

        Image&  operator=(const Image&) = delete;

        /**
         * Move-copy an Image.
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

        GLenum
        format() const
        {
            return _format;
        }

        const unsigned char*
        data() const
        {
            return _data;
        }

        bool
        loaded() const
        {
            return _data != nullptr;
        }

        LUMS_EXPORTED void  setPath(const std::string path, bool resource = true);
        /**
         * Load a png image from a file.
         * @param path The file path.
         * @param resource If true, prepend resourcePath() to the path.
         * @return A reference to an image.
         */

        LUMS_EXPORTED void  load();

        LUMS_EXPORTED void  unload();

        /**
         * Destructor
         */
        LUMS_EXPORTED ~Image();

    private:
        unsigned int    _width;
        unsigned int    _height;
        std::string     _path;
        GLenum          _format;
        unsigned char*  _data;
    };
}

#endif
