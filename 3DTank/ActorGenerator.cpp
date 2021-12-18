#include "ActorGenerator.h"
#include "IWorld.h"
#include "Player.h"
#include "Enemy.h"
#include "LevelImage.h"

ActorGenerator::ActorGenerator(IWorld* world):
	world_{world}
{
}

//�X�e�[�W�ɉ����������\�����ƂɃA�N�^�[�𐶐�
void ActorGenerator::generate(unsigned int stage)
{
	//�S�A�N�^�[���폜����
	world_->clear_actor();

	//�t�@�C�������쐬
	std::string file_name = "Assets/Actor_tables/actor_generate_table" + std::to_string(stage) + ".csv";
	//�t�@�C����ǂݍ���
	actor_generate_table_.load(file_name);
	//�X�e�[�W�ɉ��������@�A�G���̔z�u���s��
	for (int i = 0; i < actor_generate_table_.rows(); ++i) {
		//�����N���X���擾
		std::string name = actor_generate_table_.get(i, 0);
		//�����ʒu�擾
		GSvector3 position{ actor_generate_table_.getf(i, 1), actor_generate_table_.getf(i, 2), actor_generate_table_.getf(i, 3) };
		//�����A�N�^�[
		Actor* actor{ nullptr };
		if (name == "Player") actor = new Player{ world_, position };
		else if (name == "Enemy")  actor = new Enemy{ world_, position };
		//�A�N�^�[�𐶐�
		if (actor)world_->add_actor(actor);
	}

	//�X�e�[�W��񉉏o��ǉ�
	world_->add_actor(new LevelImage{ world_ });

}
