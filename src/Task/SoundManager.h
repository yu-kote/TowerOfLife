#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/GainNode.h"
#include "cinder/audio/SamplePlayerNode.h"

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

        void setGain(float value_)
        {
            gain->setValue(value_);
        }
    };

    class SoundManager
    {
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
            //bufferPlayerLoad(ci::app::getAssetPath("SoundData/BufferPlayerResource.txt").string());
            //filePlayerLoad(ci::app::getAssetPath("SoundData/FilePlayerResource.txt").string());
        }

        std::shared_ptr<Sound> find(const std::string& key_)
        {
            if (sound.find(key_) == sound.end())
                assert(!"Not sound name");
            return sound.find(key_)->second;
        }

    private:
        void registerFilePlayerNode(std::string key_, std::string filepath_)
        {
            ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(filepath_));

            ci::audio::FilePlayerNodeRef fileplayer = ctx->makeNode(new ci::audio::FilePlayerNode());
            fileplayer->setSourceFile(source);

            sound.insert(std::make_pair(key_, std::make_shared<Sound>(Sound(fileplayer, ctx))));
        }

        void registerBufferPlayerNode(std::string key_, std::string filepath_)
        {
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


        void allStop()
        {
            for (auto& it : sound)
            {
                it.second->stop();
            }
        }

    private:

        // ­‚µ‚¸‚Â“Ç‚İ‚Ş‚â‚Â‚ªfileplayer
        // ˆê‹C‚É“Ç‚İ‚Ş‚â‚Â‚ªbufferplayer

        std::unordered_map<std::string, std::shared_ptr<Sound>> sound;
        ci::audio::Context* ctx;

    };


}
