#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <vector>
#include "Component.h"

class System
{
public:
    System();
	~System();
protected:
	std::vector<Component *> components;
	virtual void addComponent(Component * ) = 0;

public:

};

#endif