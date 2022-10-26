#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Array.h"
#include "ArrayInt.h"

struct comp
{
	bool operator()(const std::string& a, const std::string& b)
	{
		if (a.compare(b) > 0) return true;
		return false;
	}
};

int main()
{
	ArrayInt val;
	for(int i = 0; i < 10; ++i)
		val +=i,
	std::cout << val.getCap() << " " << val.getSize() << std::endl;

	val -= 3;
	val.InsertAt(3, 3);
	std::cout << val;
	std::cout << val.getCap() << " " << val.getSize() << std::endl;

	return 0;

	Array<int> iv;
	std::cin >> iv;

	iv - 3;
	std::cout << iv.getCap() << " " << iv.getSize() << std::endl;

	Array<int> ivecCopy;
	ivecCopy = iv;
	ivecCopy += 0;

	std::cout << ivecCopy << std::endl;
	std::cout << ivecCopy.getCap() << " " << ivecCopy.getSize() << std::endl;

	int minIndex = iv.FindMinIndex();
	if (minIndex >= 0) {
		std::cout << iv[minIndex];
	}
	else {
		std::cout << "Array is empty";
	}

	iv.Sort();

	std::cout << "Sorted: " << iv << std::endl;
	std::cout << iv.getCap() << " " << iv.getSize() << std::endl;
	Array<std::string> ivec;

	ivec += "Banana";
	ivec += "Zangar";
	ivec += "stupid";
	ivec += "1";
	ivec += "a";

	std::cout << ivec << std::endl;
	std::cout << ivec[ivec.FindMaxIndex(comp())] << std::endl;
	std::cout << " " << ivec.getCap() << " " << ivec.getSize() << std::endl;
	
	//ivec.Sort();


	return 0;
}