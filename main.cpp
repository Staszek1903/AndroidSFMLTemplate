
#include "p.h"
#include "menu.h"
#include <SFML/Graphics.hpp>


#include <unistd.h>

int main()
{
    std::cout<<"cur brk "<<sbrk(0)<<std::endl;
    Program p;
    ProgramStage::setWindow(p.get_window());
    ProgramStage::next_stage<Menu>();

    p.run();

    std::cout<<"cur brk "<<sbrk(0)<<std::endl;
	return 0;
}
