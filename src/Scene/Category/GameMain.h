#pragma once
#include "../Manager/SceneBase.h"


class GameMain : public SceneBase
{
public:
    GameMain();
    void setup()override;
    void update()override;
    void draw() override;
    void shift()override;
    void shutdown()override;

private:

    std::string select_name;
};