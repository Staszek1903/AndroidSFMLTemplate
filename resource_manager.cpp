#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include "resource_getter.h"
#include "singleton.hpp"

class ResourceManager : public Singleton
{
	ResourceManager();
	virtual ~ResourceManager();
	friend class Singleton:
	
public:

	RESOURCE(int, elo)
	
		
};

#endif	