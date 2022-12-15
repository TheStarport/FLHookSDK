#pragma once

#include "SQLiteCpp/SQLiteCpp.h"

class DLL SqlManager : Singleton<SqlManager>
{
	static SQLite::Database Create(const std::string& path);

public:
	SqlManager();
	explicit SqlManager(const std::string& path);

	SQLite::Database db;
	static std::unique_ptr<SqlManager> GetDatabase(const std::string& path);
};