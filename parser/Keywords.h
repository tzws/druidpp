//http://codereview.stackexchange.com/questions/14309/conversion-between-enum-and-string-in-c-class-header
//http://stackoverflow.com/questions/207976/how-to-easily-map-c-enums-to-strings
#ifndef KEYWORDS_HEADER_H
#define KEYWORDS_HEADER_H

#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>
#include <boost/bimap.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/functional/hash.hpp>
#include <iostream>
//#include <hash_map>

#include <boost/algorithm/string.hpp>
#include "Token.h"

//#include <unordered_map>

#include <boost/smart_ptr.hpp>

#include "../deps/xxhash/xxhash.h"
#include "../deps/smhasher/MurmurHash3.h"


extern int my_strcmp(const char* s1, const char* s2);

extern int bsd_strcmp(register const char *s1, register const char *s2);

extern int bsd_strcmp_u(register const char *s1, register const char *s2);
extern int apple_strcmp(const char *s1, const char *s2);

extern void convertToUpperCase(char *sPtr);


struct char_cmp { bool operator () (const char *a,const char *b) const 
	{
		return strcasecmp(a,b) < 0;
	} 
};




struct eqstr
{


	//inline size_t operator()(const char *s) const {
		//size_t hash = 1;
		//for (; *s; ++s) hash = hash * 5 + *s;
		//return hash;
	//}

	inline size_t operator()(const char *s) const {
		size_t hash = 1;
		hash = XXH32(s, strlen(s),0);
		//MurmurHash3_x86_32(s, strlen(s),0, &hash);
		//std::cout << "hash is: " << hash  << std::endl;

		return hash;
	}

	bool operator()(const char* s1, const char* s2) const
	{

		//std::cout << "s1 is: " << s1 << ", and s2 is: " << s2  << std::endl;
		//return strcasecmp(s1, s2) == 0;
		return strcmp(s1, s2) == 0;
		//return bsd_strcmp_u(s1, s2) == 0;
	}
};

struct Hash
{
	size_t operator()(const char* s) const
	{
#if 0
		/* magic numbers bits from <span class="skimlinks-unlinked">http://www.isthe.com/chongo/tech/comp/fnv</span>/ */
		// FNV-1a
		size_t h = 14695981039346656037U;
		while (*s) {
			h ^= *s; 
			h *= 1099511628211U;
			++s;
		}
		return h;
#else
		std::size_t seed = 0;
		for (; *s; ++s) {
			boost::hash_combine(seed, *s);
		}   
		return seed;
#endif
	}
};

struct mshash {
	
	inline size_t operator()(const char* s) const
	{
		std::size_t hash = 0;
		while (*s)
		{
			hash = hash * 101  +  *s++;
		}
		return hash;

	}
};

struct iequal_to
: std::binary_function<std::string, std::string, bool>
{
	iequal_to() {}
	explicit iequal_to(std::locale const& l) : locale_(l) {}

	template <typename String1, typename String2>
		bool operator()(String1 const& x1, String2 const& x2) const
		{
			return boost::algorithm::iequals(x1, x2, locale_);
		}
	private:
	std::locale locale_;
};

struct ihash
: std::unary_function<std::string, std::size_t>
{
	ihash() {}
	explicit ihash(std::locale const& l) : locale_(l) {}

	template <typename String>
		std::size_t operator()(String const& x) const
		{
			std::size_t seed = 0;

			for(typename String::const_iterator it = x.begin();
					it != x.end(); ++it)
			{
				boost::hash_combine(seed, std::toupper(*it, locale_));
			}

			return seed;
		}
	private:
	std::locale locale_;
};

namespace hash
{
	template <std::size_t FnvPrime, std::size_t OffsetBasis>
		struct basic_fnv_1
		{
			std::size_t operator()(std::string const& text) const
			{
				std::size_t hash = OffsetBasis;
				for(std::string::const_iterator it = text.begin(), end = text.end();
						it != end; ++it)
				{
					hash *= FnvPrime;
					hash ^= *it;
				}

				return hash;
			}
		};

	template <std::size_t FnvPrime, std::size_t OffsetBasis>
		struct basic_fnv_1a
		{
			std::size_t operator()(std::string const& text) const
			{
				std::size_t hash = OffsetBasis;
				for(std::string::const_iterator it = text.begin(), end = text.end();
						it != end; ++it)
				{
					hash ^= *it;
					hash *= FnvPrime;
				}

				return hash;
			}
		};

