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

void threadpool()
{
	std::shared_ptr<thread_pool::ThreadPool> ptr_pool = std::make_shared<thread_pool::ThreadPool>();
	std::thread th(pushtask, ptr_pool);
	th.join();
	printf("ptr_pool:%d\n", ptr_pool.use_count());
}

int countdown(int from, int to)
{
	for (int i = from; i != to; --i)
	{
		std::cout << i << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Finished!\n";
	return from - to;
}

void packageTest()
{
	std::packaged_task<int(int, int)> task(countdown); // 设置 packaged_task
	std::future<int> ret = task.get_future(); // 获得与 packaged_task 共享状态相关联的 future 对象.
	std::thread th(std::move(task), 10, 0);   //创建一个新线程完成计数任务.
	int value = ret.get();                    // 等待任务完成并获取结果.
	std::cout << "The countdown lasted for " << value << " seconds.\n";
	th.join();
}

#include <iomanip>
void showTimer()
{
	namespace chrono = std::chrono;

	// Because c-style date&time utilities don't support microsecond precison,
	// we have to handle it on our own.
	auto time_now = chrono::system_clock::now();
	auto duration_in_ms = chrono::duration_cast<chrono::milliseconds>(time_now.time_since_epoch());
	auto ms_part = duration_in_ms - chrono::duration_cast<chrono::seconds>(duration_in_ms);

	tm local_time_now;
	time_t raw_time = chrono::system_clock::to_time_t(time_now);
	_localtime64_s(&local_time_now, &raw_time);
	std::cout << std::put_time(&local_time_now, "%Y%m%d %H:%M:%S,")
		<< std::setfill('0') << std::setw(3) << ms_part.count();
}

#include "../MD5/inc/MD5.h"
void testMD5()
{
	while (true)
	{
		unsigned char str[1024] = "";
		std::cin >> str;
		MD5 md5;
		md5.GenerateMD5(str, 1024);
		printf("%s\n", md5.ToString().c_str());
	}
}

#include <fstream>
int fileMD5()
{
	HANDLE hd = CreateFile(L"C:/Workspace/Project/main.cpp", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hd == INVALID_HANDLE_VALUE)
	{
		printf("%d\n", GetLastError());
		return -1;
	}
	DWORD nSize = GetFileSize(hd, NULL);
	HANDLE mapHD = CreateFileMapping(hd, NULL, PAGE_READWRITE, 0, nSize, L"main.cpp");
	if (mapHD == NULL)
	{
		printf("%d\n", GetLastError());
		return -2;
	}
	void* pvFile = MapViewOfFile(mapHD, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, nSize);
	if (pvFile == nullptr)
	{
		printf("%d\n", GetLastError());
		return -3;
	}
	MD5 md5;
	md5.GenerateMD5((unsigned char*)pvFile, nSize);
	printf("MD5:%s\n", md5.ToString().c_str());
}

#include "../DataStruct/inc/DataStruct.h"
int main()
{
	DataStruct::List<int> l;
	int i[3] = { 1,2,3 };
	l.pushback(i[0]);
	l.pushback(i[1]);
	l.pushback(i[2]);

	for (int i = 0; i < 3; ++i)
	{
		printf("%d\n", l[i]);
	}
	system("pause");
	return 0;
}