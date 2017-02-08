#pragma once
#include "TolBlockActionBase.h"


namespace tol
{
    enum TolBlockActionType
    {
        NORMAL,
        ROUNDTRIP,
    };

    class NormalBlock : public TolBlockActionBase
    {
    public:
        NormalBlock(TolBlock* block_);

        void update()override;

    private:

    };

    class RoundTripBlock : public TolBlockActionBase
    {
    public:
        RoundTripBlock(TolBlock* block_);

        void update()override;
    private:
        float movecount;
    };

}
