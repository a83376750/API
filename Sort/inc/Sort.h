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
	//ֱ�Ӳ��������㷨  
	void insertSort()const;
	//�۰���������㷨  
	void binaryInsertSort()const;
	//ϣ�������㷨  
	void shellSort(int dk[], const int& count)const;
	//ð�������㷨  
	void bubbleSort()const;
	//���������㷨  
	void quickSort()const;
	//��ʾ����Ԫ��
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
