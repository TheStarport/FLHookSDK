#pragma once

#include <optional>

#include "SQLiteCpp/SQLiteCpp.h"

class DLL SqlManager : Singleton<SqlManager>
{
	explicit SqlManager(const std::string& path);
	static SQLite::Database Create(const std::string& path);

	SQLite::Database db;
	std::optional<SQLite::Transaction> activeTransaction;

public:
	SqlManager();

	SQLite::Database& GetDb();
	static std::unique_ptr<SqlManager> GetDatabase(const std::string& path);
	SQLite::Statement StartQuery(const std::string& query, bool createTransaction = true);
	void Commit();
	void Rollback();
};