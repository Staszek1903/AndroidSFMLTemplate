#ifndef SINGLETON_H_
#define SINGLETON_H_

template < class T >
class Singleton
{
	Singleton(const Singleton&) = delete;
	Singleton & operator= (const Singleton&) = delete;
	
	static T * instance
public:
	static T& get();
	static void release();
}

 template <class T>
 T* Singleton::instance = nullptr;
 
 template < class T>
  T& Singleton::get()
  {
  	if(!instance) instance = new Singleton<T>();
  	return *instance;
  {
  	
  void Singleton::release()
  {
  	delete instance;