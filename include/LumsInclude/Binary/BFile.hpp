/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    BFile.hpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_BFILE_HPP
#define LUMS_BFILE_HPP

#include <string>
#include <LumsInclude/Binary/BValue.hpp>

namespace lm
{
    class BFile
    {
        class Iterator
        {
        public:
            Iterator(const BFile& file, int index) : _file(file), _index(index){}
            Iterator        operator++() { Iterator i = *this; _index++; return i; }
            Iterator        operator++(int) { _index++; return *this; }
            Iterator        operator--() { Iterator i = *this; _index--; return i; }
            Iterator        operator--(int) { _index--; return *this; }
            const BValue&   operator*() { return _file[_index]; }
            const BValue&   operator->() { return _file[_index]; }
            bool            operator==(const Iterator& rhs) { return _index == rhs._index; }
            bool            operator!=(const Iterator& rhs) { return !(*this == rhs); }

        private:
            const BFile&    _file;
            int             _index;
        };

    public:
        BFile();
        void            open(const std::string& path, bool resource = true);
        int             size() const { return _size; }
        const BValue&   operator[](int i) const { return _values[i]; }
        Iterator        begin() const { return Iterator(*this, 0); }
        Iterator        end() const { return Iterator(*this, _size); }
        ~BFile();

    private:
        int         _size;
        BValue*     _values;
    };
}

#endif
