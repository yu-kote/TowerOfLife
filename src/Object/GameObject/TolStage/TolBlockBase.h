#pragma once
#include "cinder/app/App.h"
#include "../GameObject.h"


namespace tol
{
    class TolBlockBase : public GameObject
    {
        // �u���b�N���ƂɎ����Ă��鉽������̓��ʂȓ���
        virtual void action() {}
    };
}
