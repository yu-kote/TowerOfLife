#pragma once
#include "../../TextureRenderer/TextureRenderer.h"
#include "../../../../Tol/TolGameDataManager.h"
#include "../../../GameObject/Player/Player.h"
#include "../../../../Utility/Easing/Ease.h"
#include "../../../../Task/SoundManager.h"


namespace tol
{
    class ContinueBackGround : public TextureRenderer
    {
    public:

        ContinueBackGround();

        void setup()override;
        void update()override;
        void draw()override;

    private:
        float alpha;
    };


    class ContinueInfo : public TextureRenderer
    {
    public:
        ContinueInfo() :
            TextureRenderer("ContinueFont")
        {
            transform.scale = ci::Vec3f(500, 110, 0);
            transform.position = -transform.scale / 2;
            transform.position.y -= 130;
        }
        void draw()override
        {
            drawRect();
        }
    };
    class ContinueYesButton : public TextureRenderer
    {
    public:
        ContinueYesButton() :
            TextureRenderer("ContinueYesButton")
        {
            is_select = true;
            transform.scale = ci::Vec3f(200, 100, 0);
            scale = ci::Vec3f::one() * 1.3f;
            select_scale = ci::Vec3f::one() * 1.3f;
            default_scale = ci::Vec3f::one();
            current_select = is_select;
            time = 0;
        }

        void draw()override
        {
            ci::gl::scale(ci::Vec3f(0.95f + 0.05f  * sin(time), 0.95f + 0.05f  * sin(time), 1));
            ci::gl::translate(-scale / 2);
            ci::gl::scale(scale);

            drawRect();
        }

        void update()override
        {
            if (is_select)
                time += 0.1f;

            if (current_select == is_select)return;
            current_select = is_select;

            Easing.kill(scale);
            if (is_select)
                Easing.add(scale, select_scale, 10, EaseType::QuartOut);
            else
            {
                time = 0;
                Easing.add(scale, default_scale, 10, EaseType::QuartOut);
            }
            SoundGet.find("ContinueSelect")->start();
        }
        void select()
        {
            Easing.add(scale, scale* 1.1f, 60, EaseType::ElasticOut);
        }
        bool is_select;

    private:
        bool current_select;

        ci::Vec3f scale;
        ci::Vec3f select_scale;
        ci::Vec3f default_scale;
        float time;
    };

    class ContinueNoButton : public TextureRenderer
    {
    public:
        ContinueNoButton() :
            TextureRenderer("ContinueNoButton")
        {
            is_select = false;
            transform.scale = ci::Vec3f(200, 100, 0);
            scale = ci::Vec3f::one();
            select_scale = scale * 1.3f;
            default_scale = scale;
            time = 0;
        }

        void draw()override
        {
            ci::gl::scale(ci::Vec3f(0.95f + 0.05f * sin(time), 0.95f + 0.05f * sin(time), 1));
            ci::gl::translate(-scale / 2);
            ci::gl::scale(scale);

            drawRect();
        }

        void update()override
        {
            if (is_select)
                time += 0.1f;

            if (current_select == is_select)return;
            current_select = is_select;

            Easing.kill(scale);
            if (is_select)
                Easing.add(scale, select_scale, 10, EaseType::QuartOut);
            else
            {
                time = 0;
                Easing.add(scale, default_scale, 10, EaseType::QuartOut);
            }

        }
        void select()
        {
            Easing.add(scale, scale* 1.1f, 60, EaseType::ElasticOut);
        }
        bool is_select;

    private:
        bool current_select;

        ci::Vec3f scale;
        ci::Vec3f select_scale;
        ci::Vec3f default_scale;
        float time;
    };

    class ContinueCanvas : public TextureRenderer
    {
    public:
        ContinueCanvas();

        void setup()override;
        void update()override;
        void draw()override;

        std::string getSelectButtonName();

    private:

        std::shared_ptr<ContinueInfo> info;

        std::shared_ptr<ContinueYesButton> yes_button;
        std::shared_ptr<ContinueNoButton> no_button;

    };

    class Continue : public TextureRenderer
    {
    public:
        Continue();

        void setup()override;
        void update()override;
        void draw()override;
        void transDraw()override;

        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }

        std::string getSelectButtonName() { return select_name; }

    private:

        std::shared_ptr<tol::Player> player;

    private:

        std::shared_ptr<ContinueBackGround> background;
        std::shared_ptr<ContinueCanvas> canvas;

        bool current_active;
        std::string select_name;
    };
}