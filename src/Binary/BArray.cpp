#include <LumsInclude/Binary/BArray.hpp>

using namespace lm;

BArray::BArray()
: _size(0)
, _values(nullptr)
{

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