#pragma once
#include "../Manager/SceneBase.h"


class Gacha : public SceneBase
{
public:
    Gacha();
    void setup()override;
    void update()override;
    void draw() override;
    void shift()override;
    void shutdown()override;

private:
};