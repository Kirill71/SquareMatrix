#ifndef MATRIX_CONTROLLER_H

#define MATRIX_CONTROLLER_H
#include<fstream>
#include<memory>
#include<conio.h>
#include<time.h>
#include"SquareMatrix.h"


const unsigned FIRST_MATRIX = 0;
const unsigned SECOND_MATRIX = 37; // сдвиг указателя для функции seekg для считывания  второй матрицы из файла.
const char SPACE = ' ';

class SquareMatrixController
{
private:
	template<typename T,unsigned SIZE = 4> static void input_or_output(SquareMatrix<T, SIZE>&, bool);
public:
	template<typename T, unsigned SIZE = 4> static void print( SquareMatrix<T,SIZE>&);
	template<typename T, unsigned SIZE = 4> static void input(SquareMatrix<T,SIZE>&);
	template<typename T, unsigned SIZE = 4> static void read_to_file(const std::string&, SquareMatrix<T,SIZE>&, unsigned);
	template<typename T, unsigned SIZE = 4> static void write_to_file(const SquareMatrix<T,SIZE>&);
	template<typename T, unsigned SIZE = 4> static void random_input(SquareMatrix<T,SIZE>&, unsigned, bool=false);
};

template<typename T, unsigned SIZE>
void SquareMatrixController::input_or_output(SquareMatrix<T,SIZE>& val, bool io)
{
	for (unsigned i (0); i <SIZE; ++i)
	{
		for (unsigned j (0); j <SIZE; ++j)
		{
			if (io)  std::cin >> val[i][j]; else std::cout << val[i][j] <<SPACE;
		}
			if(!io) std::cout << std::endl;
	}
}

template<typename T, unsigned SIZE>
void SquareMatrixController::print(SquareMatrix<T,SIZE>& val)
{
	input_or_output(val, false);
}

template<typename T, unsigned SIZE>
void SquareMatrixController::input(SquareMatrix<T,SIZE>& val)
{
	input_or_output(val, true);
}

template<typename T, unsigned SIZE>
void SquareMatrixController::read_to_file(const std::string& path, SquareMatrix<T,SIZE>& val, unsigned seek)
{
	auto read = std::make_unique<std::ifstream>(path);
	if (!(*read))
	{
		std::cerr << "File could not be opened becouse file not found." << std::endl;
		_getch();
		exit(1);
	}
	if (seek)
		read->seekg(seek);
	(*read) >> val;
}

template<typename T, unsigned SIZE>
void SquareMatrixController::write_to_file(const SquareMatrix<T,SIZE>& val)
{
	auto write = std::make_unique<std::ofstream>("output.txt");
	(*write) << val;
}

template<typename T, unsigned SIZE>
void SquareMatrixController::random_input(SquareMatrix<T,SIZE>& val, unsigned seed, bool isNegative)
{
	srand((unsigned)time(NULL));
	for (unsigned i (0); i < SIZE; ++i)
	{
		for (unsigned j(0); j < SIZE; ++j)
		{
			(isNegative) ? val[i][j] = ((rand() % seed) - (2 * seed)) : val[i][j] = rand() % seed;
		}
	}
}
#endif // !MATRIX_CONTROLLER_H


