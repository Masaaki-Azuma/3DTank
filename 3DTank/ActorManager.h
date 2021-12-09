#ifndef ACTOR_MANGER_H_
#define ACTOR_MANGER_H_

#include <list>
#include <string>

class Actor;

class ActorManager
{
public:
	ActorManager() = default;
	~ActorManager();

	void update(float delta_time);
	void draw() const;

	void add(Actor* actor);
	void remove();
	void find(const std::string& name) const;
	void find_with_tag(const std::string& tag) const;
	void clear();

private:
	std::list<Actor*> actors_;
};
#endif//!ACTOR_MANGER_H_

