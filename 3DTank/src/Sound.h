#ifndef SOUND_H_
#define SOUND_H_

/* 命名規則は以下のようにしてみる
* "リソース種別_使用シーン_リソース名"
* リソース名では"_"は使わず、パスカルケースで記述する
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