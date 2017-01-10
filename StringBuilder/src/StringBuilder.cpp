#include "../StringBuilder/inc/StringBuilder.h"
#include <functional>
#include <numeric>

using namespace std;
StringBuilder::StringBuilder()
{

}

StringBuilder::StringBuilder(size_t s)
{
	s_.reserve(s);
}


StringBuilder::~StringBuilder()
{

}

StringBuilder& StringBuilder::append(const char *s)
{
	lock_guard<mutex> l{ mutex_ };
	s_.push_back(s);
	return *this;
}

StringBuilder& StringBuilder::append(char *s)
{
	const char* tmp = s;
	return append(tmp);
}

void StringBuilder::resize(size_t s) 
{
	lock_guard<mutex> l{ mutex_ };
	s_.reserve(s);
}


//+= 0.63s  accumulate 0.49s   500 loops
//+= 2.56s  accumulate 2.38s   10000 loops
string StringBuilder::toString()const
{
	string s;
	s.reserve(s_.size());
	for (auto iter = s_.begin(); iter != s_.end(); ++iter)
		s += *iter;
	return s/*accumulate(s_.begin(), s_.end(), s)*/;
}

//听说在liunx下accumulate在超出一定个数的字符串下，会出问题，windows下暂时无这问题
