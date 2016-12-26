#pragma once
#include <mutex>
#include <iostream>

class Sort
{
public:
	Sort();
	~Sort();
};

void arraySort(void *pArray, size_t size)
{
	try
	{
		if (!pArray)
			throw std::exception("ø’÷∏’Î");
	}
	catch (const std::exception &e)
	{
		std::cerr << "error:" << e.what() << std::endl;
		exit(-1);
	}
}

