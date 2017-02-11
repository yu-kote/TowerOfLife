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
