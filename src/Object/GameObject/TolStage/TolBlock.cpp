#include "TolBlock.h"
#include "../../Component/Components/Material.h"
#include "../../../Task/ObjDataManager.h"

using namespace ci;
using namespace ci::app;


void tol::TolBlock::setup()
{
    gl::Material m = gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                                  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                                  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                                  80.0f,
                                  ci::ColorA(0.2f, 0.2f, 0.2f));
    addComponent<tol::Material>(tol::Material(m));

    mesh = &ObjDataGet.find("Block");
    transform.scale = Vec3f(10, 0.5f, 10);
}

void tol::TolBlock::update()
{
    action->update();

}

void tol::TolBlock::draw()
{
    drawBegin();
    pushModelView();
    componentsDraw();

    //gl::drawCube(Vec3f::zero(), Vec3f::one());
    gl::draw(*mesh);
    popModelView();
    drawEnd();
}

void tol::TolBlock::transDraw()
{

}

float tol::TolBlock::calcMeshIntersection(ci::Ray ray)
{
    Matrix44f m =
        Matrix44f::createTranslation(transform.position) *
        Matrix44f::createRotation(transform.angle)*
        Matrix44f::createScale(transform.scale);
    Matrix44f rm = m.inverted();

    Vec3f dir = rm.transformVec(ray.getDirection());
    ray.setDirection(dir);
    Vec3f origin = rm * ray.getOrigin();
    ray.setOrigin(origin);

    // ��ԏ������ʒu���擾���邽�߂�float�̍ő�l������
    float intersection = std::numeric_limits<float>().max();

    for (int i = 0; i < mesh->getNumTriangles(); i++)
    {
        // �|���S���̎O�p�`�̈ʒu��p��
        Vec3f tri_1, tri_2, tri_3;
        // ���b�V������|���S���̒��_�̈ʒu�����擾
        mesh->getTriangleVertices(i, &tri_1, &tri_2, &tri_3);

        float hit;
        // �|���S���Ƀ��C���������Ă��邩�ǂ����𒲂ׂ�
        // �������Ă���ꍇ�̓��C�̐��`��Ԃ��ꂽ�l������
        if (ray.calcTriangleIntersection(tri_1, tri_2, tri_3, &hit))
        {
            if (intersection > hit)
                intersection = hit;
        }
    }
    return intersection;
}
