#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <python2.7/Python.h>

#define TIME 10

int num_threads;

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
			std::vector<std::vector<bool> > new_field;
			std::vector<bool> tmp(_length);
			for (int i = 0; i < _height; ++i)
				new_field.push_back(tmp);

			//init values for multithreading
			int chunk = (_height-1)*(_length-1) / num_threads;
			int h_bound_chunk = 2*_length / num_threads;
			int v_bound_chunk = 2*_height / num_threads;
			
			#pragma omp parallel for collapse(2) schedule(dynamic, chunk)
			for (int i = 1; i < _height-1; ++i)
				for (int j = 1; j < _length-1; ++j)
					if(check(i,j))
						new_field[i][j] = true;
					else
						new_field[i][j] = false;
			
			//boundary lines field
			#pragma omp parallel for collapse(2) schedule(dynamic, h_bound_chunk)
			for (int i = 0; i < _height; i+=_height-1){
//				std::cout << i;
				for (int j = 1; j <_length-1; ++j)
					if (check_boundary(i,j))
						new_field[i][j] = true;
					else
						new_field[i][j] = false;
			}
			#pragma omp parallel for collapse(2) schedule(dynamic, v_bound_chunk)
			for (int j = 0; j < _length; j+=_length-1){
				for (int i = 0; i < _height; ++i)
					if (check_boundary(i,j))
						new_field[i][j] = true;
					else
						new_field[i][j] = false;
			}
			_field =std::move(new_field);

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
		void print_res(int argc, char* argv[]){
			std::ofstream out("res.txt");
			for (int i = 0; i < _height; ++i){
				for (int j = 0; j < _length; ++j)
					if(_field[i][j])
						out << i << "," << j <<"\n";			
			}
			out.close();
			//init value for python graph
		        PyObject *pName, *pModule, *pDict, *pFunc, *pValue;
			if (argc >= 3){
				Py_Initialize();
				PyRun_SimpleString("import sys");
				PyRun_SimpleString("sys.path.append('/home/akdmol/Mipt_prog/Parallel/life_game/')");
				pName = PyString_FromString(argv[1]);
				pModule = PyImport_Import(pName);
				pDict = PyModule_GetDict(pModule);
				pFunc = PyDict_GetItemString(pDict, argv[2]);

				if (PyCallable_Check(pFunc)){
					PyObject_CallObject(pFunc, NULL);
					//free resources
					Py_DECREF(pModule);
					Py_DECREF(pName);
				}
				Py_Finalize();
			}

		
		}
	private:
		int _height;
		int _length;
		std::vector<std::vector<bool> > _field;
};

int main(int argc, char* argv[]){
	Field life_game("first_gen.txt");
	
	num_threads = 3;
	omp_set_num_threads(num_threads);
	double start, end, total;
	start = omp_get_wtime();
//	for (int i = 0; i < TIME; ++i)
		life_game.next_gen();
		life_game.next_gen();	
	end = omp_get_wtime();
	total = end - start;
//	printf("%.8f \n", total);
	life_game.print_res(argc, argv);
	return 0;
}
