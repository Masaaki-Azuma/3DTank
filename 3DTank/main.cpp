#include <GSgame.h>
#include "IScene.h"
#include "PlayScene.h"
#include "SceneManager.h"

class MyGame : public gslib::Game
{
public:
	void start() override
	{
		scene_manager_.add("PlayScene", new PlayScene{});
		scene_manager_.change("PlayScene");
	}
	void update(float delta_time) override
	{
		scene_manager_.update(delta_time);
	}
	void draw() override
	{
		scene_manager_.draw();
	}
	void end() override
	{

	}

private:
	SceneManager scene_manager_;
};


int main()
{
	return MyGame().run();
}