#ifndef MATRIX_CONTROLLER_H

#define MATRIX_CONTROLLER_H
#include<fstream>
#include<memory>
#include<time.h>
#include"SquareMatrix.h"

const unsigned FIRST_MATRIX = 0;
#ifdef _WIN32
const unsigned SECOND_MATRIX = 37;
#else
const unsigned SECOND_MATRIX = 36;
#endif

class SquareMatrixController
{
public:
	template<typename T, int SIZE = 4> static void read_from_file(const std::string&, SquareMatrix<T,SIZE>&, unsigned);
	template<typename T, int SIZE = 4> static void write_to_file(const std::string&, const SquareMatrix<T,SIZE>&);
};

template<typename T, int SIZE>
void SquareMatrixController::read_from_file(const std::string& path, SquareMatrix<T,SIZE>& val, unsigned seek)
{
	auto read = std::make_unique<std::ifstream>(path);
	if (!(*read))
	{
		std::cerr << "File could not be opened because file not found." << std::endl;
		exit(1);
	}
	if (seek)
		read->seekg(seek);
	(*read) >> val;
}

template<typename T, int SIZE>
void SquareMatrixController::write_to_file(const std::string& path, const SquareMatrix<T,SIZE>& matrix)
{
	auto write = std::make_unique<std::ofstream>(path);
    (*write) << matrix;
}

#endif // !MATRIX_CONTROLLER_H


