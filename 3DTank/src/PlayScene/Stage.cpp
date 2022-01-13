#include "Stage.h"
#include <string>
#include "Figure/BoundingSphere.h"
#include "Figure/Line.h"
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
	/*gsLoadOctree(mesh_, "Assets/stage_mesh.oct");
	gsLoadOctree(collider_, "Assets/stage_collide.oct");*/
	//ステージメッシュをロード
	std::string file_name = "Assets/Stage/Mesh/stage_mesh";
	file_name += std::to_string(stage);
	file_name += ".oct";
	gsLoadOctree(mesh_, file_name.c_str());
	//ステージコライダーをロード
	file_name = "Assets/Stage/Collider/stage_collide";
	file_name += std::to_string(stage);
	file_name += ".oct";
	gsLoadOctree(collider_, file_name.c_str());
}

void Stage::clear()
{
	//ステージを解放
	gsDeleteOctree(mesh_);
	gsDeleteOctree(collider_);
}

void Stage::draw() const
{
	gsDrawSprite2D(Texture_Background, NULL, NULL, NULL, NULL, NULL, NULL);
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
