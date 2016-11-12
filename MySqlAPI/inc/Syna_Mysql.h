#pragma once
#include <mysql.h>
/************************************************************************/
/* mysql_init(MYSQL *mysql)							初始化mysql         */
/* mysql_real_connect(MYSQL *mysql, const char *host,
					   const char *user,
					   const char *passwd,
					   const char *db,
					   unsigned int port,
					   const char *unix_socket,
					   unsigned long clientflag);	连接数据库           */
/* mysql_query(MYSQL *mysql, const char *q);		执行数据库命令		*/
/* 数据库命令 - "SET NAMES GBK" 设置编码									*/
/* mysql_store_result(MYSQL *mysql);				获取query执行后结果	*/
/* mysql_fetch_row(MYSQL_RES *result);				获取查询结果的一行	*/
/* mysql_free_result(results);????					释放结果集			*/
/* mysql_close(mysql);????							关闭连接数据库		*/
/************************************************************************/
namespace Syna
{
	class Syna_Mysql
	{
	public:
		Syna_Mysql();
		~Syna_Mysql();
	};
}