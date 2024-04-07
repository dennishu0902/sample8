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
SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
                               unsigned int lower_idx,
                               unsigned int upper_idx)
{
  if(curr_cord.Get()->Length() ==0 || upper_idx > curr_cord.Get()->Length() || lower_idx >= upper_idx) 
     throw out_of_range("Out of range");
  if(curr_cord.Get()->Left().Get()==nullptr)
  { // leaf
      if(lower_idx == 0 && upper_idx== curr_cord.Get()->Length())
        return curr_cord;
      else
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
        if((left.Get() == curr_cord.Get()->Left().Get())  && (right.Get() == curr_cord.Get()->Right().Get()))
        {
           return curr_cord;
        }
       else
        {  
         SharedPointer<Cord> result= ConcatCords(left, right);
         return result;
        } 
       } 
  }
}
