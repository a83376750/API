#include <iostream>
#include "../MySqlAPI/inc/Syna_Mysql.h"

int main()
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
	return 0;
}