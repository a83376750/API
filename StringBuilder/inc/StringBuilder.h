#pragma once
#include <vector>


template<class T>
class StringBuilder
{
public:
	StringBuilder();
	StringBuilder(size_t s);
	~StringBuilder();
	StringBuilder& append(T &Right);
	StringBuilder& append(T *Right);
	StringBuilder& append(const T *Right);

private:
	std::vector<T>	s_;
	std::mutex		mutex_;
};

template<class T>
StringBuilder<T>::StringBuilder()
{
	
}

template<class T>
StringBuilder<T>::StringBuilder(size_t s)
{
	s_.reserve(s);
}


template<class T>
StringBuilder<T>::~StringBuilder()
{

}

template<class T>
StringBuilder<T>& StringBuilder<T>::append(T &Right)
{
	std::lock_guard<std::mutex> l{ mutex_ };
	s_.push_back(Right);
	return *this;
}


template<class T>
StringBuilder& StringBuilder<T>::append(T *Right)
{
	std::lock_guard<std::mutex> l{ mutex_ };
	s_.push_back(*Right);
	return *this;
}


template<class T>
StringBuilder& StringBuilder<T>::append(const T *Right)
{
	std::lock_guard<std::mutex> l{ mutex_ };
	s_.push_back(*Right);
	return *this;
}
