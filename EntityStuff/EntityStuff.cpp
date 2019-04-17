#include "EntityStuff.h"

EntityStuff::EntityStuff()
{
	
}

EntityStuff::~EntityStuff()
{
	for(auto * s : systems)
	{
		delete s;
	}	
}