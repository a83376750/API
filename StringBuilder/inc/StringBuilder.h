#pragma once
#include <vector>
#include <list>
#include <mutex>
#include <string>
#include <numeric>

using namespace std;
template<typename chr>
class StringBuilder
{
public:
	typedef basic_string<chr> string_t;

	StringBuilder() = default;
	StringBuilder(size_t s) {	vec_.reserve(s);	};
	~StringBuilder() {	clear();	};

	StringBuilder& append(chr *s)
	{
		lock_guard<mutex> l{ mutex_ };
		vec_.push_back(s);
		return *this;
	}

	StringBuilder& popback()
	{
		lock_guard<mutex> l{ mutex_ };
		vec_.pop_back();
		return *this;
	}

	void clear()
	{
		lock_guard<mutex> l{ mutex_ };
		vec_.clear();
	}

	void resize(size_t s)
	{
		lock_guard<mutex> l{ mutex_ };
		vec_.reserve(s);
	}

	//��˵��liunx��accumulate�ڳ���һ���������ַ����£�������⣬windows����ʱ��������
	//+= 0.63s	accumulate 0.49s   500 loops
	//+= 2.56s	accumulate 2.38s   10000 loops
	//����Ϊģ��� += 1.75s	 accumulate 1.78s	10000 loops
	string_t toString()const
	{
		string_t s;
		s.reserve(vec_.size());
		//��һ�ַ���
		for (auto iter = vec_.begin(); iter != vec_.end(); ++iter)
			s += *iter;

		//�ڶ��ַ���
		//accumulate(s_.begin(), s_.end(), s);
		return s;
	}
private:
	vector<chr*>			vec_;
	mutex					mutex_;

};



