#pragma once
#include <iostream>
#include <functional>

//template<typename Head, typename... Tail>
//struct isSameArrayType {
//	static const bool value = (std::is_same_v<Head, Tail> && ...);
//};

template<typename T>
class Array
{
private:
	void Reserve(const int newCap);
	void Resize(const int size, const T& value = T());
	void Inverse(int begin, int end);
public:
	Array() : m_head(nullptr), m_size(0), m_cap(0) { Reserve(2); }
	Array(const int size, const T& value = T());
	Array(const Array<T>& other);
	Array(const T* arr, const int size);
	~Array();

	int getSize() const { return m_size; }
	int getCap()  const { return m_cap; }
	const T& operator[](const int index) const;
	T& operator[](const int index);
	
	void Clear();
	void Sort();
	void Swap(T& a, T& b);
	void ShiftLeft(const int index, int shift);
	void ShiftRight(const int index, int shift);

	void Cctn(Array<T>& arr);											// Concationation of Arrays
	void operator+=(const T& value);									// Add element at the end of dynamic array
	void operator-=(const int index);								// Delete element by index
	void operator-(const T& value);										// Delete element by first value
	void InsertAt(int index, T& value);
	Array<T>& operator=(const Array<T>& arr);
	Array<T>& operator+=(const Array<T>& other);
	Array<T>& operator+(const Array<T>& other) const;

	int FindIndex(const T& value) const;								// Find index of first value
	int FindMaxIndex();
	int FindMinIndex();

	
	bool operator==(Array<T>& arr);
	bool operator!=(Array<T>& arr);
	
	template<typename T>
	friend std::ostream& operator<<(std::ostream & stream, const Array<T>&arr);	
	template<typename T>
	friend std::istream& operator>>(std::istream & stream, Array<T>&arr);	
	

	template<typename Pr>
	int FindMinIndex(Pr Pred)
	{
		return _FindMinIndex(Pred);
	}

	template<typename Pr>
	int FindMaxIndex(Pr Pred)
	{
		return _FindMaxIndex(Pred);
	}
	
	template<typename Pr>
	void Sort(Pr _Pred)	
	{ 
		_Sort(_Pred);
	}
private:
	template<typename Pr>
	void _Sort(Pr Pred)
	{
		int i, j;
		for (i = 0; i < m_size - 1; i++)
		{
			for (j = 0; j < m_size - i - 1; j++)
			{
				if (Pred(m_head[j], m_head[j + 1]))
				{
					Swap(m_head[j], m_head[j + 1]);
				}
			}
		}

	}

	template<typename Pr>
	int _FindMaxIndex(Pr Pred)
	{
		if (m_size != 0)
		{
			int maxIndex = 0;
			for (int i = 1; i < m_size - 1; ++i)
			{
				if (Pred(m_head[maxIndex], m_head[i]))
				{
					maxIndex = i;
				}
			}
			return maxIndex;
		}
		return -1;
	}

	template<typename Pr>
	int _FindMinIndex(Pr Pred)
	{
		if (m_size != 0)
		{
			int minIndex = 0;
			for (int i = 1; i < m_size - 1; ++i)
			{
				if (Pred(m_head[i], m_head[minIndex]))
				{
					minIndex = i;
				}
			}
			return minIndex;
		}
		return -1;
	}

	T* m_head = nullptr;
	int m_size = 0;
	int m_cap = 0;
};

template<typename T>
inline Array<T>::Array(const int size, const T& value)
{
	if (size < 0)
	{
		throw std::out_of_range("The size cannot be negative");
	}
	Resize(size, value);
}

template<typename T>
inline Array<T>::~Array()
{
	delete[] m_head;
	m_head = nullptr;
}

template<typename T>
inline void Array<T>::Cctn(Array<T>& arr)
{
	Resize(m_size + arr.m_size);
	int i = m_size;
	for (int j = 0; i < arr.m_size; ++i, ++j)
	{
		m_head[i] = arr.m_head[j];
	}
}

template<typename T>
Array<T>& Array<T>::operator+=(const Array<T>& other)
{
	Cctn(other);
	return *this;
}

template<typename T>
inline Array<T>& Array<T>::operator+(const Array<T>& other) const
{
	Array<T> sum = *this;
	sum += other;
	return sum;
}

template<typename T>
inline void Array<T>::operator+=(const T& value)
{
	if (m_size <= 1) { Reserve(2); }
	else if (m_size >= m_cap) 
	{
		Reserve(m_cap + m_cap / 2);
	}
	m_head[m_size] = value;
	++m_size;
}

