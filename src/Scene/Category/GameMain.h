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

    void countDownStop();
    void stopObjects(const bool& active);

    bool is_gamestop;
    bool current_gamestop;
    void gameStop();

};