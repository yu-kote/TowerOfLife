#pragma once
#include "../GameObject.h"
#include "TolBlock.h"
#include "TolBlockActions.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"

namespace tol
{
    class TolBlockHolder : public GameObject
    {
    public:

        TolBlockHolder() {}

        void setup();
        void update();
        void draw();

        void setCamera(std::shared_ptr<tol::Camera> camera_) { camera = camera_; }
        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }

    private:


        std::shared_ptr<tol::Player> player;
        void playerSetStandRay();
        // ���C��������Ĉ�ԋ߂��Ƃ���ɓ������Ă�������_��Ԃ�
        float hitValueNearInZero(const ci::Ray& ray);

    private:

        void decideLookAtCamera();
        std::shared_ptr<tol::Camera> camera;
        ci::Vec3f ease_eyepoint;
        ci::Vec3f ease_center;


    private: // �u���b�N�̊Ǘ�

        // ��ԏ�Ɉ�i�ǉ�����
        void addOneStepBlocks(const std::vector<TolBlockActionType>& addblocktypes);

    private:

        // �z��ԍ���������Ĕ͈͊O���ǂ�����Ԃ�
        bool isBlockOutOfRange(const int& num);
        // �z��ԍ������������ԑ傫���l��Ԃ�
        int adjusMinMaxNum(const int& num, const int& max_value);

        ci::Vec2f twoDimensionalArrayCenterPoint(const int&  size_x, const int& size_y);
        // ������������āA���̍����̈�i��̃u���b�N�̈ʒu��Ԃ�
        float convertBlockHeight(const float& height);
        // ������������āA���̍����ɂ���u���b�N�ƃu���b�N�̊Ԃ̍�����Ԃ�
        float centerBetweenBlockHeight(const float& height);

        float current_top_height;     // ��ԏ�̃u���b�N�̍���
        float height_interval;        // ��i���̊Ԋu
        float block_interval;         // �ׂ̃u���b�N�Ƃ̊Ԋu


        int z_num;                    // �u���b�N�̉��s���̐�
        int x_num;                    // �u���b�N�̉��̐�

        std::vector<std::shared_ptr<TolBlock>> blocks;

    };
}


