#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <memory>

template < class T >
class Singleton
{
protected:
	Singleton(){}
	Singleton(const Singleton&) = delete;
	Singleton & operator= (const Singleton&) = delete;
	
    static std::unique_ptr<T> instance;
public:
	static T& get();
	static void release();
};

 template <class T>
 std::unique_ptr<T> Singleton<T>::instance;// = std::make_unique<T>();
 
 template < class T>
  T& Singleton<T>::get()
  {
    if(!instance) instance = std::make_unique<T>();
  	return *instance;
  }
  
  template < class T >
  void Singleton<T>::release()
  {
    instance.reset();
  }
  
  #endif
