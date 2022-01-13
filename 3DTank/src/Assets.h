#ifndef ASSETS_H_
#define ASSETS_H_

/* �����K���͈ȉ��̂悤�ɂ��Ă݂�
* "���\�[�X���_(�g�p�V�[��)_���\�[�X��"
* ���\�[�X���ł�"_"�͎g�킸�A�p�X�J���P�[�X�ŋL�q����
*/

//�e�N�X�`��
enum
{
	Texture_Title_Logo,
	Texture_Title_Menu,
	Texture_Tutorial_Board0,
	Texture_Tutorial_Board1,
	Texture_Tutorial_PressXToTitle,
	Texture_Cursor,
	Texture_Background,
	Texture_PressXToBack,
	Texture_PressZ,
	Texture_Stage,
	Texture_Clear,
	Texture_Miss,
	Texture_RedCurtain,
	Texture_Number,
	Texture_SilhouetteBackground,
};

//���b�V��
enum
{
	Mesh_Player,
	Mesh_ImmovableEnemy,
	Mesh_ReflectionEnemy,
	Mesh_MortorEnemy,
	Mesh_BlastMortorEnemy,
	Mesh_ChaseEnemy,
	Mesh_BounceEnemy,
	Mesh_PredictionEnemy,
	Mesh_Enemy,

	Mesh_CannonBall,
	Mesh_PlayerCannonBall,
	Mesh_EnemyCannonBall,
	Mesh_TargetSign,

};

//�I�N�c���[
enum
{
	Octree_Mesh,
	Octree_Collide,
};

//�G�t�F�N�g
enum
{
	Effect_Smoke,
};
#endif//!ASSETS_H_
