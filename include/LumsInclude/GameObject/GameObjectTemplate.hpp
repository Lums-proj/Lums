/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    GameObjectTemplate.hpp                         oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_GAME_OBJECT_TEMPLATE
#define LUMS_GAME_OBJECT_TEMPLATE

#include <string>
#include <unordered_map>
#include <LumsInclude/Binary/BValue.hpp>
#include <LumsInclude/GameObject/GameObject.hpp>

namespace lm
{
    class GameObjectTemplate
    {
    public:
        GameObjectTemplate();
        void        load();
        void        loadBinary(const BObject& object);
        GameObject* operator()();
        ~GameObjectTemplate();

    private:
        std::unordered_map<size_t, BObject>     _components;
    };
}

#endif
