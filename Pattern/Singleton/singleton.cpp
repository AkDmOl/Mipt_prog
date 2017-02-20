#include <iostream>

class Singleton{
	public:
		static Singleton* init(){
			if (Singleton::_instance != NULL)
				return Singleton::_instance;
			else{
				Singleton::_instance = new Singleton();
				return Singleton::_instance;
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
	Singleton* attempt_2 = Singleton::init();
	std::cout << attempt << "	" << attempt_2 << "\n";
	return 0;
}
