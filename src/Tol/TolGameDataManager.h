#pragma once

#define TolData TolGameDataManager::instance()

enum SceneCategory
{
    TITLE,
    GAMEMAIN,
    GACHA,
};

namespace tol
{
    class TolGameDataManager
    {
        TolGameDataManager()
        {
            temp_coin = 0;
            coin = 0;
            score = 0;
        }
    public:

        static TolGameDataManager& instance()
        {
            static TolGameDataManager data;
            return data;
        }

        SceneCategory prev_scene;

        int temp_coin;
        int coin;
        int score;



    };
}

