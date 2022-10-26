#include <assert.h>
#include <cctype>
#include <random>

#include "ArrayInt.h"

void ArrayInt::Resize(const int size, const int value)
{
	Reserve(size);
	for (int i = m_size; i < size; ++i)
	{
		m_head[i] = value;
	}
	m_size = size;
}

void ArrayInt::Reserve(const int newCap)
{
	if (newCap > m_cap)
	{
		int* newArr = new int[newCap];
		for (int i = 0; i < m_size; ++i)
		{
			newArr[i] = m_head[i];
		}

		delete[] m_head;
		m_head = newArr;
		m_cap = newCap;
	}
}

void ArrayInt::Inverse(int begin, int end)
{
	while (begin < end)
	{
		Swap(m_head[begin], m_head[end]);
		++begin;
		--end;
	}
}

ArrayInt::ArrayInt(const int* arr, const int size)
{
	m_head = new int[size];
	m_cap = m_size = size;
	for (int i = 0; i < size; ++i)
	{
		m_head[i] = arr[i];
	}
}

ArrayInt::ArrayInt(const ArrayInt& arr)
{
	m_size = arr.m_size;
	m_cap = arr.m_cap;
	m_head = new int[arr.m_cap];
	for (int i = 0; i < arr.m_size; ++i)
	{
		m_head[i] = arr.m_head[i];
	}
	for (int i = m_size; i < m_cap; ++i)
	{
		m_head[i] = 0;
	}
}

ArrayInt& ArrayInt::operator=(ArrayInt& arr)
{
	if (this != &arr)
	{
		if (m_size != arr.m_size)
		{
			Resize(arr.m_size);
			for (int i = 0; i < arr.m_size; ++i)
			{
				m_head[i] = arr.m_head[i];
			}
		}

		for (int i = 0; i < m_size; ++i)
		{
			m_head[i] = arr.m_head[i];
		}
	}
	return *this;
}

const int& ArrayInt::operator[](const int index) const
{
	assert(index >= 0 && index < m_size);
	return m_head[index];
}

int& ArrayInt::operator[](const int index)
{
	assert(index >= 0 && index < m_size);
	return m_head[index];
}

void ArrayInt::Sort()
{
	int i, j;
	for (i = 0; i < m_size - 1; i++)
	{
		for (j = 0; j < m_size - i - 1; j++)
		{
			if (m_head[j] < m_head[j + 1])
			{
				Swap(m_head[j], m_head[j + 1]);
			}
		}
	}
}

void ArrayInt::Swap(int& a, int& b)
{
	int t = a; 
	a = b;
	b = t;
}

void ArrayInt::ShiftLeft(const int index, int shift)
{
	shift = (shift >= m_size - index) ? shift % index : shift;
	if (shift == 0) return;
	Inverse(index, index + shift - 1);
	Inverse(index, m_size - 1);
	Inverse(index, m_size - 1 - shift);
}

void ArrayInt::ShiftRight(const int index, int shift)
{
	shift = shift >= m_size - index ? shift % index : shift;
	if (shift == 0) return;
	Inverse(index, m_size - 1);
	Inverse(index, index + shift - 1);
	Inverse(index + shift, m_size - 1);
}

int ArrayInt::FindIndex(const int value) const
{
	for (int i = 0; i < m_size; ++i)
	{
		if (m_head[i] == value)
		{
			return i;
		}
	}
	return -1;
}

int ArrayInt::FindMaxIndex()
{
	if (m_size != 0)
	{
		int maxIndex = 0;
		for (int i = 1; i < m_size - 1; ++i)
		{
			if (m_head[maxIndex] < m_head[i])
			{
				maxIndex = i;
			}
		}
		return maxIndex;
	}
	return -1;
}

int ArrayInt::FindMinIndex()
{
	if (m_size != 0)
	{
		int minIndex = 0;
		for (int i = 1; i < m_size; ++i)
		{
			if (m_head[i] < m_head[minIndex])
			{
				minIndex = i;
			}
		}
		return minIndex;
	}
	return -1;
}

void ArrayInt::Cctn(ArrayInt& arr)
{
	Resize(m_size + arr.m_size);
	int i = m_size;
	for (int j = 0; i < arr.m_size; ++i, ++j)
	{
		m_head[i] = arr.m_head[j];
	}
	for (int j = m_size; j < m_cap; ++j)
	{
		m_head[j] = 0;
	}
}

void ArrayInt::InsertAt(int index, int value)
{
	if (index < 0 || index >= m_size)
	{
		throw std::out_of_range("Attempt to delete an element outside an array");
	}
	int size = m_size;
	Resize(++size);
	m_head[m_size - 1] = value;
	ShiftRight(index, 1);
}

void ArrayInt::operator+=(const int value)
{
	if (!m_size) { Reserve(2); }
	else if (m_size >= m_cap)
	{
		Reserve(2 * m_cap);
	}
	m_head[m_size] = value;
	++m_size;
}

void ArrayInt::operator-=(const int index)
{
	if (index < 0 || index >= m_size)
	{
		throw std::out_of_range("Attempt to delete an element outside an array");
	}

	ShiftLeft(index, 1);
	--m_size;
}

void ArrayInt::operator-(const int value)
{
	int index = FindIndex(value);
	if (index != -1) this->operator-=(index);
}

std::ostream& operator<<(std::ostream& stream, const ArrayInt& arr)
{
	for (int i = 0; i < arr.m_size; ++i)
	{
		stream << arr.m_head[i] << " ";
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, ArrayInt& arr) 
{
	for (int i = 0; i < arr.m_size; ++i)
	{
		stream >> arr.m_head[i];
	}
	return stream;
}

bool ArrayInt::operator==(ArrayInt& arr)
{
	if (m_size != arr.m_size)
	{
		for (int i = 0; i < m_size; i++)
		{
			if (m_head[i] != arr.m_head[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool ArrayInt::operator!=(ArrayInt& arr)
{
	return !(this->operator==(arr));
}

void ArrayInt::RandFill()
{
	std::random_device os_seed;
	std::uniform_int_distribution<int> distribute(1, 50);

	for (int i = 0; i < m_size; ++i)
	{
		m_head[i] = distribute(os_seed);
	}
}

void ArrayInt::RandFillDecr()
{
	std::random_device os_seed;
	std::uniform_int_distribution<int> distribute(1, 50);
	m_head[m_size - 1] = distribute(os_seed);
	for (int i = m_size - 2; i != -1; --i)
	{
		m_head[i] = m_head[i + 1] + distribute(os_seed);
	}
}

void ArrayInt::RandFillIncr()
{
	std::random_device os_seed;
	std::uniform_int_distribution<int> distribute(1, 50);
	m_head[0] = rand() % 50;
	for (int i = 1; i < m_size; ++i)
	{
		m_head[i] = m_head[i - 1] + distribute(os_seed);
	}
}