#include <iostream>
#include "../MySqlAPI/inc/Syna_Mysql.h"
#include "../ThreadPool/inc/ThreadPool.h"

void mysql_test()
{
	Syna::Syna_Mysql sql;
	if (sql.Connect("127.0.0.1", "syna", "83376750", "syna", 3306))
	{
		std::cout << "connect OK" << std::endl;
	}
	else
	{
		std::cout << "connect error" << std::endl;
	}

	sql.Query("syna", "select * from account");
}

void pushtask(std::shared_ptr<thread_pool::ThreadPool> ptr)
{
	int i = 0;
	do 
	{
		cin >> i;
		ptr->PushTask(mysql_test);
	} while (i != 0);
}

int main()
{
	std::shared_ptr<thread_pool::ThreadPool> ptr_pool = std::make_shared<thread_pool::ThreadPool>();
	ptr_pool->StartThreadPool();
	std::thread th(pushtask, ptr_pool);
	th.join();
	getchar();
	return 0;
}