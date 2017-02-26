#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/imageIo.h"

#include "../Utility/Json/JsonInfo.h"

#include <unordered_map>

#define TextureGet tol::TextureManager::get()

namespace tol
{
    class TextureManager
    {
    public:
        static TextureManager& get()
        {
            static TextureManager texturenamager;
            return texturenamager;
        }

        void setup()
        {
            if (json.openJson("GameData/Texture.json"))
                findTextureInfoFromValue(json.root, "Tol");
            else
                assert(!"Could not open Texture.json file");
        }

        ci::gl::TextureRef find(const std::string& findname_)
        {
            if (texture.find(findname_) == texture.end())
            {
                assert(!"Find Texture Missing");
            }
            return texture.find(findname_)->second;
        }

        void loadTextTexture(const std::string& filepath_)
        {
            std::ifstream ifs(filepath_);
            std::string key, path;
            while (!ifs.eof())
            {
                ifs >> key;
                ifs >> path;
                registerTexture(key, path);
            }
        }

        void registerTexture(const std::string& key_, const std::string& filepath_)
        {
            ci::DataSourceRef data_source = ci::app::loadAsset(filepath_);
            ci::ImageSourceRef image_source = loadImage(data_source);
            auto f = ci::gl::Texture::Format();
            //f.setWrap(GL_REPEAT, GL_REPEAT);

            texture.insert(std::make_pair(key_, ci::gl::TextureRef(std::make_shared<ci::gl::Texture>(image_source, f))));
        }

    private:

        // 画像のデータをjsonから読む
        void findTextureInfoFromValue(const Json::Value& value, const std::string& key)
        {
            auto child = value.get(key, value);

            if (!json.isValue(child))
            {
                std::string key;
                std::string path;

                for (auto const& keys : value.getMemberNames())
                {
                    if (keys == "Key")
                        key = value[keys].asString();
                    if (keys == "Path")
                        path = value[keys].asString();
                }
                registerTexture(key, path);
            }
            else
            {
                // 再帰してメンバーがいないところまでたどる
                for (auto const& it : child.getMemberNames())
                {
                    findTextureInfoFromValue(child, it);
                }
            }
        }

        std::unordered_map<std::string, ci::gl::TextureRef> texture;

        JsonInfo json;
    };
}
