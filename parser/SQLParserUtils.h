#include <boost/smart_ptr.hpp>

public class SQLParserUtils {

	public:
		static SQLStatementParser createSQLStatementParser(std::string sql, std::string dbType);

		static SQLExprParser createExprParser(std::string sql, std::string dbType);
};

