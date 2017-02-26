#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/GainNode.h"
#include "cinder/audio/SamplePlayerNode.h"

#include "../Utility/Json/JsonInfo.h"

#include <unordered_map>

#define SoundGet tol::SoundManager::get()

namespace tol
{
    class Sound
    {
    public:

        ci::audio::SamplePlayerNodeRef player_node;

        ci::audio::GainNodeRef gain;

        Sound(ci::audio::SamplePlayerNodeRef node_, ci::audio::Context* ctx_)
        {
            gain = ctx_->makeNode(new ci::audio::GainNode());

            player_node = node_;
            gain->setValue(1.0f);

            player_node >> gain >> ctx_->getOutput();
        }

        void add(ci::audio::SamplePlayerNodeRef node_)
        {
            player_node = node_;
        }

    public:

        void start()
        {
            player_node->start();
        }
        void stop()
        {
            player_node->stop();
        }
        void disable()
        {
            player_node->disable();
        }
        bool isEnabled()
        {
            return player_node->isEnabled();
        }
        void setLoopEnabled(bool is_loop_)
        {
            player_node->setLoopEnabled(is_loop_);
        }
        bool isLoopEnabled()
        {
            return player_node->isLoopEnabled();
        }

        void setGain(float value_)
        {
            gain->setValue(value_);
        }
    };

    class SoundManager
    {
        // 少しずつ読み込むやつがfileplayer
        // 一気に読み込むやつがbufferplayer
        enum SoundType
        {
            FILE_PLAYER,
            BUFFER_PLAYER
        };

    public:
        static SoundManager& get()
        {
            static SoundManager soundmanager;
            return soundmanager;
        }

        SoundManager()
        {
            ctx = ci::audio::master();
            ctx->enable();
        }

        void setup()
        {
            soundLoadJson("GameData/Sound.json");
        }

        std::shared_ptr<Sound> find(const std::string& key_)
        {
            if (sound.find(key_) == sound.end())
                assert(!"Not sound name");
            return sound.find(key_)->second;
        }

        void allStop()
        {
            for (auto& it : sound)
            {
                it.second->stop();
            }
        }

    private:

        void registerFilePlayerNode(std::string key_, std::string filepath_)
        {
            if (sound.find(key_) != sound.end())return;
            ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(filepath_));

            ci::audio::FilePlayerNodeRef fileplayer = ctx->makeNode(new ci::audio::FilePlayerNode());
            fileplayer->setSourceFile(source);

            sound.insert(std::make_pair(key_, std::make_shared<Sound>(Sound(fileplayer, ctx))));
        }

        void registerBufferPlayerNode(std::string key_, std::string filepath_)
        {
            if (sound.find(key_) != sound.end())return;
            ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(filepath_));

            ci::audio::BufferPlayerNodeRef bufferplayer = ctx->makeNode(new ci::audio::BufferPlayerNode());
            bufferplayer->loadBuffer(source);

            sound.insert(std::make_pair(key_, std::make_shared<Sound>(Sound(bufferplayer, ctx))));
        }

        void filePlayerLoad(std::string filename_)
        {
            std::ifstream soundfile(filename_);

            std::string keytemp;
            std::string pathtemp;
            while (!soundfile.eof())
            {
                soundfile >> keytemp;
                soundfile >> pathtemp;
                registerFilePlayerNode(keytemp, pathtemp);
            }
        }

        void bufferPlayerLoad(std::string filename_)
        {
            std::ifstream soundfile(filename_);

            std::string keytemp;
            std::string pathtemp;
            while (!soundfile.eof())
            {
                soundfile >> keytemp;
                soundfile >> pathtemp;
                registerBufferPlayerNode(keytemp, pathtemp);
            }
        }

        void soundLoadJson(std::string asset_filename)
        {
            if (json.openJson(asset_filename))
            {
                findSoundInfoFromValue(json.root, "FilePlayer", SoundType::FILE_PLAYER);
                findSoundInfoFromValue(json.root, "BufferPlayer", SoundType::BUFFER_PLAYER);
            }
            else
                assert(!"Could not open Sound.json file");
        }

        // サウンドのファイル読む関数
        void findSoundInfoFromValue(const Json::Value& value, const std::string& key, const SoundType& type)
        {
            auto child = value.get(key, value);

            if (!json.isValue(child))
            {
                std::string key;
                std::string path;
                float gain = 1.0f;
                bool is_loop = false;
                for (auto const& keys : value.getMemberNames())
                {
                    if (keys == "Key")
                        key = value[keys].asString();
                    if (keys == "Path")
                        path = value[keys].asString();
                    if (keys == "Loop")
                        is_loop = value[keys].asBool();
                    if (keys == "Gain")
                        gain = value[keys].asFloat();
                }
                if (type == SoundType::FILE_PLAYER)
                    registerFilePlayerNode(key, path);
                if (type == SoundType::BUFFER_PLAYER)
                    registerBufferPlayerNode(key, path);

                sound[key]->setGain(gain);
                sound[key]->setLoopEnabled(is_loop);
            }
            else
            {
                // 再帰してメンバーがいないところまでたどる
                for (auto const& it : child.getMemberNames())
                {
                    findSoundInfoFromValue(child, it, type);
                }
            }
        }

    private:

        std::unordered_map<std::string, std::shared_ptr<Sound>> sound;
        ci::audio::Context* ctx;

        JsonInfo json;
    };


}