	// For 32 bit machines:
	const std::size_t fnv_prime = 16777619u;
	const std::size_t fnv_offset_basis = 2166136261u;

	// For 64 bit machines:
	// const std::size_t fnv_prime = 1099511628211u;
	// const std::size_t fnv_offset_basis = 14695981039346656037u;

	// For 128 bit machines:
	// const std::size_t fnv_prime = 309485009821345068724781401u;
	// const std::size_t fnv_offset_basis =
	//     275519064689413815358837431229664493455u;

	// For 256 bit machines:
	// const std::size_t fnv_prime =
	//     374144419156711147060143317175368453031918731002211u;
	// const std::size_t fnv_offset_basis =
	//     100029257958052580907070968620625704837092796014241193945225284501741471925557u;

	typedef basic_fnv_1<fnv_prime, fnv_offset_basis> fnv_1;
	typedef basic_fnv_1a<fnv_prime, fnv_offset_basis> fnv_1a;
}


//typedef boost::unordered_map<std::string, Token> TokenMap;
//typedef boost::unordered_map<std::string, Token, ihash, iequal_to> TokenMap;
//typedef boost::unordered_map<std::string, Token, hash::fnv_1> TokenMap;
typedef boost::unordered_map<std::string, Token, hash::fnv_1> TokenMap;
typedef boost::unordered_map<const char*, Token, eqstr, eqstr> HMap;
//typedef boost::unordered_map<const char*, Token, mshash, eqstr> HMap;

//typedef std::map<std::string, Token> TokenMap;


typedef std::map<const char *, Token, char_cmp> UMap;

class Keywords {
	private:
		TokenMap keywords;
		UMap theMap;
		HMap hmap;
		Token tok;



	public:
		static Keywords* getInstance();

		bool containsValue(Token &token);

		//Keywords(UMap<String, Token> keywords){
		//this.keywords = keywords;
		//}

		Token &getKeyword(std::string &key);
		Token &getKeyword(const char * key);
		Token &getKeyword( char * key);
		TokenMap& getKeywords();

