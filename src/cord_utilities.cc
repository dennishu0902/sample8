#include "cord_utilities.hpp"
#include <stack>
#include <string_view>
using namespace std;
SharedPointer<Cord> ConcatCords(SharedPointer<Cord> left_cord,
                                 SharedPointer<Cord> right_cord)
{
   Cord  *p_cord= new Cord();
   p_cord->left_  = left_cord;
   p_cord->right_ = right_cord;
   p_cord->length_ = left_cord.Get()->length_ + right_cord.Get()->length_ ;
   SharedPointer<Cord> scord = SharedPointer<Cord>(p_cord);
   return scord;
}
SharedPointer<Cord> CreateNewCords(SharedPointer<Cord> curr_cord,
                               unsigned int lower_idx,
                               unsigned int upper_idx)
{
      auto c_str = curr_cord->ToString();
      char *p_ch = c_str.Get();
      char *p_ch1= new char[upper_idx - lower_idx + 1];
      unsigned int i=lower_idx,j=0;
      while(i<upper_idx) p_ch1[j++]=p_ch[i++];
      p_ch1[j]= 0;
      std::string_view sv(p_ch1);
      SharedPointer<Cord> left = new Cord(sv);;
      delete[] p_ch1;
      return left;
}
#if 0
SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
                               unsigned int lower_idx,
                               unsigned int upper_idx)
{
  if(curr_cord.Get()->Length() ==0 || upper_idx > curr_cord.Get()->Length() || lower_idx >= upper_idx) 
     throw out_of_range("Out of range");
  if(lower_idx == 0 && upper_idx== curr_cord.Get()->Length())
        return curr_cord;   
  else if(curr_cord.Get()->Left().Get()==nullptr)
  { // leaf
        return CreateNewCords(curr_cord,lower_idx, upper_idx);
  }
  else
  {
    unsigned int l_len = curr_cord.Get()->Left().Get()->Length();
    if(lower_idx >= l_len) 
       return SubString(curr_cord.Get()->Right(),lower_idx - l_len, upper_idx - l_len);
    else if (upper_idx <=  l_len)  
       return SubString(curr_cord.Get()->Left(),lower_idx, upper_idx);
    else
       {
        SharedPointer<Cord> left = SubString(curr_cord.Get()->Left(),lower_idx, l_len);
        SharedPointer<Cord> right= SubString(curr_cord.Get()->Right(),0, upper_idx - l_len); 
        return ConcatCords(left, right);
      } 
  }
}
#else
void push_to_stack(std::stack<SharedPointer<Cord>> &s_stack,std::stack<unsigned int>  &i_stack,
                   SharedPointer<Cord> curr_cord,unsigned int lower_idx,unsigned int upper_idx)
{
  s_stack.push(curr_cord);
  i_stack.push(lower_idx);
  i_stack.push(upper_idx);
                   }
SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
                               unsigned int lower_idx,
                               unsigned int upper_idx)
{
  if(curr_cord.Get()->Length() ==0 || upper_idx > curr_cord.Get()->Length() || lower_idx >= upper_idx) 
     throw out_of_range("Out of range");
  std::stack<SharedPointer<Cord>>   s_stack,a_stack;
  std::stack<unsigned int>          i_stack;
  unsigned int tlower_idx=0,tupper_idx=0;
  SharedPointer<Cord> root_cord,left_cord,right_cord;
  push_to_stack(s_stack,i_stack,curr_cord,lower_idx,upper_idx);
  while(!s_stack.empty())
  {
  root_cord = s_stack.top(); s_stack.pop();
  tupper_idx = i_stack.top();i_stack.pop();
  tlower_idx = i_stack.top();i_stack.pop();
  if(tlower_idx == 0 && tupper_idx== root_cord.Get()->Length()) a_stack.push(root_cord);
  else if(root_cord.Get()->Left().Get()==nullptr)
   a_stack.push(CreateNewCords(root_cord,tlower_idx, tupper_idx));
  else
  {
    unsigned int l_len = root_cord.Get()->Left().Get()->Length();
    if(tlower_idx >= l_len) 
        push_to_stack(s_stack,i_stack,root_cord.Get()->Right(),tlower_idx - l_len,tupper_idx - l_len);
    else if (tupper_idx <=  l_len)  
       push_to_stack(s_stack,i_stack,root_cord.Get()->Left(),tlower_idx,tupper_idx);
    else
   {
       push_to_stack(s_stack,i_stack,root_cord.Get()->Right(),0,tupper_idx - l_len);
       push_to_stack(s_stack,i_stack,root_cord.Get()->Left(),tlower_idx,l_len);
   }
  }
 }
  left_cord = a_stack.top();a_stack.pop(); 
  while(!a_stack.empty())
  {
    right_cord = a_stack.top();a_stack.pop(); 
    left_cord = ConcatCords(right_cord, left_cord);   
  }
  return left_cord;
}
#endif