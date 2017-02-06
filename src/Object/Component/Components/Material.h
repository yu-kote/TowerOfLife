#pragma once
#include "../../Component/Component.h"
#include "cinder/gl/Material.h"


namespace ar {
	class Material : public Component {
	public:

		Material(ci::gl::Material mt_) {
			material = mt_;
		}

		void drawBegin()override {
			material.apply();
		}

		void setMaterial(ci::gl::Material mt_) {
			material = mt_;
		}

	private:

		ci::gl::Material material;

	};

}