template<typename T>
inline void Array<T>::operator-=(const int index)
{
	if (index < 0 || index >= m_size)
	{
		throw std::out_of_range("Attempt to delete an element outside an array");
	}
	ShiftLeft(index, 1);
	--m_size;
}

template<typename T>
inline void Array<T>::operator-(const T& value)
{
	int index = FindIndex(value);
	if(index != -1) this->operator-=(index);
}

template<typename T>
inline void Array<T>::InsertAt(int index, T& value)
{
	if (index < 0 || index >= m_size)
	{
		throw std::out_of_range("Attempt to delete an element outside an array");
	}
	Resize(1 + m_size);
	m_head[m_size - 1] = value;
	ShiftRight(index, 1);
}

template<typename T>
inline Array<T>& Array<T>::operator=(const Array<T>& arr)
{
	if (this != &arr)
	{
		if (m_size != arr.m_size)
		{
			m_size = 0;
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

template<typename T>
inline void Array<T>::Clear()
{
	delete[] m_head;
	m_cap = 2;
	m_size = 0;
	m_head = new T[m_cap];
}

template<typename T>
inline void Array<T>::Swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

template<typename T>
inline void Array<T>::ShiftLeft(const int index, int shift)
{
	shift = shift >= m_size - index ? shift % index : shift;
	if (!shift) return;
	Inverse(index, index + shift - 1);
	Inverse(index, m_size - 1);
	Inverse(index, m_size  - 1 - shift);
}

template<typename T>
inline void Array<T>::ShiftRight(const int index, int shift)
{

	shift = shift >= m_size - index ? shift % index : shift;
	if (!shift) return;
	Inverse(index, m_size - 1);
	Inverse(index, index + shift - 1);
	Inverse(index + shift, m_size - 1);
}

template<typename T>
inline void Array<T>::Reserve(const int newCap)
{
	if (newCap > m_cap)
	{
		T* newArr = new T[newCap];
		for (int i = 0; i < m_size; ++i)
		{
			newArr[i] = m_head[i];
		}

		delete[] m_head;
		m_head = newArr;
		m_cap = newCap;
	}
}

template<typename T>
inline void Array<T>::Resize(const int size, const T& value)
{
	Reserve(size);
	for (int i = m_size; i < size; ++i)
	{
		m_head[i] = value;
	}
	m_size = size;
}

template<typename T>
inline void Array<T>::Inverse(int begin, int end)
{
	while (begin < end)
	{
		Swap(m_head[begin], m_head[end]);
		++begin;
		--end;
	}
}

template<typename T>
inline Array<T>::Array(const Array<T>& other)
{
	m_size = other.m_size;
	m_cap = other.m_cap;
	m_head = new T[other.m_cap];
	for (int i = 0; i < other.m_size; ++i)
	{
		m_head[i] = other.m_head[i];
	}
	for (int i = m_size; i < m_cap; ++i)
	{
		m_head[i] = T();
	}
}

template<typename T>
inline Array<T>::Array(const T* arr, const int size)
{
	m_head = new T[size];
	m_cap = m_size = size;
	for (int i = 0; i < size; ++i)
	{
		m_head[i] = arr[i];
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Array<T>& arr)
{
	for (int i = 0; i < arr.m_size; ++i)
	{
		stream << arr.m_head[i] << " ";
	}
	return stream;
}

template<typename T>
std::istream& operator>>(std::istream& stream, Array<T>& arr)
{
	if (arr.m_size == 0)
	{
		std::cout << "Set a size: ";
		int size;
		stream >> size;
		arr.Resize(size);
	}

	for (int i = 0; i < arr.m_size; ++i)
	{
		stream >> arr.m_head[i];
	}
	return stream;
}

template<typename T>
inline int Array<T>::FindIndex(const T& value) const
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

template<typename T>
inline T& Array<T>::operator[](const int index)
{
	return m_head[index]; /* это segment fault не exeption, 
						  segment fault не надо ловить. За счет того 
						  что не надо навешивать условия if с++ быстрее*/
}

template<typename T>
inline const T& Array<T>::operator[](const int index) const
{
	return m_head[index];
}

template<typename T>
void Array<T>::Sort()
{
	_Sort(std::less<>());
}

template<typename T>
int Array<T>::FindMaxIndex()
{
	return _FindMaxIndex(std::less<>{});
}

template<typename T>
inline int Array<T>::FindMinIndex()
{
	return _FindMinIndex(std::less<>{});
}

template<typename T>
inline bool Array<T>::operator==(Array<T>& arr)
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

template<typename T>
inline bool Array<T>::operator!=(Array<T>& arr)
{
	return !(this->operator==(arr));
}

