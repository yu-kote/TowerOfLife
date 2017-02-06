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
	// �����̌���
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
	// ���C�g��L���ɂ���
	gl::enable(GL_LIGHTING);
	gl::enable(GL_NORMALIZE);
	light->enable();
}
void Light::Off()
{
	// ���C�g�I�t
	gl::disable(GL_LIGHTING);
	gl::disable(GL_NORMALIZE);
	light->disable();
}



void Light::directionalLightSetup()
{
	//   �`���ƊǗ��ԍ�(0~7)��^����
	light = new gl::Light(gl::Light::DIRECTIONAL, 0);
	// �����̐F
	light->setAmbient(Color(0.0f, 0.0f, 0.0f));
	// �g�U���̐F
	light->setDiffuse(Color(0.8f, 0.8f, 0.8f));
	// ���ʌ��̐F
	light->setSpecular(Color(0.5f, 0.5f, 0.5f));
	// �����̌���

	light->setDirection(directionallight_direction);
}

void Light::pointLightSetup()
{
	// �_�����̏ꍇ
	light = new gl::Light(gl::Light::POINT, 1);

	// �����̐F
	light->setAmbient(Color(0.0f, 0.0f, 0.0f));
	// �g�U���̐F
	light->setDiffuse(Color(0.8f, 0.8f, 0.8f));
	// ���ʌ��̐F
	light->setSpecular(Color(0.5f, 0.5f, 0.5f));

	// �ʒu
	light->setPosition(Vec3f(400, 0, 0));

	// �����W����ݒ�
	// 
	// f = 1/(C + Ld + Qd^2)
	// 
	// C ConstantAttenuation
	// L LinearAttenuation
	// Q QuadraticAttenuation
	// d �Ώۂ܂ł̋���
	// 
	// C,L,Q ���ꂼ��0�ȏ�̒l���w��(0���Z���N���Ȃ��悤��!!)
	// 
	light->setAttenuation(0.0f,        // ConstantAttenuation
						  0.5f,        // LinearAttenuation
						  0.0f);       // QuadraticAttenuation
}

void Light::spotLightSetup()
{
	// �X�|�b�g���C�g�̏ꍇ
	light = new gl::Light(gl::Light::SPOTLIGHT, 0);

	// �����̐F
	light->setAmbient(Color(0.0f, 0.0f, 0.0f));
	// �g�U���̐F
	light->setDiffuse(Color(0.8f, 0.8f, 0.8f));
	// ���ʌ��̐F
	light->setSpecular(Color(0.5f, 0.5f, 0.5f));

	// �ʒu
	light->setPosition(Vec3f(0.0f, 0.0f, 0.0f));

	// �����̌���
	light->setDirection(Vec3f(0.0f, 0.0f, 1.0f));

	// �����W����ݒ�
	// 
	// f = 1/(C + Ld + Qd^2)
	// 
	// C ConstantAttenuation
	// L LinearAttenuation
	// Q QuadraticAttenuation
	// d �Ώۂ܂ł̋���
	// 
	// C,L,Q ���ꂼ��0�ȏ�̒l���w��(0���Z���N���Ȃ��悤��!!)
	// 
	light->setAttenuation(0.0f,        // ConstantAttenuation
						  0.5f,        // LinearAttenuation
						  0.0f);       // QuadraticAttenuation

									   // �P�x�̕��U� (0~128) �l���傫���ƃ{������������ۂɂȂ�
	light->setSpotExponent(10.0f);
	// ���ˊp�x (0~90)
	light->setSpotCutoff(5.0f);
}

void Light::shutdown()
{
	delete light;
}
