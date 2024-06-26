#ifndef SHARED_POINTER_HPP
#define SHARED_POINTER_HPP
#include <iostream>
enum class kSharedPointerType { kArray, kObject };

using namespace std;
template <typename T>
class SharedPointer {
 public:
   SharedPointer(T* address,
                 kSharedPointerType type = kSharedPointerType::kObject)
   {
  holder_ = address;
  type_ = type;
  ref_count_ = new unsigned int(0);
   };
   ~SharedPointer()
  {
  if(ref_count_ != nullptr)  
   {  
   if(*ref_count_ == 0)
    {
   if(type_ == kSharedPointerType::kArray) 
       delete[] holder_;
    else  
       delete   holder_;
    delete  ref_count_;
    ref_count_ = nullptr;
    holder_ = nullptr;
    }
    else
       *ref_count_ = *ref_count_ - 1;
  }
  };
   SharedPointer(const SharedPointer<T>& source)
   {
   holder_ = source.holder_;
   ref_count_ = source.ref_count_;
   type_ = source.type_;
   if(source.ref_count_ != nullptr)
       *source.ref_count_ = *source.ref_count_ + 1;
   };
   SharedPointer<T>& operator=(const SharedPointer<T>& source)
   {
   if(this == &source) return *this;
   if(this->ref_count_ != nullptr)
   {
      if(*this->ref_count_ !=0 ) *this->ref_count_= *this->ref_count_ - 1;
      else
      {
        if(type_ == kSharedPointerType::kArray) 
           delete[] holder_;
        else  
           delete   holder_;
       delete  ref_count_;     
      } 
   }  
   this->holder_ = source.holder_;
   this->ref_count_ = source.ref_count_;
   this->type_ = source.type_;
   *this->ref_count_ = *this->ref_count_ + 1;
   return *this;
   }

  // Provided, do not modify!
  SharedPointer() = default;
  T& operator*() { return *holder_; }
  T* operator->() { return holder_; }
  const T* operator->() const { return holder_; }
  T* Get() { return holder_; }
  const T* Get() const { return holder_; }
  unsigned int UseCount() const {
    return (ref_count_ != nullptr) ? *ref_count_ : 0;
  }
bool b_newed=false;
 private:
  T* holder_ = nullptr;
  kSharedPointerType type_ = kSharedPointerType::kObject;
  unsigned int* ref_count_ = nullptr;
 
};

// non-member helper function declarations

// non-member helper function definitions

// member function definitions

#endif