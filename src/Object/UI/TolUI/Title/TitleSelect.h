#pragma once
#include "../../TextureRenderer/TextureRenderer.h"
#include "../../../../Tol/TolGameDataManager.h"
#include "../../../../Utility/Easing/Ease.h"
#include "../../../../Task/SoundManager.h"


namespace tol
{
    class TitleBackGround : public TextureRenderer
    {
    public:
        TitleBackGround()
        {
        }

        void setup()override
        {
            alpha = 0.0f;

            Easing.add(alpha, 0.6f, 60, EaseType::BackIn);
        }
        void update()override
        {
            color->setColor(0, 0, 0, alpha);
        }
        void transDraw()override
        {
            ci::gl::drawSolidRect(ci::Rectf(0,
                                            0,
                                            ci::app::getWindowSize().x,
                                            ci::app::getWindowSize().y));
        }

    private:
        float alpha;
    };

    class TitleLogo : public TextureRenderer
    {
    public:
        TitleLogo() :
            TextureRenderer("TitleLogo")
        {
            transform.scale = ci::Vec3f(1000, 250, 0);
            transform.position = -transform.scale / 2;

            transform.position.x += 30;
            transform.position.y -= 180;

        }

        void setup()
        {

        }
        void draw()override
        {
            drawRect();
        }
    };
    class TitlePlayButton : public TextureRenderer
    {
    public:
        TitlePlayButton() :
            TextureRenderer("GotoPlayButton")
        {
            is_select = true;
            current_select = is_select;
            transform.scale = ci::Vec3f(400, 200, 0);
            scale = ci::Vec3f::one() * 1.3f;
            select_scale = ci::Vec3f::one() * 1.3f;
            default_scale = ci::Vec3f::one();
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
            Easing.add(scale, scale * 1.1f, 60, EaseType::ElasticOut);
        }

        bool is_select;

    private:
        bool current_select;

        ci::Vec3f scale;
        ci::Vec3f select_scale;
        ci::Vec3f default_scale;
    };

    class TitleGachaButton : public TextureRenderer
    {
    public:
        TitleGachaButton() :
            TextureRenderer("GachaButton")
        {
            is_select = false;
            transform.scale = ci::Vec3f(400, 200, 0);
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

    class TitleSelect : public TextureRenderer
    {
    public:
        TitleSelect();

        void setup()override;
        void update()override;
        void transDraw()override;

        std::string getSelectButtonName();

    private:

        std::shared_ptr<TitleLogo> logo;
        std::shared_ptr<TitlePlayButton> play_button;
        std::shared_ptr<TitleGachaButton> gachabutton;

    };

}
