#pragma once
#include "SceneBase.h"
#include <memory>


#define SceneCreate SceneManager::instance().sceneCreate

class SceneManager
{
    SceneManager() {}
public:

    static SceneManager& instance()
    {
        static SceneManager scenemanager;
        return scenemanager;
    }

    template<class T>
    void sceneCreate(T* create)
    {
        scene = std::make_shared<T>(*create);
    }

    SceneBase& get() { return *scene; }

private:

    std::shared_ptr<SceneBase> scene;
};
