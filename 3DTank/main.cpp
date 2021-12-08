#include <GSgame.h>

class MyGame : public gslib::Game
{
public:
	void start() override
	{
	}
	void update(float delta_time) override
	{

	}
	void draw() override
	{
	}
	void end() override
	{

	}
};


int main()
{
	return MyGame().run();
}