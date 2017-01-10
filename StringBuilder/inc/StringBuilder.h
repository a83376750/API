#pragma once
#include <vector>
#include <list>
#include <mutex>
#include <string>
class StringBuilder
{
public:
	StringBuilder();
	StringBuilder(size_t s);
	~StringBuilder();

	StringBuilder& append(const char *s);
	StringBuilder& append(char *s);
	void resize(size_t s);
	std::string toString()const;
private:
	std::vector<const char*>	s_;
	std::mutex					mutex_;

};