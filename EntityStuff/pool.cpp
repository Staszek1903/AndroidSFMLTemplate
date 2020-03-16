#include "pool.hpp"

std::vector<stuff::Pools *> stuff::Pools::pools;

void stuff::Pools::resetPools()
{
    for(auto * ptr : pools) ptr->reset();
}

void stuff::Pools::clearPools()
{
    for(auto * ptr : pools) ptr->clear();
}
