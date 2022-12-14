#include <FLHook.hpp>

const std::string flServerDb = "FLServer.db";

SqlManager::SqlManager() : db(Create(flServerDb))
{
}

SqlManager::SqlManager(const std::string& path) : db(Create(path))
{
}

SQLite::Database SqlManager::Create(const std::string& path)
{
	std::string saveGameDir;
	saveGameDir.reserve(MAX_PATH);
	GetUserDataPath(saveGameDir.data());

	return {saveGameDir + path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE};
}

std::unique_ptr<SqlManager> SqlManager::GetDatabase(const std::string& path)
{
	return std::make_unique<SqlManager>(path);
}

SQLite::Database& SqlManager::GetDb()
{
	return db;
}

SQLite::Statement SqlManager::StartQuery(const std::string& query, bool createTransaction)
{
	if (!activeTransaction.has_value() && createTransaction)
	{
		activeTransaction.emplace(SQLite::Transaction(db));
	}

	return {db, query};
}
void SqlManager::Commit()
{
	if (!activeTransaction.has_value())
	{
		throw SQLite::Exception("Cannot commit transaction. No transaction in progress.");
	}

	activeTransaction->commit();
	activeTransaction = std::nullopt;
}
void SqlManager::Rollback()
{
	if (!activeTransaction.has_value())
	{
		throw SQLite::Exception("Cannot rollback transaction. No transaction in progress.");
	}

	activeTransaction = std::nullopt;
}