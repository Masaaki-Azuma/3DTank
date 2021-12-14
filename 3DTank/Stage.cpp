#include "Stage.h"
#include "BoundingSphere.h"
#include "Line.h"
#include "Assets.h"

//�ǂ�ID��p���ĕ`�悷��̂����o���Ă���
Stage::Stage(GSuint mesh, GSuint collider):
	mesh_{ mesh }, collider_{ collider }
{
}

Stage::~Stage()
{
	//�X�e�[�W�����
	clear();
}

void Stage::load(int stage)
{
	//�����̃X�e�[�W���폜����
	clear();
	//stage�ɉ������X�e�[�W��ǂݍ���
	gsLoadOctree(mesh_, "Assets/stage_mesh.oct");
	gsLoadOctree(collider_, "Assets/stage_collide.oct");
}

void Stage::clear()
{
	//�X�e�[�W�����
	gsDeleteOctree(mesh_);
	gsDeleteOctree(collider_);
}

void Stage::draw() const
{
	//�n�`�̕`��
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
