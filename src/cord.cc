#include "cord.hpp"
#include <string_view>

#include <stdexcept>
#include <stack>
#include "cord_utilities.hpp"
using namespace std;

Cord::Cord(std::string_view sv)
{ size_t i=0;
  data_ = new char[sv.size()+1];
  //copy sv to data_
  for(i=0;i<sv.size();i++)
      data_[i] = sv[i];
  data_[i] = 0; //end flag   
  length_ = sv.size();
}
Cord::~Cord()
{
   if(data_ != nullptr) 
   {
     delete[] data_; 
     data_ = nullptr;
   }
}
SharedPointer<char> Cord::ToString() const
{  
   char *p_ch = new char[length_+1]; 
   size_t i=0;
   size_t cnt=0,cnt1=0;
   std::stack<const Cord*>  s_stack;
   const Cord  *p_left;
   const Cord  *p_right;
   const Cord  *p_center;
   p_center = this;
   s_stack.push(p_center); 
   cnt++;
   while (!s_stack.empty()) {
        p_center = s_stack.top(); s_stack.pop();
        p_left = p_center->left_.Get(); 
        p_right = p_center->right_.Get(); 
        if (p_right)
           { s_stack.push(p_right); cnt++;}
        if (p_left)
           { s_stack.push(p_left); cnt++;}
        else
        {
         size_t j=0;
         cnt1++;
         while(p_center->data_[j]) p_ch[i++] = p_center->data_[j++];
        }
    }
   p_ch[i] = 0;//end flag 
   SharedPointer<char> ch_str(p_ch,kSharedPointerType::kArray);  
   std::cout << "Total cord " << cnt;
   std::cout << "Total leaf cord " << cnt1 <<std::endl;
   return ch_str;
}