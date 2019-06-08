#ifndef SquareMatrix_H_
#define SquareMatrix_H_

#include<vector>
#include<iostream>
#include <algorithm>
#include <thread>
#include <future>

template<typename T = double, int SIZE = 4>
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
	size_t size() const noexcept { return arr.size();}

private:
	std::vector<std::vector<T>> arr;
	template <typename T2, int SIZE2> friend  std::ostream& operator << (std::ostream& lhs, const SquareMatrix<T2, SIZE2>&rhs);
	template <typename T2, int SIZE2> friend  const std::istream& operator >> (std::istream& lhs, SquareMatrix<T2, SIZE2>& rhs);
};

template<typename T, int SIZE>
SquareMatrix<T, SIZE>::SquareMatrix() :arr(SIZE)
{
    static_assert(std::is_arithmetic<T>(), "Arithmetic type required");
	if (SIZE <= 0) 
		throw std::invalid_argument("value of SquareMatrix size negative or zero.");

    std::for_each(arr.begin(), arr.end(),[](std::vector<T>& row)
    {
        row.resize(SIZE, 0);
    });
}

template<typename T, int SIZE>
SquareMatrix<T, SIZE>::~SquareMatrix()
{
    std::for_each(arr.begin(), arr.end(), [](std::vector<T>& row){row.clear();});
	arr.clear();
}

template<typename T, int SIZE>
SquareMatrix<T, SIZE>::SquareMatrix(const SquareMatrix<T, SIZE>&rhs) : SquareMatrix()
{
    static_assert(std::is_arithmetic<T>(), "Arithmetic type required");
	if (this != &rhs)
	{
		for (uint32_t i (0); i < SIZE; ++i)
			for (uint32_t j (0); j < SIZE; ++j)
				arr[i][j] = rhs.arr[i][j];
	}
}

template<typename T, int SIZE>
SquareMatrix<T, SIZE> & SquareMatrix<T, SIZE>::operator= (const SquareMatrix<T, SIZE>& rhs)
{
    static_assert(std::is_arithmetic<T>(), "Arithmetic type required");
	if (this != &rhs)
	{
		new (this) SquareMatrix(rhs);
	}
	return *this;
}

template<typename T, int SIZE>
SquareMatrix<T, SIZE> SquareMatrix<T, SIZE>::operator* (const SquareMatrix<T, SIZE>& rhs)
{
    auto multiple_async = [this, rhs]() {
        SquareMatrix<T, SIZE> temp;
        for (uint32_t k(0); k < SIZE; ++k)
            for (uint32_t i(0); i < SIZE; ++i)
                for (uint32_t j(0); j < SIZE; ++j)
                    temp.arr[k][i] += arr[k][j] * rhs.arr[j][i];

        return temp;
    };
	return std::async(multiple_async).get();
}

template<typename T, int SIZE>
void SquareMatrix<T, SIZE>::operator *= (const SquareMatrix<T, SIZE>& rhs)
{
	*this = *this * rhs;
}
template<typename T, int SIZE>
const std::vector<T>& SquareMatrix<T, SIZE>::operator[](uint32_t index) const
{
	if (index < 0 || index > SIZE) { throw std::out_of_range("Out of range exception"); }
	return arr[index];
}

template<typename T, int SIZE>
std::vector<T>& SquareMatrix<T, SIZE>::operator[](uint32_t index)
{
	return const_cast<std::vector<T>&>(
		static_cast<const SquareMatrix<T, SIZE>& >(*this)
		[index]
	);
}

template<typename T, int SIZE>
std::ostream & operator<<(std::ostream& lhs, const SquareMatrix<T, SIZE>& rhs)
{
	for (uint32_t i (0); i < SIZE; ++i)
	{
		for (uint32_t j (0); j < SIZE; ++j)
			lhs << rhs.arr[i][j] << ' ';
		lhs << std::endl;
	}
	return lhs;
}

template<typename T, int SIZE >
const std::istream & operator >> (std::istream&  lhs, SquareMatrix<T, SIZE>& rhs)
{
	for (uint32_t i (0); i < SIZE; ++i)
		for (uint32_t j (0); j < SIZE; ++j)
			lhs >> rhs.arr[i][j];
	return lhs;
}
#endif // !SquareMatrix_H_