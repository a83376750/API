#pragma once
#include <mutex>
#include <iostream>

template<class T,size_t len>
class Sort
{
public:
	Sort();
	~Sort();

public:
	//直接插入排序算法  
	void insertSort()const;
	//折半插入排序算法  
	void binaryInsertSort()const;
	//希尔排序算法  
	void shellSort(int dk[], const int& count)const;
	//冒泡排序算法  
	void bubbleSort()const;
	//快速排序算法  
	void quickSort()const;
	//显示所有元素
	void show()const;

	inline void swap(T &l, T &r)const;
private:
	T		*pb_;
	size_t	len_;
};

template<class T, size_t len>
Sort<T, len>::Sort()
{

}

template<class T, size_t len>
Sort<T, len>::~Sort()
{

}

template<class T, size_t len>
void Sort<T, len>::swap(T &l, T &r) const
{

}

template<class T, size_t len>
void Sort<T, len>::show() const
{

}

template<class T, size_t len>
void Sort<T, len>::quickSort() const
{

}

template<class T, size_t len>
void Sort<T, len>::bubbleSort() const
{

}

template<class T, size_t len>
void Sort<T, len>::shellSort(int dk[], const int& count) const
{

}

template<class T, size_t len>
void Sort<T, len>::binaryInsertSort() const
{

}

template<class T, size_t len>
void Sort<T, len>::insertSort() const
{

}
