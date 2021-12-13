#ifndef ISCENE_H_
#define ISCENE_H_

class IScene
{
public:
	virtual ~IScene() = default;
	virtual void start() = 0;
	virtual void update(float delta_time) = 0;
	virtual void draw() const = 0;
	virtual void end() = 0;

	//シーンが終了したか？
	virtual void is_end() const = 0;
};

#endif//!ISCENE_H_
