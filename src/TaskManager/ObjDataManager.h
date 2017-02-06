#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/TriMesh.h"
#include "cinder/ObjLoader.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

#include <unordered_map>
#include <assert.h>


#define ObjDataGet tol::ObjManager::get()

namespace tol
{
    class ObjManager
    {
    public:
        static ObjManager& get()
        {
            static ObjManager trimeshmanager;
            return trimeshmanager;
        }

        void setup()
        {
            using namespace ci;
            using namespace ci::app;

            // ‚±‚ñ‚ÈŠ´‚¶

            set("Player", "ObjData/player.obj");
            set("obstacle", "ObjData/kirai.obj");
            set("Enemy", "ObjData/enemy.obj");
            set("Boss0", "ObjData/Boss/boss_hidarisita1.obj");
            set("Boss1", "ObjData/Boss/boss_hidarisita2.obj");
            set("Boss2", "ObjData/Boss/boss_hidariue1.obj");
            set("Boss3", "ObjData/Boss/boss_hidariue2.obj");
            set("Boss4", "ObjData/Boss/boss_migisita1.obj");
            set("Boss5", "ObjData/Boss/boss_migisita2.obj");
            set("Boss6", "ObjData/Boss/boss_migiue1.obj");
            set("Boss7", "ObjData/Boss/boss_migiue2.obj");
            set("Boss8", "ObjData/Boss/boss_body.obj");

        }

        ci::TriMesh& find(std::string key_)
        {
            if (mesh.find(key_) == mesh.end())
                assert(!"Not mesh find");
            return mesh.find(key_)->second;
        }


    private:
        void set(std::string _key, std::string _path)
        {
            ci::ObjLoader charaloader = ci::ObjLoader(ci::app::loadAsset(_path));
            ci::TriMesh charactormesh;
            charaloader.load(&charactormesh,
                             boost::logic::indeterminate, boost::logic::indeterminate,
                             false);
            mesh.insert(std::make_pair(_key, charactormesh));
        }
        std::unordered_map<std::string, ci::TriMesh> mesh;
    };
}
