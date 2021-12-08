#include <GSgame.h>
#include "PlayScene.h"

class MyGame : public gslib::Game
{
public:
	void start() override
	{
		scene_.start();
	}
	void update(float delta_time) override
	{

	}
	void draw() override
	{
		scene_.draw();
	}
	void end() override
	{

	}

private:
	PlayScene scene_;
};


int main()
{
	return MyGame().run();
}