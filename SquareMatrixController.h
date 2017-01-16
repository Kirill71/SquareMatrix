#ifndef MATRIX_CONTROLLER_H

#define MATRIX_CONTROLLER_H
#include<fstream>
#include<memory>
#include<conio.h>
#include<time.h>
#include"SquareMatrix.h"


const size_t FIRST_MATRIX = 0;
const size_t SECOND_MATRIX = 37; // ñäâèã óêàçàòåëÿ äëÿ ôóíêöèè seekg äëÿ ñ÷èòûâàíèÿ  âòîðîé ìàòðèöû èç ôàéëà.
const char SPACE = ' ';

class SquareMatrixController
{
private:
	template<typename T,size_t SIZE=4>static void input_or_output(SquareMatrix<T, SIZE>&, bool);
public:
	template<typename T, size_t SIZE=4> static void print( SquareMatrix<T,SIZE>&);
	template<typename T, size_t SIZE=4> static void input(SquareMatrix<T,SIZE>&);
	template<typename T, size_t SIZE=4> static void read_to_file(const std::string&, SquareMatrix<T,SIZE>&, size_t);
	template<typename T, size_t SIZE=4> static void write_to_file(const SquareMatrix<T,SIZE>&);
	template<typename T, size_t SIZE=4> static void random_input(SquareMatrix<T,SIZE>&, size_t, bool=false);
};

template<typename T, size_t SIZE>
void SquareMatrixController::input_or_output(SquareMatrix<T,SIZE>& val, bool io)
{
	for (size_t i(0); i <SIZE; ++i)
	{
		for (size_t j(0); j <SIZE; ++j)
		{
			if (io)  std::cin >> val[i][j]; else std::cout << val[i][j] <<SPACE;
		}
			if(!io) std::cout << std::endl;
	}
}

template<typename T, size_t SIZE>
void SquareMatrixController::print(SquareMatrix<T,SIZE>& val)
{
	input_or_output(val, false);
}

template<typename T, size_t SIZE>
void SquareMatrixController::input(SquareMatrix<T,SIZE>& val)
{
	inputORoutput(val, true);
}

template<typename T, size_t SIZE>
void SquareMatrixController::read_to_file(const std::string& path, SquareMatrix<T,SIZE>& val, size_t seek)
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

template<typename T, size_t SIZE>
void SquareMatrixController::write_to_file(const SquareMatrix<T,SIZE>& val)
{
	auto write = std::make_unique<std::ofstream>("output.txt");
	(*write) << val;
}

template<typename T, size_t SIZE>
void SquareMatrixController::random_input(SquareMatrix<T,SIZE>& val, size_t seed, bool isNegative)
{
	srand((unsigned int)time(NULL));
	for (size_t i (0); i < SIZE; ++i)
	{
		for (size_t j(0); j < SIZE; ++j)
		{
			(isNegative) ? val[i][j] = ((rand() % seed) - (2 * seed)) : val[i][j] = rand() % seed;
		}
	}
}
#endif // !MATRIX_CONTROLLER_H


