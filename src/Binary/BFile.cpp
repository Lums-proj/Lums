#include <fstream>
#include <LumsInclude/Binary/BFile.hpp>
#include <LumsInclude/OperatingSystem.hpp>

using namespace lm;

BFile::BFile()
: _size(0)
, _values(nullptr)
{

}

void
BFile::open(const std::string& path, bool resource)
{
    std::string fpath = (resource) ? resourcePath() + '/' + path : path;

    std::ifstream file(fpath);
    file.read((char *)&_size, 4);
    _values = new BValue[_size];

    for (int i = 0; i < _size; ++i)
        _values[i].parse(file);
}

BFile::~BFile()
{
    delete [] _values;
}