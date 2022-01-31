#include "ActorGenerator.h"
#include "IWorld.h"
#include "Actor/Player.h"
#include "Actor/Enemy/Enemy.h"
#include "Actor/Enemy/ImmovableEnemy.h"
#include "Actor/Enemy/ReflectionEnemy.h"
#include "Actor/Enemy/MortorEnemy.h"
#include "Actor/Enemy/ChaseEnemy.h"
#include "Actor/Enemy/BounceEnemy.h"
#include "Actor/Enemy/BlastMortorEnemy.h"
#include "Actor/Enemy/PredictionEnemy.h"

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
		//����y���p�x�擾
		float angleY{ actor_generate_table_.getf(i, 4) };
		//�����A�N�^�[
		Actor* actor{ nullptr };
		if      (name == "Player")           actor = new Player{ world_, position };
		else if (name == "ImmovableEnemy")   actor = new ImmovableEnemy{ world_, position };
		else if (name == "ReflectionEnemy")  actor = new ReflectionEnemy{ world_, position, angleY };
		else if (name == "MortorEnemy")      actor = new MortorEnemy{ world_, position };
		else if (name == "ChaseEnemy")       actor = new ChaseEnemy{ world_, position };
		else if (name == "BounceEnemy")       actor = new BounceEnemy{ world_, position };
		else if (name == "BlastMortorEnemy")       actor = new BlastMortorEnemy{ world_, position };
		else if (name == "PredictionEnemy")       actor = new PredictionEnemy{ world_, position };
		//else if (name == "Enemy")  actor = new Enemy{ world_, position };
		//�A�N�^�[�𐶐�
		if (actor)world_->add_actor(actor);
	}
}
