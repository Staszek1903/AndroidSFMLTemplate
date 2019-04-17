#include "System.h"

System::System()
{
	
}

System::~System()
{
	for(auto * p : components)
	{
		delete p;
	}
}