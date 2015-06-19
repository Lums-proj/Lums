#include <LumsInclude/Binary/BValue.hpp>
#include <LumsInclude/Binary/BArray.hpp>
#include <LumsInclude/Binary/BObject.hpp>


using namespace lm;

BValue::BValue()
: _type(BType::None)
{

}

void
BValue::parse(std::ifstream& file)
{
    char c;

    file.read(&c, 1);

    switch (c)
    {
        case 'i':
            _type = BType::Int;
            file.read((char*)&_int, 4);
            break;
        case 'f':
            _type = BType::Float;
            file.read((char*)&_float, 4);
            break;
        case 's':
            _type = BType::String;
            int size;
            file.read((char*)&size, 4);
            _string = new char[size + 1];
            _string[size] = 0;
            file.read(_string, size);
            break;
        case 'o':
            _type = BType::Object;
            _object = new BObject;
            _object->parse(file);
            break;
        case 'a':
            _type = BType::Array;
            _array = new BArray;
            _array->parse(file);
        default:
            break;
    } 
}

BValue::~BValue()
{
    switch (_type)
    {
        case BType::String:
            delete [] _string;
            break;
        case BType::Array:
            delete _array;
            break;
        case BType::Object:
            delete _object;
        default:
            break;
    }
}