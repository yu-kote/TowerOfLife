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
        TitleBackGround() {}
        void setup()override;
        void update()override;
        void transDraw()override;

    private:
        float alpha;
    };

    class TitleLogo : public TextureRenderer
    {
    public:
        TitleLogo();

        void draw()override
        {
            drawRect();
        }
    };

    class TitlePlayButton : public TextureRenderer
    {
    public:
        TitlePlayButton();

        void update()override;
        void draw()override;
        void select();

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

        std::string getSelectButtonName() { return select_name; }

    private:
        std::string select();

        std::shared_ptr<TitleLogo> logo;
        std::shared_ptr<TitlePlayButton> play_button;
        std::shared_ptr<TitleGachaButton> gachabutton;

        std::string select_name;

    };

}
