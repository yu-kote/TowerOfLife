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
        }

        void draw()override
        {
            ci::gl::translate(-scale / 2);
            ci::gl::scale(scale);
            drawRect();
        }

        void update()override
        {
            if (current_select == is_select)return;
            current_select = is_select;
            Easing.kill(scale);
            if (is_select)
                Easing.add(scale, select_scale, 10, EaseType::QuartOut);
            else
                Easing.add(scale, default_scale, 10, EaseType::QuartOut);
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
        }

        void draw()override
        {
            ci::gl::translate(-scale / 2);
            ci::gl::scale(scale);
            drawRect();
        }

        void update()override
        {
            if (current_select == is_select)return;
            current_select = is_select;
            Easing.kill(scale);
            if (is_select)
                Easing.add(scale, select_scale, 10, EaseType::QuartOut);
            else
                Easing.add(scale, default_scale, 10, EaseType::QuartOut);

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
        void transDraw()override;

        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }

        std::string getSelectButtonName() { return canvas->getSelectButtonName(); }

    private:

        std::shared_ptr<tol::Player> player;

    private:

        std::shared_ptr<ContinueBackGround> background;
        std::shared_ptr<ContinueCanvas> canvas;

        bool current_active;
    };
}