#ifndef ISCENE_H_
#define ISCENE_H_

#include <string>

//シーン抽象インターフェース
class IScene
{
public:
	virtual ~IScene() = default;
	virtual void start() = 0;
	virtual void update(float delta_time) = 0;
	virtual void draw() const = 0;
	virtual void end() = 0;

	//シーンが終了したか？
	virtual bool is_end() const = 0;
	//次のシーン名を取得
	virtual const std::string next() const = 0;
};

#endif//!ISCENE_H_
