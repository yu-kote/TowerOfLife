#pragma once
#include "../GameObject.h"
#include "TolBlock.h"
#include "TolBlockActions.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "TolCoinHolder.h"

namespace tol
{
    class TolBlockHolder : public GameObject
    {
    public:

        TolBlockHolder() {}

        void setup()override;
        void update()override;
        void draw()override;

        void setCamera(std::shared_ptr<tol::Camera> camera_) { camera = camera_; }
        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }
        void setCoinHolder(std::shared_ptr<tol::TolCoinHolder> coin_holder_) { coin_holder = coin_holder_; }

        void reset();

    private: // �v���C���[

        std::shared_ptr<tol::Player> player;
        void playerSetStandRay();
        // ���C��������Ĉ�ԋ߂��Ƃ���ɓ������Ă�������_��Ԃ�
        float hitValueNearInZero(const ci::Ray& ray);

    private: // �J����

        void decideLookAtCamera();
        std::shared_ptr<tol::Camera> camera;
        ci::Vec3f ease_eyepoint;
        ci::Vec3f ease_center;

        void cameraDistanceToBlock();

    private: // �R�C��

        std::shared_ptr<tol::TolCoinHolder> coin_holder;

    private: // �u���b�N�̊Ǘ�

        // ��ԏ�Ɉ�i�ǉ�����
        void addOneStepBlocks(const std::vector<TolBlockActionType>& addblocktypes);

        void addBlocks();

    private:

        // �z��ԍ���������Ĕ͈͊O���ǂ�����Ԃ�
        bool isBlockOutOfRange(const int& num);
        // �z��ԍ������������ԑ傫���l��Ԃ�
        int adjusMinMaxNum(const int& num, const int& max_value);

        // �T�C�Y������Đ^�񒆂̒l��Ԃ�
        ci::Vec2f twoDimensionalArrayCenterPoint(const int&  size_x, const int& size_y);
        // ������������āA���̍����̈�i��̃u���b�N�̈ʒu��Ԃ�
        float convertBlockHeight(const float& height);
        // ������������āA���̍����ɂ���u���b�N�ƃu���b�N�̊Ԃ̍�����Ԃ�
        float centerBetweenBlockHeight(const float& height);


        int camera_height;                  // �J�����̍���
        int camera_up_time;                 // �J��������ɏオ�鎞��
        int camera_up_remaining_time;       // ��ɏオ��܂ł̎c�莞��

        int current_top_height;             // ��ԏ�̃u���b�N�̍���
        int height_interval;                // ��i���̊Ԋu
        int block_space;                    // �ׂ̃u���b�N�Ƃ̊Ԋu


        int z_num;                          // �u���b�N�̉��s���̐�
        int x_num;                          // �u���b�N�̉��̐�

        std::deque<std::shared_ptr<TolBlock>> blocks;

    };
}


