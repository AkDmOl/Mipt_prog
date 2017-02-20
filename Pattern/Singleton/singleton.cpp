#include <iostream>

class singleton{
	public:
		static singleton* init(){
			if (!_instance)
				return _instance;
			else{
				_instance = new singleton();
				return _instance;
			}	
		}
	private:
		singleton();
		static singleton* _instance;
}
