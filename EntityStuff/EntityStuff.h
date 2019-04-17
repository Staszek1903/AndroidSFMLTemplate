#ifndef ENTITYSTUFF_H_
#define ENTITYSTUFF_H_

#include <vector>

#include "../Singleton.hpp"
#include "Component.h"
#include "System.h"

class EntityStuff : public Singleton<EntitiStuff>
{
	std::vector <Component *> components;
	std::vector <System *> systems;
};

#endif