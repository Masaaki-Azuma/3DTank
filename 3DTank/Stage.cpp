#include "Stage.h"
#include "BoundingSphere.h"
#include "Line.h"
#include "Assets.h"

//どのIDを用いて描画するのかを覚えておく
Stage::Stage(GSuint mesh, GSuint collider):
	mesh_{ mesh }, collider_{ collider }
{
}

Stage::~Stage()
{
	//ステージを解放
	clear();
}

void Stage::load(int stage)
{
	//既存のステージを削除する
	clear();
	//stageに応じたステージを読み込む
	gsLoadOctree(mesh_, "Assets/stage_mesh.oct");
	gsLoadOctree(collider_, "Assets/stage_collide.oct");
}

void Stage::clear()
{
	//ステージを解放
	gsDeleteOctree(mesh_);
	gsDeleteOctree(collider_);
}

void Stage::draw() const
{
	//地形の描画
	gsDrawOctree(mesh_);
}

bool Stage::collide(const BoundingSphere& sphere, GSvector3* center)
{
	return gsOctreeCollisionSphere(
		gsGetOctree(collider_),
		&sphere.center(), sphere.radius(), center) == GS_TRUE;
}

bool Stage::collide(const Line& line, GSvector3* intersect)
{
	return gsOctreeCollisionLine(
		gsGetOctree(collider_),
		&line.start(), &line.end(), intersect, nullptr
	);
}
