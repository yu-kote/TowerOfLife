#pragma once
#include "cinder/Camera.h"
#include "../../../Utility/Json/JsonInfo.h"
#include "../../GameObject/GameObject.h"

namespace tol
{
    class Player;
    class TolBlockHolder;

    class Camera : public tol::GameObject
    {
    public:
        Camera();

        void setup()override;
        void update()override;
        void laterUpdate()override;

        void awakeDraw()override;
        void laterDraw()override;

        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }
        void setTolBlockHolder(std::shared_ptr<tol::TolBlockHolder> block_holder_) { block_holder = block_holder_; }

        void setCenterOfInterestPoint(const ci::Vec3f & point) { center_of_interest_point = point; }
        ci::Vec3f getCenterOfInterestPoint() { return center_of_interest_point; }

        void setEyePoint(const ci::Vec3f & point) { transform.position = point; }
        void lookAt(const ci::Vec3f & eyepoint, const ci::Vec3f & target)
        {
            transform.position = eyepoint;
            center_of_interest_point = target;
        }

        ci::CameraPersp getCamera() { return camera; }

    private:
        ci::CameraPersp camera;

        ci::Vec3f center_of_interest_point;         // �����
        ci::Vec3f objective_distance;               // �X�e�[�W�Ƃ̋���
        ci::Vec3f objective_distance_init_value;    // �X�e�[�W�Ƃ̋����̏����l

        // �s���߂�����߂��l��Ԃ�
        ci::Vec3f restorePeak(ci::Vec3f check_value, ci::Vec3f restore_value);

    private: // json����ǂނƂ���

        JsonInfo json;
        void jsonSetup();

    private: // �v���C���[

        std::shared_ptr<tol::Player> player;

    public: // �X�e�[�W�Ƃ̂����

        int getCameraHeight() { return camera_height; }

    private:

        // �J�����̈ʒu�ƌ��������߂�֐�
        void decideLookAtCamera();
        // �J�������グ��
        void upCamera();
        // �J�������C�[�W���O����
        void easeCamera();

        std::shared_ptr<TolBlockHolder> block_holder;
        ci::Vec3f ease_eyepoint;            // �C�[�W���O����J�����̈ʒu
        ci::Vec3f ease_center;              // �C�[�W���O����J�����̌����
        float ease_speed;                   // �C�[�W���O�̑���
        int camera_height;                  // �J�����̍���
        int camera_up_time;                 // �J��������ɏオ�鎞��
        int camera_up_remaining_time;       // ��ɏオ��܂ł̎c�莞��

    };
}