#ifndef ASSETS_H_
#define ASSETS_H_

/* 命名規則は以下のようにしてみる
* "リソース種別_(使用シーン)_リソース名"
* リソース名では"_"は使わず、パスカルケースで記述する
*/

//テクスチャ
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
	Texture_RedCurtain,
};

//メッシュ
enum
{
	Mesh_Player,
	Mesh_Enemy,
	Mesh_CannonBall,
	Mesh_TargetSign,

};

//オクツリー
enum
{
	Octree_Mesh,
	Octree_Collide,
};
#endif//!ASSETS_H_
