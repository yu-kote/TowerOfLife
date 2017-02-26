#pragma once
#include "../Manager/SceneBase.h"


class Title : public SceneBase
{
public:
    Title();
    void setup()override;
    void update()override;
    void draw() override;
    void shift()override;
    void shutdown()override;

private:
};