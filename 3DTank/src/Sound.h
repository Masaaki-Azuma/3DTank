#ifndef SOUND_H_
#define SOUND_H_

/* �����K���͈ȉ��̂悤�ɂ��Ă݂�
* "���\�[�X���_�g�p�V�[��_���\�[�X��"
* ���\�[�X���ł�"_"�͎g�킸�A�p�X�J���P�[�X�ŋL�q����
*/

//SE
enum
{
	Se_CursorMove,
	Se_Curtain,
	Se_ChangeStage,
	Se_StartStage,
	Se_ClearStage,
	Se_MissStage,
	Se_Bomb,
	Se_TankShoot,
	Se_HitEnemy,
	Se_PlayerMove,
	Se_EnemyMove,
};

//BGM
enum
{
	Music_Title,
	Music_Battle,
};
#endif//!SOUND_H_