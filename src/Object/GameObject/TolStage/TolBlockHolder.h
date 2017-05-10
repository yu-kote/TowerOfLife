#pragma once
#include "../../../Utility/Json/JsonInfo.h"
#include "../GameObject.h"
#include "TolBlock.h"
#include "TolBlockActions.h"
#include "TolCoinHolder.h"

namespace tol
{
    class Player;
    class Camera;

    class TolBlockHolder : public GameObject
    {
    public:
        TolBlockHolder() {}

        void setup()override;
        void update()override;
        void draw()override;
        void transDraw()override;

        void setCamera(std::shared_ptr<tol::Camera> camera_) { camera = camera_; }
        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }
        void setCoinHolder(std::shared_ptr<tol::TolCoinHolder> coin_holder_) { coin_holder = coin_holder_; }

        // ���Z�b�g�֐�
        void reset();

    private: // �v���C���[

        std::shared_ptr<tol::Player> player;
        // ���C�̂����蔻�肷��Ƃ���
        void playerSetStandRay();
        // ���C��������Ĉ�ԋ߂��Ƃ���ɓ������Ă�������_��Ԃ�
        float hitValueNearInZero(const ci::Ray& ray);

    public: // �J����

        int getHeightInterval() { return height_interval; }
        ci::Vec2f getCenterPos() { return twoDimensionalArrayCenterPoint(x_num, z_num); }
        // ������������āA���̍����ɂ���u���b�N�ƃu���b�N�̊Ԃ̍�����Ԃ�
        float centerBetweenBlockHeight(const int& height);
        int getBlockSpace() { return block_space; }

    private:

        // �J�����ƃu���b�N�̋������݂ău���b�N����������֐�
        void cameraDistanceToBlockErase();

        std::shared_ptr<tol::Camera> camera;

    private: // �R�C���̏��

        std::shared_ptr<tol::TolCoinHolder> coin_holder;

    private: // �u���b�N�̏��Ǘ�

        // json����u���b�N�̏�������������֐�
        void stageSetup();
        // ��ԏ�Ɉ�i�ǉ�����
        void addOneStepBlocks(const std::vector<TolBlockActionType>& addblocktypes);
        // json�ǂݍ��݂��ău���b�N��ǉ�����֐�
        void addBlocks();

        // �v���C���[�ƃu���b�N�����Ԃ�����u���b�N�𓧖�������֐�
        void transBlock();

        JsonInfo json;

    private: // �X�e�[�W

        // �z��ԍ���������Ĕ͈͊O���ǂ�����Ԃ�
        bool isBlockOutOfRange(const int& num);
        // �z��ԍ������������ԑ傫���l��Ԃ�
        int adjusMinMaxNum(const int& num, const int& max_value);
        // �u���b�N�����}�X�ɂȂ��Ă����S�_��Ԃ�
        ci::Vec2f twoDimensionalArrayCenterPoint(const int&  size_x, const int& size_y);
        // ����ԍ����Ƃ���̒i����Ԃ�
        int currentTopBlockStep();


        int current_top_height;             // ��ԏ�̃u���b�N�̍���
        int height_interval;                // ��i���̊Ԋu
        int block_space;                    // �ׂ̃u���b�N�Ƃ̊Ԋu

        int z_num;                          // �u���b�N�̉��s���̐�
        int x_num;                          // �u���b�N�̉��̐�

        std::deque<std::shared_ptr<TolBlock>> blocks;   // popfront������̂�deque���ő�

    private:

    };
}


