#pragma once
#include "../GameObject.h"
#include "../Camera/Camera.h"
#include "cinder/Ray.h"

#include "../../../Utility/Interface/Interface.h"

namespace tol
{
    class Player : public GameObject
    {
    public:
        // �v���C���[�̏��
        enum State
        {
            STAND,
            MOVING,
            RIZING,
            FALL,
        };

        void setup()override;
        void update()override;
        void draw()override;
        void laterDraw()override;

        void setCamera(std::shared_ptr<tol::Camera> camera_) { camera = camera_; }

        ci::Ray getStandRay() { return stand_ray; }
        void setStandRayIntersection(const float & t) { stand_ray_intersection = t; }
        float getStandRayIntersection() { return stand_ray_intersection; }

        ci::Ray getRizeRay() { return rize_ray; }
        void setRizeRayIntersecion(const float& t) { rize_ray_intersection = t; }

        ci::Ray getCameraRay() { return camera_ray; }

        bool isDead() { return is_fall_dead; }

        bool isStand() { return (state == State::STAND || state == State::MOVING); }



    private:
        std::shared_ptr<tol::Camera> camera;

        // �ړ��֐�
        void axisMove();
        // �p�b�h�̍��X�e�B�b�N�̑傫�����擾
        ci::Vec2f getLeftAxisVec();

        // �x�N�g�����݂ĉ�]������֐�
        void vecRotate();

        // �p�x�̍����o��
        float angleDifference(const float& angle1, const float& angle2);

        // float�̒l��0��t�̑����ŋ߂Â���
        void valueSlowlyToZero(float& value, float t);

        // ���C�̍X�V
        void rayUpdate();
        // �W�����v
        void jump();
        // �d�͂�������
        void useGravity();
        // ����
        void stand();
        // �����Ԃ���
        void hitTheHead();

        // �v���C���[�̏�Ԃ��X�V����֐�
        void stateUpdate();

        void gameover();

        // ���Z�b�g�֐�
        void reset();
    private:

        ci::TriMesh* mesh;


        State state;                        // �v���C���[�̏��
        State current_state;                // ���̃v���C���[�̏�Ԃ�ۑ�


        ci::Vec3f velocity;                 // �x�N�g��
        ci::Quatf current_quat;             // ���̃N�H�[�^�j�I��
        float ground_move_speed;            // �n��ɂ���Ƃ��̉����x
        float ground_move_speed_max;        // �n��ɂ���Ƃ��̑����̍ő�l
        ci::Vec3f moving_distance;          // ��t���[���Ɉړ����鋗��
        bool is_max_speed;                  // �������I����Ă��邩�ǂ���
        float air_move_speed;               // �󒆂ɂ���Ƃ��̈ړ����x


        float gravity;                      // �d��
        float fall_speed_max;               // ��������ő呬�x


        float jump_power;                   // �W�����v��
        ci::Vec3f jump_moment_vec;          // �W�����v����u�Ԃ̈ړ��x�N�g��
        int jump_duration;                  // �W�����v�{�^�������������
        int jump_time;                      // �W�����v���Ă���Ԃ̎���
        bool is_jump_key_press;             // �W�����v�L�[�������Ă��邩�ǂ���
        bool can_jump;                      // �W�����v�ł��邩�ǂ���


        ci::Ray stand_ray;                  // �n�ʂɗ����߂̃��C
        float stand_ray_intersection;       // �n�ʂɗ����߂̃��C�̌����n�_

        ci::Ray rize_ray;                   // �V��ɂԂ��邽�߂̃��C
        float rize_ray_intersection;        // �V��ɂԂ��邽�߂̃��C�̌����n�_

        bool is_fall_dead;                  // �������������ǂ���
        int is_dead_distance_judgment;      // �ǂ̂��炢���ꂽ��A�E�g���̒l

        ci::Ray camera_ray;
    };



    class TestDraw : public GameObject
    {
    public:

        void setup()override
        {
            hit_sphere_y = 0.0f;
            Params->addParam("hit_sphere_y", &hit_sphere_y).step(0.01f);
        }
        void update()override
        {

        }
        void draw()override
        {
            ci::Vec3f pos = player->getStandRay().calcPosition(player->getStandRayIntersection());
            ci::gl::drawSphere(pos, 0.3f);
            ci::gl::drawSphere(player->getStandRay().calcPosition(hit_sphere_y), 0.3);

            pos = player->getStandRay().getOrigin();
            ci::gl::drawVector(pos, pos + player->getStandRay().getDirection());

            pos = player->getCameraRay().getOrigin();
            ci::gl::drawVector(pos, pos + player->getCameraRay().getDirection());

        }
        void laterDraw()override
        {

        }

        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }
        void setCamera(std::shared_ptr<tol::Camera> camera_) { camera = camera_; }

    private:

        std::shared_ptr<tol::Player> player;
        std::shared_ptr<tol::Camera> camera;


        float hit_sphere_y;

    };
}

