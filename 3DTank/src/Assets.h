#ifndef ASSETS_H_
#define ASSETS_H_

/* 命名規則は以下のようにしてみる
* "リソース種別_(使用シーン)_リソース名"
* リソース名では"_"は使わず、パスカルケースで記述する
*/

//アセットID管理ヘッダー

//テクスチャ
enum
{
	Texture_Title_Logo,
	Texture_Title_Menu,
	Texture_Tutorial_Board0,
	Texture_Tutorial_Board1,
	Texture_Tutorial_PressXToTitle,
	Texture_Pause_Board,
	Texture_Pause_ReturnToGame,
	Texture_Pause_ReturnToTitle,
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

//メッシュ
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

//オクツリー
enum
{
	Octree_Mesh,
	Octree_Collide,
};

//エフェクト
enum
{
	Effect_Smoke,
};

//SE
enum
{
	Se_CursorMove,
	Se_Curtain,
	Se_StartStage,
	Se_Bomb,
	Se_HitEnemy,
	Se_TankMove,
};

//BGM
enum
{
	Music_Title,
	Music_Battle,
};

#endif//!ASSETS_H_
