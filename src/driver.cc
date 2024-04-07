#include <iostream>

#include "cord_utilities.hpp"
#include "cord.hpp"
#include <iostream>
int main() {
  #if 0
     SharedPointer<Cord> a = new Cord("he");
     SharedPointer<Cord> b = new Cord("llo");
     SharedPointer<Cord> c = ConcatCords(a, b);
     SharedPointer<Cord> d = new Cord("wor");
     SharedPointer<Cord> e = new Cord("ld");
     SharedPointer<Cord> f = ConcatCords(d, e);
     SharedPointer<Cord> g = ConcatCords(c, f);
     SharedPointer<Cord> h = ConcatCords(a, b);
   #else  
     SharedPointer<Cord> a = new Cord("sse");
     SharedPointer<Cord> b = new Cord("ssion");
     SharedPointer<Cord> c = ConcatCords(a, b);
     SharedPointer<Cord> d = new Cord("po");
     SharedPointer<Cord> e = ConcatCords(d, c);
     SharedPointer<Cord> f = new Cord("pre");
     SharedPointer<Cord> g = ConcatCords(f, e);
    #endif 
    auto c_str = g->ToString();
    std::cout << c_str.Get() << std::endl;
    auto res = SubString(g,2, 4);
    auto res_str = res->ToString();
    std::cout << res_str.Get() << std::endl; 
  //  res = new Cord("po");
}