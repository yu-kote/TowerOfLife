#include "Light.h"

using namespace ci;
using namespace ci::app;
using namespace tol;

Light::Light()
{
	setup();
}

Light::~Light()
{
}

void Light::setup()
{
	transform.direction = Vec3f(-1.0f, 0.4f, 0.3f);
	transform.position = Vec3f(-4000.0f, 3000.0f, -4000.0f);

	directionallight_direction = transform.direction;
#if 1
	directionalLightSetup();
#endif
#if 0
	pointLightSetup();
#endif
#if 0
	spotLightSetup();
#endif
}

void Light::update()
{
	light->setPosition(transform.position);
	// 光源の向き
	light->setDirection(transform.direction);

}

void tol::Light::draw()
{
	On();
}

void tol::Light::laterDraw()
{
	Off();
}

void Light::On()
{
	// ライトを有効にする
	gl::enable(GL_LIGHTING);
	gl::enable(GL_NORMALIZE);
	light->enable();
}
void Light::Off()
{
	// ライトオフ
	gl::disable(GL_LIGHTING);
	gl::disable(GL_NORMALIZE);
	light->disable();
}



void Light::directionalLightSetup()
{
	//   形式と管理番号(0~7)を与える
	light = new gl::Light(gl::Light::DIRECTIONAL, 0);
	// 環境光の色
	light->setAmbient(Color(0.0f, 0.0f, 0.0f));
	// 拡散光の色
	light->setDiffuse(Color(0.8f, 0.8f, 0.8f));
	// 鏡面光の色
	light->setSpecular(Color(0.5f, 0.5f, 0.5f));
	// 光源の向き

	light->setDirection(directionallight_direction);
}

void Light::pointLightSetup()
{
	// 点光源の場合
	light = new gl::Light(gl::Light::POINT, 1);

	// 環境光の色
	light->setAmbient(Color(0.0f, 0.0f, 0.0f));
	// 拡散光の色
	light->setDiffuse(Color(0.8f, 0.8f, 0.8f));
	// 鏡面光の色
	light->setSpecular(Color(0.5f, 0.5f, 0.5f));

	// 位置
	light->setPosition(Vec3f(400, 0, 0));

	// 減衰係数を設定
	// 
	// f = 1/(C + Ld + Qd^2)
	// 
	// C ConstantAttenuation
	// L LinearAttenuation
	// Q QuadraticAttenuation
	// d 対象までの距離
	// 
	// C,L,Q それぞれ0以上の値を指定(0除算が起きないように!!)
	// 
	light->setAttenuation(0.0f,        // ConstantAttenuation
						  0.5f,        // LinearAttenuation
						  0.0f);       // QuadraticAttenuation
}

void Light::spotLightSetup()
{
	// スポットライトの場合
	light = new gl::Light(gl::Light::SPOTLIGHT, 0);

	// 環境光の色
	light->setAmbient(Color(0.0f, 0.0f, 0.0f));
	// 拡散光の色
	light->setDiffuse(Color(0.8f, 0.8f, 0.8f));
	// 鏡面光の色
	light->setSpecular(Color(0.5f, 0.5f, 0.5f));

	// 位置
	light->setPosition(Vec3f(0.0f, 0.0f, 0.0f));

	// 光源の向き
	light->setDirection(Vec3f(0.0f, 0.0f, 1.0f));

	// 減衰係数を設定
	// 
	// f = 1/(C + Ld + Qd^2)
	// 
	// C ConstantAttenuation
	// L LinearAttenuation
	// Q QuadraticAttenuation
	// d 対象までの距離
	// 
	// C,L,Q それぞれ0以上の値を指定(0除算が起きないように!!)
	// 
	light->setAttenuation(0.0f,        // ConstantAttenuation
						  0.5f,        // LinearAttenuation
						  0.0f);       // QuadraticAttenuation

									   // 輝度の分散具合 (0~128) 値が大きいとボンヤリした印象になる
	light->setSpotExponent(10.0f);
	// 放射角度 (0~90)
	light->setSpotCutoff(5.0f);
}

void Light::shutdown()
{
	delete light;
}