	private:
		// Constructor? (the {} brackets) are needed here.
		Keywords() {

			keywords["ALL"] = ALL;
			keywords["ALTER"] = ALTER;
			keywords["AND"] = AND;
			keywords["ANY"] = ANY;
			keywords["AS"] = AS;

			keywords["ENABLE"] = ENABLE;
			keywords["DISABLE"] = DISABLE;

			keywords["ASC"] = ASC;
			keywords["BETWEEN"] = BETWEEN;
			keywords["BY"] = BY;
			keywords["CASE"] = CASE;
			keywords["CAST"] = CAST;

			keywords["CHECK"] = CHECK;
			keywords["CONSTRAINT"] = CONSTRAINT;
			keywords["CREATE"] = CREATE;
			keywords["DATABASE"] = DATABASE;
			keywords["DEFAULT"] = DEFAULT;
			keywords["COLUMN"] = COLUMN;
			keywords["TABLESPACE"] = TABLESPACE;
			keywords["PROCEDURE"] = PROCEDURE;
			keywords["FUNCTION"] = FUNCTION;

			keywords["DELETE"] = TOKEN_DELETE;
			keywords["DESC"] = DESC;
			keywords["DISTINCT"] = DISTINCT;
			keywords["DROP"] = DROP;
			keywords["ELSE"] = ELSE;
			keywords["EXPLAIN"] = EXPLAIN;
			keywords["EXCEPT"] = EXCEPT;

			keywords["END"] = END;
			keywords["ESCAPE"] = ESCAPE;
			keywords["EXISTS"] = EXISTS;
			keywords["FOR"] = FOR;
			keywords["FOREIGN"] = FOREIGN;

			keywords["FROM"] = FROM;
			keywords["FULL"] = FULL;
			keywords["GROUP"] = GROUP;
			keywords["HAVING"] = HAVING;
			keywords["IN"] = TOKEN_IN;

			keywords["INDEX"] = INDEX;
			keywords["INNER"] = INNER;
			keywords["INSERT"] = TOKEN_INSERT;
			keywords["INTERSECT"] = INTERSECT;
			keywords["INTERVAL"] = INTERVAL;

			keywords["INTO"] = INTO;
			keywords["IS"] = IS;
			keywords["JOIN"] = JOIN;
			keywords["KEY"] = KEY;
			keywords["LEFT"] = LEFT;

			keywords["LIKE"] = LIKE;
			keywords["LOCK"] = LOCK;
			keywords["MINUS"] = MINUS;
			keywords["NOT"] = NOT;

			keywords["NULL"] = XNULL;
			keywords["ON"] = ON;
			keywords["OR"] = OR;
			keywords["ORDER"] = ORDER;
			keywords["OUTER"] = OUTER;

			keywords["PRIMARY"] = PRIMARY;
			keywords["REFERENCES"] = REFERENCES;
			keywords["RIGHT"] = RIGHT;
			keywords["SCHEMA"] = SCHEMA;
			keywords["SELECT"] = TOKEN_SELECT;

			keywords["SET"] = SET;
			keywords["SOME"] = SOME;
			keywords["TABLE"] = TABLE;
			keywords["THEN"] = THEN;
			keywords["TRUNCATE"] = TRUNCATE;

			keywords["UNION"] = UNION;
			keywords["UNIQUE"] = UNIQUE;
			keywords["UPDATE"] = UPDATE;
			keywords["VALUES"] = VALUES;
			keywords["VIEW"] = VIEW;
			keywords["SEQUENCE"] = SEQUENCE;
			keywords["TRIGGER"] = TRIGGER;
			keywords["USER"] = USER;

			keywords["WHEN"] = WHEN;
			keywords["WHERE"] = WHERE;
			keywords["XOR"] = XOR;

			keywords["OVER"] = OVER;
			keywords["TO"] = TO;
			keywords["USE"] = USE;

			keywords["REPLACE"] = REPLACE;

			keywords["COMMENT"] = COMMENT;
			keywords["COMPUTE"] = COMPUTE;
			keywords["WITH"] = WITH;
			keywords["GRANT"] = GRANT;
			keywords["NO_EXISTING_TOKEN"] = NO_EXISTING_TOKEN;


			//theMap.insert(UMap::value_type("ALL",   ALL) );
			//theMap.insert(UMap::value_type("ALTER",   ALTER) );
			//theMap.insert(UMap::value_type("AND",   AND) );
			//theMap.insert(UMap::value_type("ANY",   ANY) );
			//theMap.insert(UMap::value_type("AS",   AS) );

			//theMap.insert(UMap::value_type("ENABLE",   ENABLE) );
			//theMap.insert(UMap::value_type("DISABLE",   DISABLE) );

			//theMap.insert(UMap::value_type("ASC",   ASC) );
			//theMap.insert(UMap::value_type("BETWEEN",   BETWEEN) );
			//theMap.insert(UMap::value_type("BY",   BY) );
			//theMap.insert(UMap::value_type("CASE",   CASE) );
			//theMap.insert(UMap::value_type("CAST",   CAST) );

			//theMap.insert(UMap::value_type("CHECK",   CHECK) );
			//theMap.insert(UMap::value_type("CONSTRAINT",   CONSTRAINT) );
			//theMap.insert(UMap::value_type("CREATE",   CREATE) );
			//theMap.insert(UMap::value_type("DATABASE",   DATABASE) );
			//theMap.insert(UMap::value_type("DEFAULT",   DEFAULT) );
			//theMap.insert(UMap::value_type("COLUMN",   COLUMN) );
			//theMap.insert(UMap::value_type("TABLESPACE",   TABLESPACE) );
			//theMap.insert(UMap::value_type("PROCEDURE",   PROCEDURE) );
			//theMap.insert(UMap::value_type("FUNCTION",   FUNCTION) );

			//theMap.insert(UMap::value_type("DELETE",   DELETE) );
			//theMap.insert(UMap::value_type("DESC",   DESC) );
			//theMap.insert(UMap::value_type("DISTINCT",   DISTINCT) );
			//theMap.insert(UMap::value_type("DROP",   DROP) );
			//theMap.insert(UMap::value_type("ELSE",   ELSE) );
			//theMap.insert(UMap::value_type("EXPLAIN",   EXPLAIN) );
			//theMap.insert(UMap::value_type("EXCEPT",   EXCEPT) );

			//theMap.insert(UMap::value_type("END",   END) );
			//theMap.insert(UMap::value_type("ESCAPE",   ESCAPE) );
			//theMap.insert(UMap::value_type("EXISTS",   EXISTS) );
			//theMap.insert(UMap::value_type("FOR",   FOR) );
			//theMap.insert(UMap::value_type("FOREIGN",   FOREIGN) );

			//theMap.insert(UMap::value_type("FROM",   FROM) );
			//theMap.insert(UMap::value_type("FULL",   FULL) );
			//theMap.insert(UMap::value_type("GROUP",   GROUP) );
			//theMap.insert(UMap::value_type("HAVING",   HAVING) );
			//theMap.insert(UMap::value_type("IN",   IN) );

			//theMap.insert(UMap::value_type("INDEX",   INDEX) );
			//theMap.insert(UMap::value_type("INNER",   INNER) );
			//theMap.insert(UMap::value_type("INSERT",   INSERT) );
			//theMap.insert(UMap::value_type("INTERSECT",   INTERSECT) );
			//theMap.insert(UMap::value_type("INTERVAL",   INTERVAL) );

			//theMap.insert(UMap::value_type("INTO",   INTO) );
			//theMap.insert(UMap::value_type("IS",   IS) );
			//theMap.insert(UMap::value_type("JOIN",   JOIN) );
			//theMap.insert(UMap::value_type("KEY",   KEY) );
			//theMap.insert(UMap::value_type("LEFT",   LEFT) );

			//theMap.insert(UMap::value_type("LIKE",   LIKE) );
			//theMap.insert(UMap::value_type("LOCK",   LOCK) );
			//theMap.insert(UMap::value_type("MINUS",   MINUS) );
			//theMap.insert(UMap::value_type("NOT",   NOT) );

			////theMap.insert(UMap::value_type("NULL",   XNULL) );
			//theMap.insert(UMap::value_type("ON",   ON) );
			//theMap.insert(UMap::value_type("OR",   OR) );
			//theMap.insert(UMap::value_type("ORDER",   ORDER) );
			//theMap.insert(UMap::value_type("OUTER",   OUTER) );

			//theMap.insert(UMap::value_type("PRIMARY",   PRIMARY) );
			//theMap.insert(UMap::value_type("REFERENCES",   REFERENCES) );
			//theMap.insert(UMap::value_type("RIGHT",   RIGHT) );
			//theMap.insert(UMap::value_type("SCHEMA",   SCHEMA) );
			//theMap.insert(UMap::value_type("SELECT",   SELECT) );

			//theMap.insert(UMap::value_type("SET",   SET) );
			//theMap.insert(UMap::value_type("SOME",   SOME) );
			//theMap.insert(UMap::value_type("TABLE",   TABLE) );
			//theMap.insert(UMap::value_type("THEN",   THEN) );
			//theMap.insert(UMap::value_type("TRUNCATE",   TRUNCATE) );

			//theMap.insert(UMap::value_type("UNION",   UNION) );
			//theMap.insert(UMap::value_type("UNIQUE",   UNIQUE) );
			//theMap.insert(UMap::value_type("UPDATE",   UPDATE) );
			//theMap.insert(UMap::value_type("VALUES",   VALUES) );
			//theMap.insert(UMap::value_type("VIEW",   VIEW) );
			//theMap.insert(UMap::value_type("SEQUENCE",   SEQUENCE) );
			//theMap.insert(UMap::value_type("TRIGGER",   TRIGGER) );
			//theMap.insert(UMap::value_type("USER",   USER) );

			//theMap.insert(UMap::value_type("WHEN",   WHEN) );
			//theMap.insert(UMap::value_type("WHERE",   WHERE) );
			//theMap.insert(UMap::value_type("XOR",   XOR) );

			//theMap.insert(UMap::value_type("OVER",   OVER) );
			//theMap.insert(UMap::value_type("TO",   TO) );
			//theMap.insert(UMap::value_type("USE",   USE) );

			//theMap.insert(UMap::value_type("REPLACE",   REPLACE) );

			//theMap.insert(UMap::value_type("COMMENT",   COMMENT) );
			//theMap.insert(UMap::value_type("COMPUTE",   COMPUTE) );
			//theMap.insert(UMap::value_type("WITH",   WITH) );
			//theMap.insert(UMap::value_type("GRANT",   GRANT) );
			//theMap.insert(UMap::value_type("NO_EXISTING_TOKEN",   NO_EXISTING_TOKEN) );



			hmap["ALL"] = ALL;
			hmap["ALTER"] = ALTER;
			hmap["AND"] = AND;
			hmap["ANY"] = ANY;
			hmap["AS"] = AS;

			hmap["ENABLE"] = ENABLE;
			hmap["DISABLE"] = DISABLE;

			hmap["ASC"] = ASC;
			hmap["BETWEEN"] = BETWEEN;
			hmap["BY"] = BY;
			hmap["CASE"] = CASE;
			hmap["CAST"] = CAST;

			hmap["CHECK"] = CHECK;
			hmap["CONSTRAINT"] = CONSTRAINT;
			hmap["CREATE"] = CREATE;
			hmap["DATABASE"] = DATABASE;
			hmap["DEFAULT"] = DEFAULT;
			hmap["COLUMN"] = COLUMN;
			hmap["TABLESPACE"] = TABLESPACE;
			hmap["PROCEDURE"] = PROCEDURE;
			hmap["FUNCTION"] = FUNCTION;

			hmap["DELETE"] = TOKEN_DELETE;
			hmap["DESC"] = DESC;
			hmap["DISTINCT"] = DISTINCT;
			hmap["DROP"] = DROP;
			hmap["ELSE"] = ELSE;
			hmap["EXPLAIN"] = EXPLAIN;
			hmap["EXCEPT"] = EXCEPT;

			hmap["END"] = END;
			hmap["ESCAPE"] = ESCAPE;
			hmap["EXISTS"] = EXISTS;
			hmap["FOR"] = FOR;
			hmap["FOREIGN"] = FOREIGN;

			hmap["FROM"] = FROM;
			hmap["FULL"] = FULL;
			hmap["GROUP"] = GROUP;
			hmap["HAVING"] = HAVING;
			hmap["IN"] = TOKEN_IN;

			hmap["INDEX"] = INDEX;
			hmap["INNER"] = INNER;
			hmap["INSERT"] = TOKEN_INSERT;
			hmap["INTERSECT"] = INTERSECT;
			hmap["INTERVAL"] = INTERVAL;

			hmap["INTO"] = INTO;
			hmap["IS"] = IS;
			hmap["JOIN"] = JOIN;
			hmap["KEY"] = KEY;
			hmap["LEFT"] = LEFT;

			hmap["LIKE"] = LIKE;
			hmap["LOCK"] = LOCK;
			hmap["MINUS"] = MINUS;
			hmap["NOT"] = NOT;

			hmap["NULL"] = XNULL;
			hmap["ON"] = ON;
			hmap["OR"] = OR;
			hmap["ORDER"] = ORDER;
			hmap["OUTER"] = OUTER;

			hmap["PRIMARY"] = PRIMARY;
			hmap["REFERENCES"] = REFERENCES;
			hmap["RIGHT"] = RIGHT;
			hmap["SCHEMA"] = SCHEMA;
			hmap["SELECT"] = TOKEN_SELECT;

			hmap["SET"] = SET;
			hmap["SOME"] = SOME;
			hmap["TABLE"] = TABLE;
			hmap["THEN"] = THEN;
			hmap["TRUNCATE"] = TRUNCATE;

			hmap["UNION"] = UNION;
			hmap["UNIQUE"] = UNIQUE;
			hmap["UPDATE"] = UPDATE;
			hmap["VALUES"] = VALUES;
			hmap["VIEW"] = VIEW;
			hmap["SEQUENCE"] = SEQUENCE;
			hmap["TRIGGER"] = TRIGGER;
			hmap["USER"] = USER;

			hmap["WHEN"] = WHEN;
			hmap["WHERE"] = WHERE;
			hmap["XOR"] = XOR;

			hmap["OVER"] = OVER;
			hmap["TO"] = TO;
			hmap["USE"] = USE;

			hmap["REPLACE"] = REPLACE;

			hmap["COMMENT"] = COMMENT;
			hmap["COMPUTE"] = COMPUTE;
			hmap["WITH"] = WITH;
			hmap["GRANT"] = GRANT;
			hmap["NO_EXISTING_TOKEN"] = NO_EXISTING_TOKEN;





		};                   
		// Dont forget to declare these two. You want to make sure they
		// are unaccessable otherwise you may accidently get copies of
		// your singleton appearing.
		Keywords(Keywords const&);              // Don't Implement
		//void operator=(Keywords const&); // Don't implement
};
typedef boost::shared_ptr<Keywords> Keywords_ptr;

#endif

