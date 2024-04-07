#include <iostream>

#include "cord_utilities.hpp"
#include "cord.hpp"
#include <iostream>
SharedPointer<Cord> Con(SharedPointer<Cord> a, SharedPointer<Cord> b)
{
    SharedPointer<Cord> *c = new SharedPointer<Cord>();
   *c =  new Cord("po");
 // SharedPointer<Cord> c =  new Cord("po");
  return ConcatCords(a, *c);
}
int main() {
     /*SharedPointer<Cord> a = new Cord("he");
     SharedPointer<Cord> b = new Cord("llo");
     SharedPointer<Cord> c = ConcatCords(a, b);
     SharedPointer<Cord> d = new Cord("wor");
     SharedPointer<Cord> e = new Cord("ld");
     SharedPointer<Cord> f = ConcatCords(d, e);
     SharedPointer<Cord> g = ConcatCords(c, f);*/
     SharedPointer<Cord> a = new Cord("sse");
     SharedPointer<Cord> b = new Cord("ssion");
     SharedPointer<Cord> c = Con(a, b); 
     auto c_str = c->ToString();
     std::cout << c_str.Get() << std::endl;
    /* SharedPointer<Cord> a = new Cord("sse");
     SharedPointer<Cord> b = new Cord("ssion");
     SharedPointer<Cord> c = ConcatCords(a, b);
     SharedPointer<Cord> d = new Cord("po");
     SharedPointer<Cord> e = ConcatCords(d, c);
     SharedPointer<Cord> f = new Cord("pre");
     SharedPointer<Cord> g = ConcatCords(f, e);
     g = e;
    auto c_str = g->ToString();
    std::cout << c_str.Get() << std::endl;
    auto res = SubString(g, 0, 2);
    auto res_str = res->ToString();
    std::cout << res_str.Get() << std::endl; */
}