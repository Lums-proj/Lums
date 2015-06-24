#include <cstring>
#include <LumsInclude/Binary/BObject.hpp>
#include <LumsInclude/Binary/BValue.hpp>

using namespace lm;

BObject::BObject()
: _size(0)
, _values(nullptr)
{

}

BObject::BObject(const BObject& rhs)
: _size(rhs._size)
{
    if (!_size)
        _values = nullptr;
    else
    {
        _values = new BPair[_size];
        for (int i = 0; i < _size; ++i)
        {
            _values[i].first = new char[strlen(rhs._values[i].first) + 1];
            strcpy(_values[i].first, rhs._values[i].first);
            _values[i].second = rhs._values[i].second;
        }
    }
}

BObject&
BObject::operator=(const BObject& rhs)
{
    for (int i = 0; i < _size; ++i)
        delete [] _values[i].first;
    delete [] _values;
    _size = rhs._size;
    if (!_size)
        _values = nullptr;
    else
    {
        _values = new BPair[_size];
        for (int i = 0; i < _size; ++i)
        {
            _values[i].first = new char[strlen(rhs._values[i].first) + 1];
            strcpy(_values[i].first, rhs._values[i].first);
            _values[i].second = rhs._values[i].second;
        }
    }
    return *this;
}

void
BObject::parse(std::ifstream& file)
{
    file.read((char*)&_size, 4);
    _values = new BPair[_size];
    for (int i = 0; i < _size; ++i)
    {
        int size;
        file.read((char*)&size, 4);
        char* str = new char[size + 1];
        str[size] = 0;
        file.read(str, size);
        _values[i].first = str;
        _values[i].second.parse(file);
    }
}

const BValue&
BObject::operator[](const char* str) const
{
    for (int i = 0; i < _size; ++i)
    {
        if (strcmp(str, _values[i].first) == 0)
            return _values[i].second;
    }
    return *(BValue*)nullptr;
}


BObject::~BObject()
{
    for (int i = 0; i < _size; ++i)
        delete [] _values[i].first;
    delete [] _values;
}