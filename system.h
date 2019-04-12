#ifndef SYSTEM_H_
#define SYSTEM_H

class BaseSystem
{
public:
	BaseSystem();
};

template<class S>
class System : public BaseSystem
{
public:
	System();
};

#endif