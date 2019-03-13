#include <database_query.h>

#include <assert.h>
#include <sstream>
#include <fstream>

pft::DatabaseQuery::DatabaseQuery() {
	m_statement = nullptr;
	m_database = nullptr;
}

pft::DatabaseQuery::~DatabaseQuery() {
	assert(m_statement == nullptr);
}

void pft::DatabaseQuery::Compile(const char *query) {
	assert(m_database != nullptr);

	if (m_statement != nullptr) Free();

	int result;
	const char *leftover = nullptr;
	const char *str = query;
	sqlite3_stmt **targetStatement = &m_statement;
	while (true) {
		result = sqlite3_prepare_v2(m_database, str, -1, targetStatement, &leftover);

		if (result != SQLITE_OK) {
			const char *msg = sqlite3_errmsg(m_database);
			assert(result == SQLITE_OK);
		}

		if (leftover != nullptr && *targetStatement != nullptr) {
			m_statements.push_back(nullptr);
			targetStatement = &m_statements[(int)m_statements.size() - 1];
			str = leftover;
		}
		else if (leftover == nullptr) {
			break;
		}
		else if (*targetStatement == nullptr) {
			// The last created query must be invalid
			if (m_statements.size() > 0) {
				m_statements.pop_back();
			}
			else {
				m_statement = nullptr;
			}
			break;
		}
	}
}

void pft::DatabaseQuery::LoadFile(const char *fileName) {
	std::ifstream t(fileName);
	assert(t.is_open());

	//std::string test;
	//t >> test;

	std::stringstream buffer;
	std::string content( (std::istreambuf_iterator<char>(t) ),
		( std::istreambuf_iterator<char>() ) );

	Compile(content.c_str());
}

void pft::DatabaseQuery::ExecuteAll() {
	sqlite3_step(m_statement);

	int overflowStatements = (int)m_statements.size();
	for (int i = 0; i < overflowStatements; i++) {
		sqlite3_step(m_statements[i]);
	}

}

void pft::DatabaseQuery::Reset() {
	assert(m_statement != nullptr);

	sqlite3_reset(m_statement);

	int overflowStatements = (int)m_statements.size();
	for (int i = 0; i < overflowStatements; i++) {
		sqlite3_reset(m_statements[i]);
	}
}

bool pft::DatabaseQuery::Step() {
	assert(m_statement != nullptr);

	int result = sqlite3_step(m_statement);
	return result == SQLITE_ROW;
}

pft::DatabaseQuery::DATA_TYPE pft::DatabaseQuery::GetColumnType(int column) {
	assert(m_statement != nullptr);

	int result;
	result = sqlite3_column_type(m_statement, column);

	switch (result) {
	case SQLITE_NULL:
		return NULL_TYPE;
	case SQLITE_FLOAT:
		return FLOAT_TYPE;
	case SQLITE_INTEGER:
		return INT_TYPE;
	case SQLITE_TEXT:
		return TEXT_TYPE;
	default:
		return UNKNOWN_TYPE;
	}
}

int pft::DatabaseQuery::GetInt(int column) {
	assert(m_statement != nullptr);

	int result;
	result = sqlite3_column_int(m_statement, column);

	return result;
}

std::string pft::DatabaseQuery::GetString(int column) {
	assert(m_statement != nullptr);

	std::string result;
	result = (char *)sqlite3_column_text(m_statement, column);

	return result;
}

double pft::DatabaseQuery::GetDouble(int column) {
	assert(m_statement != nullptr);

	double result;
	result = sqlite3_column_double(m_statement, column);

	return result;
}

void pft::DatabaseQuery::BindInt(const char *parameter, int value) {
	int index = GetParameterIndex(parameter);
	sqlite3_bind_int(m_statement, index, value);
}

void pft::DatabaseQuery::BindDouble(const char *parameter, double value) {
	int index = GetParameterIndex(parameter);
	sqlite3_bind_double(m_statement, index, value);
}

void pft::DatabaseQuery::BindString(const char *parameter, const char *str) {
	int index = GetParameterIndex(parameter);
	int result = sqlite3_bind_text(m_statement, index, str, -1, SQLITE_TRANSIENT);

	assert(result == SQLITE_OK);
}

void pft::DatabaseQuery::Free() {
	sqlite3_finalize(m_statement);

	m_statement = nullptr;

	int overflowStatements = (int)m_statements.size();
	for (int i = 0; i < overflowStatements; i++) {
		sqlite3_finalize(m_statements[i]);
	}
}

int pft::DatabaseQuery::GetParameterIndex(const char *parameterName) {
	std::string formatted = "$" + std::string(parameterName);

	int index = sqlite3_bind_parameter_index(m_statement, formatted.c_str());
	return index;
}
