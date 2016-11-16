#include "..\inc\Syna_Mysql.h"

using namespace Syna;

Syna_Mysql::Syna_Mysql()
{
}


Syna_Mysql::~Syna_Mysql()
{
}

bool Syna::Syna_Mysql::Connect(const char *host, const char *user, const char *passwd, const char *db, unsigned int port)
{
	MYSQL *sql = Find_MYSQL(db);
	if (sql == nullptr)
	{
		sql = mysql_init(nullptr);
		my_bool reconnect = true;
		mysql_options(sql, mysql_option::MYSQL_OPT_RECONNECT, &reconnect);
		if (!mysql_real_connect(sql, host, user, passwd, db, port, nullptr, 0))
		{
			return false;
		}

		map_Mysql_[db] = sql;
		return true;
	}
	if (!Ping(db))
	{
		sql = nullptr;
		return Connect(host, user, passwd, db, port);
	}
	return true;
}

bool Syna::Syna_Mysql::Query(const char *db, const char *sql_statement)
{
	MYSQL *sql = Find_MYSQL(db);
	if (!sql)
		return false;
	return mysql_query(sql, sql_statement) == 0;
}

bool Syna::Syna_Mysql::Ping(const char *db)
{
	MYSQL *sql = Find_MYSQL(db);
	if (!sql)
		return false;
	return mysql_ping(sql);
}

MYSQL* Syna::Syna_Mysql::Find_MYSQL(const char *db)
{
	if (!map_Mysql_.empty())
	{
		auto iter = map_Mysql_.find(db);
		if (iter != map_Mysql_.end())
		{
			return iter->second;
		}
	}
	return nullptr;
}
