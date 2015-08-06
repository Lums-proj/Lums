/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    GameObjectSet.hpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_GAME_OBJECT_SET_HPP
#define LUMS_GAME_OBJECT_SET_HPP

#include <vector>
#include <LumsInclude/GameObject/GameObject.hpp>
#include <LumsInclude/Provider.hpp>

namespace lm
{
    class GameObjectSet : public Singleton<GameObjectSet>
    {
    public:
        using container_type = std::vector<GameObject*>;

        using value_type = container_type::value_type;
        using allocator_type = container_type::allocator_type;
        using reference = container_type::reference;
        using const_reference = container_type::const_reference;
        using pointer = container_type::pointer;
        using const_pointer = container_type::const_pointer;

        using iterator = container_type::iterator;
        using const_iterator = container_type::const_iterator;
        using reverse_iterator = container_type::reverse_iterator; 
        using const_reverse_iterator = container_type::const_reverse_iterator;

        using difference_type = container_type::difference_type;
        using size_type = container_type::size_type;

        iterator begin() { return _gameObjects.begin(); }
        const_iterator begin() const { return _gameObjects.begin(); }
        const_iterator cbegin() const { return _gameObjects.cbegin(); }
        iterator end() { return _gameObjects.end(); }
        const_iterator end() const { return _gameObjects.end(); }
        const_iterator cend() const { return _gameObjects.cend(); }

        reverse_iterator rbegin() { return _gameObjects.rbegin(); }
        const_reverse_iterator rbegin() const { return _gameObjects.rbegin(); }
        const_reverse_iterator crbegin() const { return _gameObjects.crbegin(); }
        reverse_iterator rend() { return _gameObjects.rend(); }
        const_reverse_iterator rend() const { return _gameObjects.rend(); }
        const_reverse_iterator crend() const { return _gameObjects.crend(); }

        size_type size() const { return _gameObjects.size(); }
        bool empty() const { return _gameObjects.empty(); }

        void clear()
        {
            for (auto object : _gameObjects)
                delete object;
            _gameObjects.clear();
        }

        void remove(GameObject* object)
        {
            _gameObjects.erase(std::find(begin(), end(), object));
            delete object;
        }

        void remove(GameObject& object) { remove(&object); }

        GameObject& create(const char* name) { return create(GameObjectProvider::instance().get(name)()); }
        GameObject& create(GameObject& object) { return create(&object); }
        GameObject& create(GameObject* object)
        {
            _gameObjects.push_back(object);
            return *object;
        }

    private:
        container_type    _gameObjects;  
    };
}

#endif
