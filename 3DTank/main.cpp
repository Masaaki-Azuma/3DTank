#include <GSgame.h>
#include <GSeffect.h>
#include "SceneManager.h"
#include "TitleScene/TitleScene.h"
#include "PlayScene/PlayScene.h"
#include "TutorialScene/TutorialScene.h"
#include "Screen.h"
#include "Assets.h"

class MyGame : public gslib::Game
{
public:
	MyGame():
		gslib::Game{Screen::Width, Screen::Height, false}
	{

	}
	void start() override
	{
		//�G�t�F�N�g�̏�����
		gsInitEffect();
		//�V�[�����܂����ŗp���郊�\�[�X��ǂݍ���
		gsLoadTexture(Texture_RedCurtain, "Assets/red_curtain.png");

		scene_manager_.add("TitleScene", new TitleScene{});
		scene_manager_.add("PlayScene", new PlayScene{});
		scene_manager_.add("TutorialScene", new TutorialScene{});
		scene_manager_.change("TitleScene");
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
		//�S�V�[�����폜
		scene_manager_.clear();
		//���\�[�X�̉��
		gsDeleteTexture(Texture_RedCurtain);
		//�G�t�F�N�g�̏I��
		gsFinishEffect();
	}

private:
	SceneManager scene_manager_;
};


int main()
{
	return MyGame().run();
}