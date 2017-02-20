#include <iostream>

class Singleton{
	public:
		static Singleton* init(){
			if (!Singleton::_instance)
				return Singleton::_instance;
			else{
				// ???
				
			}	
		}
		void life(){
			std::cout<<"Hi";
		}
	private:
		Singleton();
		static Singleton* _instance;
};

Singleton* Singleton::_instance = NULL;

int main(){
	Singleton* attempt = Singleton::init();
	attempt->life();
	return 0;
}
