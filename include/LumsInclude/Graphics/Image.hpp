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
        size_t
        width() const
        {
            return _width;
        }

        /**
         * Get the image height.
         * @return The image height.
         */
        size_t
        height() const
        {
            return _height;
        }


        LUMS_EXPORTED void  setPath(const std::string path, bool resource = true);
        /**
         * Load a png image from a file.
         * @param path The file path.
         * @param resource If true, prepend resourcePath() to the path.
         * @return A reference to an image.
         */

        LUMS_EXPORTED void  load();

        LUMS_EXPORTED void  loadFilePNG();

        /**
         * Destructor
         */
        LUMS_EXPORTED ~Image();

    private:
        size_t                          _width;
        size_t                          _height;
        std::string                     _path;
        GLint                           _format;
    };
}

#endif
