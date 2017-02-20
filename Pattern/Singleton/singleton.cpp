#include <iostream>

class Singleton{
	public:
		static Singleton init(){
			if (Singleton::_instance != NULL){
				std::cout << "second\n";
				return *Singleton::_instance;
			}
			else{
				std::cout << "first\n";
				return Singleton();
			};	
		}
	private:
		Singleton();
		static Singleton* _instance;
};

inline Singleton::Singleton() { Singleton::_instance = this; };
Singleton* Singleton::_instance = NULL;

int main(){
	Singleton attempt = Singleton::init();
	Singleton attempt_2 = Singleton::init();
	Singleton attempt_3 = Singleton::init();
	std::cout << &attempt << "	" << &attempt_2 <<"	"<< &attempt_3 << "\n";
	return 0;
}
