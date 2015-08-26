/* ************************************************************************** */
/*                                                                            */
/*    Core/Identifier.cpp                            oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <Lums/Core.d/Identifier.hpp>

using namespace lm;

struct strCompare : std::binary_function<char*, char*, bool>
{
    bool
    operator()(const char* str1, const char* str2) const
    {
        return strcmp(str1, str2) == 0;
    }
};

// FNV-1a
struct strHash
{
    size_t
    operator()(const char* str) const
    {
        static const size_t prime = 0x01000193;
        size_t hash = 0x811C9DC5;
        while (*str)
        {
            hash = (hash ^ *str) * prime;
            str++;
        }
        return hash;
    }
};

using IdentifierMap = std::unordered_map<const char*, size_t, strHash, strCompare>;
using StringVector = std::vector<const char*>;

static IdentifierMap&
idMap()
{
    static IdentifierMap map;
    return map;
}

static StringVector&
strVector()
{
    static StringVector vector;
    return vector;
}

Identifier::Identifier(const char* str)
{
    static IdentifierMap& map = idMap();
    static StringVector& vector = strVector();
    static size_t counter = 0;

    auto it = map.find(str);
    if (it != map.end())
        _index = it->second;
    else
    {
        char* dup = strdup(str);
        map[dup] = counter;
        vector[counter] = dup;
        _index = counter;
        counter++;
    }
}

const char*
Identifier::str() const
{
    static StringVector& vector = strVector();
    return vector[_index];
}
