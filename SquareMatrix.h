#ifndef SquareMatrix_H_
#define SquareMatrix_H_

#include<vector>
#include<iostream>

template<typename T = double, unsigned SIZE = 4>
class SquareMatrix
{
public:
	SquareMatrix();
	~SquareMatrix();

	SquareMatrix(const SquareMatrix<T,SIZE>&);
	SquareMatrix<T,SIZE>& operator= (const SquareMatrix<T,SIZE>& rhs);

	SquareMatrix<T,SIZE> operator* (const SquareMatrix<T,SIZE>& rhs);
	void  operator*= (const SquareMatrix<T,SIZE> & rhs);
	const std::vector<T>& operator[] (unsigned index) const;
	std::vector<T>& operator[] (unsigned index);

private:
	std::vector<std::vector<T>> arr;
	template <typename T2, unsigned SIZE> friend  std::ostream& operator << (std::ostream& lhs, const SquareMatrix<T2, SIZE>&rhs);
	template <typename T2, unsigned SIZE> friend  const std::istream& operator >> (std::istream& lhs, SquareMatrix<T2, SIZE>& rhs);
};

template<typename T, unsigned SIZE>
SquareMatrix<T, SIZE>::SquareMatrix() :arr(SIZE)
{
	if (SIZE <= 0) 
		throw std::invalid_argument("value of SquareMatrix size negative or zero.");
	for (unsigned i{ 0 }; i < SIZE; ++i)
		arr[i].resize(SIZE, 0);
}

template<typename T, unsigned SIZE>
SquareMatrix<T, SIZE>::~SquareMatrix()
{
	for (unsigned i{ 0 }; i < SIZE; ++i)
		arr[i].~vector();
	arr.~vector();
}

template<typename T, unsigned SIZE>
SquareMatrix<T, SIZE>::SquareMatrix(const SquareMatrix<T, SIZE>&rhs) : SquareMatrix()
{
	if (this != &rhs)
	{
		for (unsigned i{ 0 }; i < SIZE; ++i)
			for (unsigned j{ 0 }; j < SIZE; ++j)
				this->arr[i][j] = rhs.arr[i][j];
	}
}

template<typename T, unsigned SIZE>
SquareMatrix<T, SIZE> & SquareMatrix<T, SIZE>::operator = (const SquareMatrix<T, SIZE>& rhs)
{
	if (this != &rhs)
	{
		this->~SquareMatrix();
		new (this) SquareMatrix(rhs);
	}
	return *this;
}

template<typename T, unsigned SIZE>
SquareMatrix<T, SIZE> SquareMatrix<T, SIZE>::operator * (const SquareMatrix<T, SIZE>& rhs)
{
	// «наю что дл€ матрицы 4’4 лучше все сделать без циклов, но решил оставить так потому что так компактнее и задача учебна€(соответсвенно быстродействее не основной показатель).
	SquareMatrix<T, SIZE> temp;

	for (unsigned k{ 0 }; k < SIZE; ++k)
		for (unsigned i{ 0 }; i < SIZE; ++i)
			for (unsigned j{ 0 }; j < SIZE; ++j)
				temp.arr[k][i] += this->arr[k][j] * rhs.arr[j][i];
	return temp;
}

template<typename T, unsigned SIZE>
void SquareMatrix<T, SIZE>::operator *= (const SquareMatrix<T, SIZE>& rhs)
{
	(*this) = (*this)*(rhs);
}
template<typename T, unsigned SIZE>
const std::vector<T>& SquareMatrix<T, SIZE>::operator[](unsigned index) const
{
	if (index < 0 || index > SIZE) { throw std::out_of_range("Out of range exception"); _getch(); exit(-1); }
	return arr[index];
}

template<typename T, unsigned SIZE>
std::vector<T>& SquareMatrix<T, SIZE>::operator[](unsigned index)
{
	return const_cast<std::vector<T>&>(
		static_cast<const SquareMatrix<T, SIZE>& >(*this)
		[index]
	);
}

template<typename T, unsigned SIZE>
std::ostream & operator<<(std::ostream& lhs, const SquareMatrix<T, SIZE>& rhs)
{
	for (unsigned i{ 0 }; i < SIZE; ++i)
	{
		for (unsigned j{ 0 }; j < SIZE; ++j)
			lhs << rhs.arr[i][j] << ' ';
		lhs << std::endl;
	}
	return lhs;
}

template<typename T, unsigned SIZE >
const std::istream & operator >> (std::istream&  lhs, SquareMatrix<T, SIZE>& rhs)
{
	for (unsigned i{ 0 }; i < SIZE; ++i)
		for (unsigned j{ 0 }; j < SIZE; ++j)
			lhs >> rhs.arr[i][j];
	return lhs;
}
#endif // !SquareMatrix_H_