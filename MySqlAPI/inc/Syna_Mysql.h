#pragma once
#include <mysql.h>
/************************************************************************/
/* mysql_init(MYSQL *mysql)							��ʼ��mysql         */
/* mysql_real_connect(MYSQL *mysql, const char *host,
					   const char *user,
					   const char *passwd,
					   const char *db,
					   unsigned int port,
					   const char *unix_socket,
					   unsigned long clientflag);	�������ݿ�           */
/* mysql_query(MYSQL *mysql, const char *q);		ִ�����ݿ�����		*/
/* ���ݿ����� - "SET NAMES GBK" ���ñ���									*/
/* mysql_store_result(MYSQL *mysql);				��ȡqueryִ�к���	*/
/* mysql_fetch_row(MYSQL_RES *result);				��ȡ��ѯ�����һ��	*/
/* mysql_free_result(results);????					�ͷŽ����			*/
/* mysql_close(mysql);????							�ر��������ݿ�		*/
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