#include"SquareMatrix.h"
#include"SquareMatrixController.h"

int main()
{
    std::string PATH ="res/input.txt";
    std::string OUTPUT_PATH = "res/output.txt";
	SquareMatrix<int > a;
	SquareMatrix<int> b;

	#ifndef _WIN32
	   PATH = "../../" + PATH;
	   OUTPUT_PATH = "../../" + OUTPUT_PATH;
    #endif
	SquareMatrixController::read_from_file(PATH, a, FIRST_MATRIX);
	SquareMatrixController::read_from_file(PATH, b, SECOND_MATRIX);
	std::cout << a;
	std::cout << std::endl;
	std::cout << b;
	std::cout << std::endl;
	a *= b;
	std::cout << a;
	SquareMatrixController::write_to_file(OUTPUT_PATH, a);
	std::cout << "program completed successfully." << std::endl;
	return 0;
}
