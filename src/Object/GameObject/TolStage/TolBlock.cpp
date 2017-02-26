#include "TolBlock.h"
#include "../../../Task/ObjDataManager.h"
#include "../../../Tol/TolGameDataManager.h"

using namespace ci;
using namespace ci::app;


void tol::TolBlock::setup()
{
    default_material = gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                                    ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                                    ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                                    80.0f,
                                    ci::ColorA(1.2f, 1.2f, 1.2f));

    trans_material = gl::Material(ci::ColorA(0.6f, 0.6f, 0.6f, 0.6f),
                                  ci::ColorA(0.6f, 0.6f, 0.6f, 0.6f),
                                  ci::ColorA(0.6f, 0.6f, 0.6f, 0.6f),
                                  80.0f,
                                  ci::ColorA(0.0f, 0.0f, 0.0f));

    material_z0 = gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                               ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                               ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                               80.0f,
                               ci::ColorA(0.3f, 0.0f, 0.0f));

    material_z1 = gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                               ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                               ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                               80.0f,
                               ci::ColorA(0.3f, 0.3f, 0.0f));

    material_z2 = gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                               ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                               ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                               80.0f,
                               ci::ColorA(0.0f, 0.0f, 0.3f));

    addComponent<tol::Material>(tol::Material(default_material));
    material = getComponent<tol::Material>();

    trans_speed = 0.03f;
    is_transparentize = false;
    mesh = &ObjDataGet.find("Block");
}

void tol::TolBlock::update()
{
    if (!getActive())return;
    if (TolData.using_item != TolItem::GIMMICK_STOP)
        action->update();

    transparentize(material_z0);
    transparentize(material_z1);
    transparentize(material_z2);
    transparentize(material->getMaterial());

}

void tol::TolBlock::draw()
{
    if (!getActive())return;

}

void tol::TolBlock::transDraw()
{
    if (!getActive())return;
    ci::gl::enableAlphaBlending();

    transform.scale = Vec3f(8, 0.55f, 8);
    drawBegin();
    pushModelView();
    componentsDraw();

    gl::draw(*mesh);

    popModelView();
    drawEnd();

    transform.scale = Vec3f(10, 0.5f, 10);
    pushModelView();
    if (block_num >= 0)
        material_z0.apply();
    if (block_num >= 3)
        material_z1.apply();
    if (block_num >= 6)
        material_z2.apply();
    gl::draw(*mesh);
    popModelView();

    ci::gl::disableAlphaBlending();
}

float tol::TolBlock::calcMeshIntersection(ci::Ray ray)
{
    if (!getActive())return std::numeric_limits<float>().max();
    // 自分の逆行列を生成
    Matrix44f m =
        Matrix44f::createTranslation(transform.position) *
        Matrix44f::createRotation(transform.angle)*
        Matrix44f::createScale(transform.scale);
    Matrix44f rm = m.inverted();

    // 引数のrayを、生成した逆行列から見たrayに変更
    Vec3f dir = rm.transformVec(ray.getDirection());
    ray.setDirection(dir);
    Vec3f origin = rm * ray.getOrigin();
    ray.setOrigin(origin);

    // 一番小さい位置を取得するためにfloatの最大値を入れる
    float intersection = std::numeric_limits<float>().max();

    for (int i = 0; i < mesh->getNumTriangles(); i++)
    {
        // ポリゴンの三角形の位置を用意
        Vec3f tri_1, tri_2, tri_3;
        // メッシュからポリゴンの頂点の位置情報を取得
        mesh->getTriangleVertices(i, &tri_1, &tri_2, &tri_3);

        float hit;
        // ポリゴンにレイが当たっているかどうかを調べる
        // 当たっている場合はレイの線形補間された値が入る
        if (ray.calcTriangleIntersection(tri_1, tri_2, tri_3, &hit))
        {
            if (intersection > hit)
                intersection = hit;
        }
    }
    return intersection;
}

void tol::TolBlock::transparentize(ci::gl::Material& material)
{
    if (is_transparentize)
    {
        gl::Material* m = &material;
        m->setAmbient(ColorA(m->getAmbient().r,
                             m->getAmbient().g,
                             m->getAmbient().b,
                             constrain(m->getAmbient().a - trans_speed,
                                       trans_material.getAmbient().a,
                                       1.0f)));

        m->setDiffuse(ColorA(m->getDiffuse().r,
                             m->getDiffuse().g,
                             m->getDiffuse().b,
                             constrain(m->getDiffuse().a - trans_speed,
                                       trans_material.getDiffuse().a,
                                       1.0f)));

        m->setSpecular(ColorA(m->getSpecular().r,
                              m->getSpecular().g,
                              m->getSpecular().b,
                              constrain(m->getSpecular().a - trans_speed,
                                        trans_material.getSpecular().a,
                                        1.0f)));

        m->setEmission(ColorA(m->getEmission().r,
                              m->getEmission().g,
                              m->getEmission().b,
                              constrain(m->getEmission().a - trans_speed,
                                        trans_material.getEmission().a,
                                        1.0f)));
    }
    else
    {
        gl::Material* m = &material;
        m->setAmbient(ColorA(m->getAmbient().r,
                             m->getAmbient().g,
                             m->getAmbient().b,
                             constrain(m->getAmbient().a + trans_speed,
                                       trans_material.getAmbient().a,
                                       1.0f)));

        m->setDiffuse(ColorA(m->getDiffuse().r,
                             m->getDiffuse().g,
                             m->getDiffuse().b,
                             constrain(m->getDiffuse().a + trans_speed,
                                       trans_material.getDiffuse().a,
                                       1.0f)));

        m->setSpecular(ColorA(m->getSpecular().r,
                              m->getSpecular().g,
                              m->getSpecular().b,
                              constrain(m->getSpecular().a + trans_speed,
                                        trans_material.getSpecular().a,
                                        1.0f)));

        m->setEmission(ColorA(m->getEmission().r,
                              m->getEmission().g,
                              m->getEmission().b,
                              constrain(m->getEmission().a + trans_speed,
                                        trans_material.getEmission().a,
                                        1.0f)));
    }
}

ci::ColorA tol::TolBlock::constrainColorA(const ci::ColorA & value,
                                          const ci::ColorA & min,
                                          const ci::ColorA & max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}