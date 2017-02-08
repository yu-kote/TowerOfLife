#pragma once
#include "../GameObject.h"
#include "TolBlock.h"
#include "TolBlockActions.h"

namespace tol
{
    class TolBlockHolder : public GameObject
    {
    public:

        TolBlockHolder() {}

        void setup();
        void update();
        void draw();


    private:

        // ��ԏ�Ɉ�i�ǉ�����
        void addOneStepBlocks(const std::vector<TolBlockActionType>& addblocktypes);

    private:

        float current_top_height;     // ��ԏ�̃u���b�N�̍���
        float height_interval;        // ��i���̊Ԋu
        float block_interval;         // �ׂ̃u���b�N�Ƃ̊Ԋu

        int z_num;                    // �u���b�N�̉��s���̐�
        int x_num;                    // �u���b�N�̉��̐�

        std::vector<std::shared_ptr<TolBlock>> blocks;

    };
}


