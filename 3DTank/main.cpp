#include <GSgame.h>
#include "SceneManager.h"
#include "IScene.h"
#include "TitleScene.h"
#include "PlayScene.h"


class MyGame : public gslib::Game
{
public:
	void start() override
	{
		scene_manager_.add("TitleScene", new TitleScene{});
		scene_manager_.add("PlayScene", new PlayScene{});
		scene_manager_.change("TitleScene");
		//scene_manager_.change("PlayScene");
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