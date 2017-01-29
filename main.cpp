#include"SquareMatrix.h"
#include"SquareMatrixController.h"

const std::string FILE_NAME = "input.txt";

int main()
{
	SquareMatrix<int> a;
	SquareMatrix<int> b;
	SquareMatrixController::read_to_file(FILE_NAME, a, FIRST_MATRIX);
	SquareMatrixController::read_to_file(FILE_NAME, b, SECOND_MATRIX);
	SquareMatrixController::print(a);
	std::cout << std::endl;
	SquareMatrixController::print(b);
	std::cout << std::endl;
	a *= b;
	SquareMatrixController::print(a);
	SquareMatrixController::write_to_file(a);
	std::cout << "program completed successfully." << std::endl;
	_getch();
	return 0;
}
