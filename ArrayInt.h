#pragma once
#include <iostream>

class ArrayInt
{
private:
	void Resize(const int size, const int value = 0);
	void Reserve(const int newCap);
	void Inverse(int begin, int end);
public:
	ArrayInt() : m_head(nullptr), m_size(0), m_cap(0) { Reserve(2); };
	ArrayInt(const int* arr, const int size);
	ArrayInt(const ArrayInt& arr);
	ArrayInt& operator=(ArrayInt& arr);
	~ArrayInt() { delete[] m_head; }

	int getSize() const { return m_size; }
	int getCap() const { return m_cap; }
	const int& operator[](const int index) const;
	int& operator[](const int index);

	void Sort();
	void Swap(int& a, int& b);
	void ShiftLeft(const int index, int shift);
	void ShiftRight(const int index, int shift);

	int FindIndex(const int value) const;
	int FindMaxIndex();
	int FindMinIndex();

	void Cctn(ArrayInt& arr);											// Concationation of Arrays
	void InsertAt(int index, int value);
	void operator+=(const int value);									// Add element at the end of dynamic array
	void operator-=(const int index);								// Delete element by index
	void operator-(const int value);

	bool operator==(ArrayInt& arr);
	bool operator!=(ArrayInt& arr);

	void RandFill();
	void RandFillIncr();
	void RandFillDecr();

	friend std::ostream& operator<<(std::ostream& stream, const ArrayInt& arr);
	friend std::istream& operator>>(std::istream& stream, ArrayInt& arr);
private:
	int* m_head = nullptr;
	int m_size = 0;
	int m_cap = 0;
};

