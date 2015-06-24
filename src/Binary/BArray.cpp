#include <LumsInclude/Binary/BArray.hpp>

using namespace lm;

BArray::BArray()
: _size(0)
, _values(nullptr)
{

}

BArray::BArray(const BArray& rhs)
: _size(rhs._size)
{
    if (!_size)
        _values = nullptr;
    else
    {
        _values = new BValue[_size];
        for (int i = 0; i < _size; ++i)
            _values[i] = rhs._values[i];
    }
}

BArray&
BArray::operator=(const BArray& rhs)
{
    delete [] _values;
    _size = rhs._size;
    if (!_size)
        _values = nullptr;
    else
    {
        _values = new BValue[_size];
        for (int i = 0; i < _size; ++i)
            _values[i] = rhs._values[i];
    }
    return *this;
}

void
BArray::parse(std::ifstream& file)
{
    file.read((char*)&_size, 4);
    _values = new BValue[_size];
    for (int i = 0; i < _size; ++i)
        _values[i].parse(file);
}

BArray::~BArray()
{
    delete [] _values;
}
