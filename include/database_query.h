#ifndef PFT_DATABASE_QUERY_H
#define PFT_DATABASE_QUERY_H

#include "sqlite_forward_decl.h"

#include <string>
#include <vector>

namespace pft {

	class DatabaseQuery {
		enum DATA_TYPE {
			NULL_TYPE,
			FLOAT_TYPE,
			INT_TYPE,
			TEXT_TYPE,
			UNKNOWN_TYPE
		};

	public:
		DatabaseQuery();
		~DatabaseQuery();

		void Compile(const char *sqlQuery);
		void LoadFile(const char *fileName);

		void ExecuteAll();

		void Reset();
		bool Step();
		DATA_TYPE GetColumnType(int column);
		int GetInt(int column);
		std::string GetString(int column);
		double GetDouble(int column);

		void BindInt(const char *parameterName, int value);
		void BindString(const char *parameterName, const char *str);
		void BindDouble(const char *parameterName, double value);

		void Free();

		void SetDatabase(sqlite3 *db) { m_database = db; }
		sqlite3 *GetDatabase() { return m_database; }
		
	protected:
		int GetParameterIndex(const char *parameterName);

		sqlite3_stmt *m_statement;
		std::vector<sqlite3_stmt *> m_statements;
		sqlite3 *m_database;
	};

} /* namespace pft */

#endif /* PFT_DATABASE_QUERY_H */
