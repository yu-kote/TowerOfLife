#pragma once
#include "../../Object/GameObject/GameObjectEntities.h"

class SceneBase
{
public:

    virtual void setup() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void shift() = 0;
    virtual void shutdown() = 0;

protected:
    tol::GameObjectEntities entities;
};