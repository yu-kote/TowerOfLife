#pragma once
#include "../GameObject.h"


namespace tol
{
    class Player : public GameObject
    {
    public:

        void setup()override;
        void update()override;
        void draw()override;



    private:



    };


}