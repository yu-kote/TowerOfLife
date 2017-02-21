#pragma once
#include "GameObject.h"
#include <iostream>

namespace tol
{
    class GameObjectEntities
    {
    public:
        GameObjectEntities();
        ~GameObjectEntities();

        void setupGameObject();

        void updateGameObject();
        void laterUpdateGameObject();

        void awakeDrawGameObject();
        void drawGameObject();
        void transDrawGameObject();
        void laterDrawGameObject();
        void transLaterDrawGameObject();

        void allDestroy();
    private:

        void componentsUpdate();

        void drawBegin();
        void drawEnd();

        void componentsDraw();
        void componentsDestory();

    public:

        template<typename T>
        void instantiate()
        {
            std::string classname = createClassName<T>();
            gameobjects.insert(std::make_pair(classname, std::make_shared<T>()));
        }

        template<typename T>
        void instantiate(const T& ptr)
        {
            std::string classname = createClassName<T>();
            gameobjects.insert(std::make_pair(classname, std::make_shared<T>(ptr)));
        }

        // GameObjectを継承したクラスの情報を知りたいとき
        // static_pointer_cast<> shared_ptrのキャスト
        // 参考 https://cpprefjp.github.io/reference/memory/shared_ptr/static_pointer_cast.html
        template<typename T>
        std::shared_ptr<T> getInstance()
        {
            std::string classname = createClassName<T>();
            if (gameobjects.find(classname) == gameobjects.end())
                assert(!"GameObject Not Finded");

            /*int script_size = sizeof(T);
            if (script_size > 128)
            {
                return std::dynamic_pointer_cast<T>(gameobjects.find(classname)->second);
            }
            else
            {
                return std::static_pointer_cast<T>(gameobjects.find(classname)->second);
            }*/
            return std::static_pointer_cast<T>(gameobjects.find(classname)->second);
        }

        template<typename T>
        void destroyGameObject()
        {
            std::string classname = createClassName<T>();
            if (objects.find(classname) == objects.end())
            {
                return;
            }
            objects.find(classname)->second->componentsDestroy();
            objects.find(classname)->second->destory();

            objects.erase(objects.find(classname));
        }

        void destroyGameObject(std::string classname_)
        {
            if (gameobjects.find(classname_) == gameobjects.end())
                return;

            gameobjects.find(classname_)->second->componentsDestroy();
            gameobjects.find(classname_)->second->destory();

            gameobjects.erase(classname_);
        }

    private:

        template<typename T>
        static std::string createClassName()
        {
            const type_info& id = typeid(T);

            std::string class_name = id.name();
            class_name.erase(0, 6);

            return class_name;
        }

    private:
        std::unordered_map<std::string, std::shared_ptr<GameObject>> gameobjects;
    };
}