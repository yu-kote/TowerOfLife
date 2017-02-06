#pragma once
#include "../../Component/Component.h"
#include "../../../TaskManager/TextureManager.h"


namespace ar {
	class Texture : public Component {
	public:

		Texture(std::string key_) {
			texture = TextureGet.find(key_);
		}

		void drawBegin()override {
			texture->enableAndBind();
		}

		void drawEnd() override {
			texture->disable();
		}

	private:
		ci::gl::TextureRef texture;
	};


}