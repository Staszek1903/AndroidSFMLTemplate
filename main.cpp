#include "p.h"
#include <SFML/Graphics.hpp>

#include "console.h"
#include "error_generate.hpp"
#include <vector>
#include <memory.h>
#include <iostream>

int main()
{
   // std::map <size_t,size_t> test;

    //for(int i=0; i<1000; ++i)
    //{
     //   test.insert(std::make_pair(i,i));
    //}

   /* auto dasd = std::make_unique<int[]>(10);
    auto asda = std::make_shared<int>(10);

    std::array<std::shared_ptr <std::string>, 10 > s1;
    s1.at(0) = std::make_shared<std::string>("siemanko");
    std::string * ss = s1.at(0).get();

    for(auto & s : s1){
        s = s1.at(0);
    }

    for(auto & s : s1){
        s.reset();
    }




    std::unique_ptr<std::string> p1, p11;
    p1 = std::make_unique<std::string>("siemaneczko");



    std::string * p2 = p1.get();

    p1.reset();
    std::cout << p2 << " " << p1.get() <<std::endl;

    return 0;
*/
    Program p;
    ProgramStage::next_stage<P>(p.get_window());

    p.run();
	
	return 0;
}
