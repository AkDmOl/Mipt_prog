#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>

#define TIME 10

class Field{
	public:
		Field(const char* data){
			std::ifstream first_gen(data);
			int len, high;
			first_gen >> _length >> _height;
			//init
			std::vector<bool> tmp(_length);
			for (int i = 0; i < _height; ++i)
				_field.push_back(tmp);
			//birth first gen
			while (!first_gen.eof()){
				int i, j;
				first_gen >> i >> j;
				_field[i][j] = true;
			}		
		}
		void next_gen(){
			std::vector<std::vector<bool> > new_field(_field);
			for (int i = 1; i < _height-1; ++i)
				for (int j = 1; j < _length-1; ++j)
					if(check(i,j))
						new_field[i][j] = true;
					else
						new_field[i][j] = false;
			//boundary lines field
			for (int i = 0; i < _height; i+=_height-1){
//				std::cout << i;
				for (int j = 1; j <_length-1; ++j)
					if (check_boundary(i,j))
						new_field[i][j] = true;
					else
						new_field[i][j] = false;
			}
			for (int j = 0; j < _length; j+=_length-1){
				for (int i = 0; i < _height; ++i)
					if (check_boundary(i,j))
						new_field[i][j] = true;
					else
						new_field[i][j] = false;
			}
			_field = new_field;

		}
		bool check_boundary(int y, int x){
			int life = 0;
			int bound_x, bound_y;
			life -= _field[y][x];
			for (int i = y-1; i <= y+1; ++i){
				bound_y = i;
				if (i == -1)
					bound_y = _height-1;
				if (i == _height)
					bound_y = 0;
				for (int j = x-1; j <= x+1; ++j){
					bound_x = j;
					if (j == -1)
						bound_x = _length-1;
					if (j == _length)
						bound_x = 0;
					if (_field[bound_y][bound_x])
						++life;
				}
			}

			if (_field[y][x] == false){
				if (life == 3)
					return true;
			}
			else{
				if (life == 2 || life == 3)
					return true;
			}
			return false;
		}

		bool check(int y, int x){
			int life = 0;
			life -= _field[y][x];
			for (int i = y-1; i <= y+1; ++i)
				for (int j = x-1; j <= x+1; ++j)
					if (_field[i][j])
						++life;	

			if (_field[y][x] == false){
				if (life == 3)
					return true;
			}
			else{
				if (life == 2 || life == 3)
					return true;
			}
			return false;
		}
		void print_res(){
			for (int i = 0; i < _height; ++i){
				for (int j = 0; j < _length; ++j)
					std::cout << _field[i][j] << " ";
				std::cout << "\n";
			}
		
		}
	private:
		int _height;
		int _length;
		std::vector<std::vector<bool> > _field;
};

int main(){
	Field life_game("first_gen.txt");
	life_game.print_res();
	std::cout << "\n";
//	for (int i = 0; i < TIME; ++i)
		life_game.next_gen();
		life_game.next_gen();
	life_game.print_res();
	return 0;
}
