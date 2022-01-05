#ifndef BLAST_MORTOR_ENEMY_H_
#define BLAST_MORTOR_ENEMY_H_

#include "Enemy.h"

//”š”­–CŠÛ‚ð•ú‚ÂŒÅ’è–C“GƒNƒ‰ƒX
class BlastMortorEnemy : public Enemy
{
public:
	BlastMortorEnemy(IWorld* world, const GSvector3& position);
protected:
	virtual void move(float delta_time) override;
	virtual void generate_cannon_ball(const GSvector3& position, const GSvector3& destination);
};
#endif//!BLAST_MORTOR_ENEMY_H_

