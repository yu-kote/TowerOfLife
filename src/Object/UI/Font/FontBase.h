#pragma once
#include "../UIBase.h"


namespace tol
{
    class FontBase : public tol::UIBase
    {
    public:
        FontBase();
        FontBase(const std::string& font_name, const float& size);

        void setFont(const std::string& font_name, const float& size);
        void setFontFromAsset(const std::string& file_name, const float& size);

        // •¶Žš•`‰æ
        void drawFont();

    protected:

        ci::Font font;
        std::string drawstring;

    };
}
