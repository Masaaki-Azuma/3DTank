#include <GSgame.h>
#include "IScene.h"
#include "PlayScene.h"

class MyGame : public gslib::Game
{
public:
	void start() override
	{
		scene_ = new PlayScene{};
		scene_->start();
	}
	void update(float delta_time) override
	{

	}
	void draw() override
	{
		scene_->draw();
	}
	void end() override
	{
		delete scene_;
	}

private:
	IScene* scene_;
};


int main()
{
	return MyGame().run();
}