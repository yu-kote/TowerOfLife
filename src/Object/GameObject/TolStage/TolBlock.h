#pragma once
#include "cinder/app/App.h"
#include "../GameObject.h"
#include "TolBlockActionBase.h"


namespace tol
{
    class TolBlock : public GameObject
    {
    public:
        TolBlock() {}

        void setup()override;
        void update()override;
        void draw()override;

        void transDraw()override;

        template<class T>
        void setBlockAction()
        {
            action = std::make_shared<T>(T(static_cast<TolBlock*>(this)));
            action->setup();
        }
    private:
        std::shared_ptr<TolBlockActionBase> action;

    };
}

