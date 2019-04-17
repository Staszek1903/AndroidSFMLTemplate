#ifndef ENTITYSTUFF_H_
#define ENTITYSTUFF_H_

#include <vector>

#include "../Singleton.hpp"
#include "../Console.h"
#include "Component.h"
#include "System.h"

class EntityStuff : public Singleton<EntityStuff>
{
protected:
	EntityStuff();
	~EntityStuff();
	friend class Singleton<EntityStuff>;

private:
	std::vector <System *> systems;
	
public:
	
	template < class S >
	void addSystem();
};

template < class S >
void EntityStuff::addSystem()
{
	systems.push_back(new S());
}

#endif