#include "entitymenager.h"

EntityMenager::EntityMenager()
{
}


EntityMenager::~EntityMenager()
{
	for( BaseSystem * p: systems )
		{delete p;}
		
	for( BaseComponent * c: components )
		{delete c;}
}
	