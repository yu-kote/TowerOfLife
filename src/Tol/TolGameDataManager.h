#pragma once
#include <list>
#define TolData TolGameDataManager::instance()

enum SceneCategory
{
    TITLE,
    GAMEMAIN,
    GACHA,
};

enum TolItem
{
    SCROLL_STOP,
    GIMMICK_STOP,
    TWO_STEP_JUMP,
    ITEM_MAX,
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
            setup();
        }

        void setup();

    public:

        static TolGameDataManager& instance()
        {
            static TolGameDataManager data;
            return data;
        }

        SceneCategory prev_scene;

        std::list<TolItem> itemlist;
        TolItem using_item;
        bool hasItem(const TolItem& item);
        void useItem(const TolItem& item);
        int itemCountCheck(const TolItem& item);

        int temp_coin;
        int coin;
        int score;

        std::string getItemName(const TolItem& item);
        std::string getItemInstruction(const TolItem& item);
    };
}

