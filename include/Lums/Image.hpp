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
#include <vector>
#include <Lums/GL.hpp>
#include <Lums/Rect2.hpp>
#include <Lums/ImageDescriptor.hpp>
#include <Lums/ExportDll.hpp>

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
         * Bind the image to the OpenGL context.
         */
        void
        bind() const
        {
            glBindTexture(GL_TEXTURE_2D, _texture);
        }

        /**
         * Get the texture identifier.
         * @return A texture identifier, or 0 if the image is not valid.
         */
        GLuint
        texture() const
        {
            return _texture;
        }

        /**
         * Check if the image is valid.
         * @return true if the image is valid.
         */
        bool
        valid() const
        {
            return _texture != 0;
        }

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

        size_t
        iwidth() const
        {
            return _iwidth;
        }

        size_t
        iheight() const
        {
            return _iheight;
        }

        /**
         * Get a rect from the atlas.
         * @param i The index of the value to get from the atlas.
         * @return A rect representing an atlas value.
         */
        const FrameDescriptord&
        atlasAt(size_t i) const
        {
            return _atlas[i];
        }

        /**
         * Set the image scaling mode.
         * @param linear If true, set the scaling mode to linear, else, set it to nearest.
         * @return A reference to the image.
         */
        Image&
        linear(bool linear = true)
        {
            bind();
            glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , linear ? GL_LINEAR : GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , linear ? GL_LINEAR : GL_NEAREST);
            return *this;
        }

        /**
         * TODO
         */
        LUMS_EXPORTED Image& atlas(size_t w = 1, size_t h = 1);

        /**
         * TODO
         */
        LUMS_EXPORTED Image& atlas(const lm::FrameDescriptori* rect, size_t n);

        /**
         * Load an image from a file.
         * @param path The file path.
         * @param resource If true, prepend resourcePath() to the path.
         * @return A reference to an image.
         */
        LUMS_EXPORTED void  loadFile(const std::string path, bool resource = true);

        /**
         * Load a png image from a file.
         * @param path The file path.
         * @param resource If true, prepend resourcePath() to the path.
         * @return A reference to an image.
         */
        LUMS_EXPORTED void  loadFilePNG(const std::string path, bool resource = true);


        /**
         * TODO
         */
        LUMS_EXPORTED void  loadDescriptor(const ImageDescriptor& descriptor);

        /**
         * Load an image from a file.
         * @param path The file path.
         * @param resource If true, prepend resourcePath() to the path.
         * @return A reference to an image.
         */
        LUMS_EXPORTED static Image    fromFile(const std::string path, bool resource = true);

        /**
         * Destructor
         */
        LUMS_EXPORTED ~Image();

    private:
        void                gen(unsigned char* img, GLint format);

        size_t                          _width;
        size_t                          _height;
        size_t                          _iwidth;
        size_t                          _iheight;
        std::vector<FrameDescriptord>   _atlas;
        GLuint                          _texture;
    };
}

#endif
