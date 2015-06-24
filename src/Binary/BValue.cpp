#include <LumsInclude/Binary/BValue.hpp>
#include <LumsInclude/Binary/BArray.hpp>
#include <LumsInclude/Binary/BObject.hpp>


using namespace lm;

BValue::BValue()
: _type(BType::None)
{

}

BValue::BValue(const BValue& rhs)
: _type(rhs._type)
{
    switch (_type)
    {
        case BType::Int:
            _int = rhs._int;
            break;
        case BType::Float:
            _float = rhs._float;
            break;
        case BType::String:
            _string = new char[strlen(rhs._string) + 1];
            strcpy(_string, rhs._string);
            break;
        case BType::Array:
            _array = new BArray(*(rhs._array));
            break;
        case BType::Object:
            _object = new BObject(*(rhs._object));
        default:
            break;
    }
}

BValue&
BValue::operator=(const BValue& rhs)
{
    _type = rhs._type;
    switch (_type)
    {
        case BType::Int:
            _int = rhs._int;
            break;
        case BType::Float:
            _float = rhs._float;
            break;
        case BType::String:
            _string = new char[strlen(rhs._string) + 1];
            strcpy(_string, rhs._string);
            break;
        case BType::Array:
            _array = new BArray(*(rhs._array));
            break;
        case BType::Object:
            _object = new BObject(*(rhs._object));
        default:
            break;
    }
    return *this;
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

BInt
BValue::asInt() const
{
    return _int;
}

BFloat
BValue::asFloat() const
{
    return _float;
}

const BObject&
BValue::asObject() const
{
    return *_object;
}

const BString
BValue::asString() const
{
    return _string;
}

const BArray&
BValue::asArray() const
{
    return *_array;
}

const BValue&
BValue::operator[](int i) const
{
    return (*_array)[i];
}

const BValue&
BValue::operator[](const char* str) const
{
    return (*_object)[str];
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