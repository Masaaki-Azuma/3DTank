#include "Stage.h"
#include <string>
#include "Figure/BoundingSphere.h"
#include "Figure/Line.h"
#include "Assets.h"

//どのIDを用いて描画するのかを覚えておく
Stage::Stage(GSuint mesh, GSuint collider):
	mesh_{ mesh }, collider_{ collider }, prev_stage_num_{-1}
{
}

Stage::~Stage()
{
	//ステージを解放
	clear();
}

void Stage::load(int stage)
{
	//同じステージだったらロードせず終了
	if (prev_stage_num_ == stage) return;

	//既存のステージを削除する
	clear();
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
	//ロードしたステージ数をキープ
	prev_stage_num_ = stage;
}

void Stage::clear()
{
	//ステージを解放
	gsDeleteOctree(mesh_);
	gsDeleteOctree(collider_);
}

void Stage::draw() const
{
	//背景の描画
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
