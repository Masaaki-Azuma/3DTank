#include "PlayScene.h"
#include <gslib.h>

void PlayScene::start()
{
	//gsLoadTexture(0, "Assets/test.png");
	gsLoadMesh(0, "Assets/tank.mshb");
	gsLoadMesh(1, "Assets/cannon_ball.mshb");
}

void PlayScene::update(float delta_time)
{
}

void PlayScene::draw() const
{
	//ƒ^ƒ“ƒN‚Ì•`‰æ
	glPushMatrix();
	glMultMatrixf(GSmatrix4::translate(GSvector3{ 0.0f, 0.0f, 0.0f }));
	gsDrawMesh(0);
	glPopMatrix();
	//–CŠÛ‚Ì•`‰æ
	glPushMatrix();
	glMultMatrixf(GSmatrix4::translate(GSvector3{ 0.0f, 0.0f, 20.0f }));
	gsDrawMesh(1);
	glPopMatrix();
}

void PlayScene::end()
{
	//gsDeleteTexture(0);
	gsDeleteMesh(0);
	gsDeleteMesh(1);
}
