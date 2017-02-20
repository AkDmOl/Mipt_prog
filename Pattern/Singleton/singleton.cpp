#include <iostream>

class Singleton{
	public:
		Singleton(const Singleton&) = delete;
		Singleton &operator=(const Singleton&) = delete;
		Singleton(Singleton&& ) = delete;
		Singleton &operator=(Singleton&&) = delete;

		static Singleton* init(){
			if (Singleton::_instance != NULL){
				std::cout << "second\n";
				return Singleton::_instance;
			}
			else{
				std::cout << "first\n";
				Singleton::_instance = new Singleton();
				return Singleton::_instance;
			};	
		}
		~Singleton(){
			delete _instance;
		}
	private:
		Singleton();
		static Singleton* _instance;
};

inline Singleton::Singleton() { Singleton::_instance = this; };
Singleton* Singleton::_instance = NULL;

int main(){
	Singleton* attempt = Singleton::init();
	Singleton* attempt_2 = Singleton::init();
	Singleton* attempt_3 = Singleton::init();
	std::cout << attempt << "	" << attempt_2 <<"	"<< attempt_3 << "\n";
	return 0;
}
