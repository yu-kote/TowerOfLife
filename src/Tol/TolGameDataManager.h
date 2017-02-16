#pragma once

#define TolData TolGameDataManager::instance()

namespace tol
{
    class TolGameDataManager
    {
        TolGameDataManager() {}
    public:

        static TolGameDataManager& instance()
        {
            static TolGameDataManager data;
            return data;
        }


        int coin = 0;
        int score = 0;



    };
}

