#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>

#include "Lexer.h"
#include "NotAllowCommentException.h"
#include "ParserException.h"
#include "IllegalStateException.h"

long  Lexer::MULTMIN_RADIX_TEN   = LONG_MIN / 10;
long  Lexer::N_MULTMAX_RADIX_TEN = -LONG_MAX / 10;
int Lexer::digits[10];

bool Lexer::_digitsInitialized = initDigits();

bool Lexer::initDigits(){

	for (int i = '0'; i <= '9'; ++i) {
		digits[i] = i - '0';
	}
	return true;
}
Lexer::~Lexer() 
{

	//std::cout << __FILE__ << ": " << __LINE__ << ", in Lexer::Lexer, destructor  " << std::endl;
	//fprintf(stderr, "in Lexer::~Lexer\n");
	if (charbufLength != 0)
	{
		//std::cout << "in Lexer::~Lexer" << std::endl;
		//fprintf(stderr, "delete charBuf\n");
		delete[] charBuf;
	}

	if (tmpbufLength != 0)
	{
		//fprintf(stderr, "delete tmpBuf\n");
		delete[] tmpBuf;
	}
	
}

Lexer::Lexer(std::string &input): 
	//text(input), 
	skipComment(true), 
	pos(-1), 
	allowComment(true), 
	varIndex(-1), 
	charbufLength (input.length() + 1),
	keywods(Keywords::getInstance())  
{
	//std::cout << "in Lexer::Lexer, input is: << " << input << ", and size is: " << input.size()  << std::endl;
	tmpBuf = NULL;
	charBuf = new char[charbufLength];
	strcpy (charBuf, input.c_str());
	//charbufLength = input.length() + 1;
	//std::cout << "in Lexer::Lexer, strlen(charBuf) is: << " << (strlen(charBuf)) << ", and charbufLength is: " << charbufLength  << std::endl;
	//std::cout << "in Lexer::Lexer, charBuf is: << " << charBuf << std::endl;
	//std::cout << "in Lexer::Lexer, charBuf[0] is: << " << charBuf[0] << std::endl;

	//std::cout << "in Lexer::Lexer, calling scanChar << " << charBuf[0] << std::endl;
	scanChar();
	//std::cout << "in Lexer::Lexer, calling scanChar  done << " << charBuf[0] << std::endl;
}

Lexer::Lexer(std::string &input, bool skipComment) : 
	//text(input), 
	skipComment(skipComment), 
	pos(-1) , 
	allowComment(true), 
	varIndex(-1) , 
	keywods(Keywords::getInstance()) 
{
	//std::cout << __FILE__ << ": " << __LINE__ << ", in Lexer::Lexer, constructor 2  " << std::endl;
	tmpBuf = NULL;
	charBuf = new char[input.size()+1];
	strcpy (charBuf, input.c_str());
	charbufLength = input.length() + 1;
	scanChar();
}

Lexer::Lexer(char* input, int inputLength, bool skipComment): 
	//text(std::string (input, inputLength)), 
	skipComment(skipComment), 
	pos(-1), 
	allowComment(true), 
	varIndex(-1), 
	keywods(Keywords::getInstance()) 
{

	tmpBuf = NULL;
	charBuf = new char[inputLength];
	strncpy (charBuf, input, inputLength );
	//memcpy (charBuf, input, inputLength );
	charbufLength = inputLength;

	scanChar();
}

Lexer::CommentHandler& Lexer::getCommentHandler() {
	return commentHandler;
}

void Lexer::setCommentHandler(CommentHandler &commentHandler) {
	commentHandler = commentHandler;
}

//inline char Lexer::charAt(int index) {

	////if (index >= text.length()) {
		////return LayoutCharacters::EOI;
	////}
	////return text.at(index);

	//return (index >= charbufLength ) ? LayoutCharacters::EOI : charBuf[index];

	////if (index >= charbufLength) {
		////return LayoutCharacters::EOI;
	////}


	//////std::cout << "in Lexer::CharAt, index is: << " << (index) << std::endl;
	////return charBuf[index];

//}

//std::string &Lexer::addSymbol() {
	////std::cout << "in Lexer::addSymbol step 1, mark is: " << mark << ", and bufPos is: " << bufPos << std::endl;
	//return subString(mark, bufPos);
//}

void Lexer::addSymbol1() {
	//std::cout << "in Lexer::addSymbol1 step 1, mark is: " << mark << ", and bufPos is: " << bufPos << std::endl;
	stringMark.startPos = mark;
	stringMark.endPos = bufPos;
	//return subString(mark, bufPos);
}




//std::string &Lexer::subString(int offset, int count) {
	////std::cout << "in Lexer::subString step 1, offset is: " << offset << ", and count is: " << count << ", and text is: " << text << std::endl;
	////return text.substr(offset, offset + count);
	//return text.substr(offset, count);
//}

void Lexer::subString1(int offset, int count) {
	//std::cout << "in Lexer::subString1 step 1, offset is: " << offset << ", and count is: " << count << ", and text is: " << text << std::endl;
	//return text.substr(offset, count);



	stringMark.startPos = offset;
	stringMark.endPos = count;

}



bool Lexer::isAllowComment() {
	return allowComment;
}

void Lexer::setAllowComment(bool allowComment) {
	allowComment = allowComment;
}

int Lexer::nextVarIndex() {
	return ++varIndex;
}

Keywords *Lexer::getKeywods() {
	return keywods;
}

void Lexer::doMark() {
	SavePoint x_savePoint;
	x_savePoint.bp = pos;
	x_savePoint.sp = bufPos;
	x_savePoint.np = mark;
	x_savePoint.ch = ch;
	x_savePoint.token = token;
	savePoint = x_savePoint;
}

void Lexer::reset() {
	pos = savePoint.bp;
	bufPos = savePoint.sp;
	mark = savePoint.np;
	ch = savePoint.ch;
	token = savePoint.token;
}


bool Lexer::isEOF() {
	//return pos >= text.length();
	return pos >= charbufLength;
}

/**
 * Return the current token, set by nextToken().
 */
Token& Lexer::getToken() {
	return token;
}

std::string &Lexer::info() {
	stringInfo = boost::lexical_cast<std::string>(token) + " " + getStringVal();
	return stringInfo;
}

void Lexer::nextTokenComma() {
	if (ch == ' ') {
		scanChar();
	}

	//if (ch == ',' || ch == '，') {
	if (ch == ',' ) {
		scanChar();
		token = COMMA;
		return;
	}

	if (ch == ')') {
		scanChar();
		token = RPAREN;
		return;
	}

	nextToken();
}

void Lexer::nextTokenLParen() {
	if (ch == ' ') {
		scanChar();
	}

	if (ch == '(') {
		scanChar();
		token = LEFTPAREN;
		return;
	}
	nextToken();
}

void Lexer::nextTokenValue() {
	if (ch == ' ') {
		scanChar();
	}

	if (ch == '\'') {
		bufPos = 0;
		scanString();
		return;
	}

	if (ch >= '0' && ch <= '9') {
		bufPos = 0;
		scanNumber();
		return;
	}

	if (ch == '?') {
		scanChar();
		token = QUES;
		return;
	}

	if (CharTypes::isFirstIdentifierChar(ch) && ch != 'N') {
		scanIdentifier();
		return;
	}

	nextToken();
}

void Lexer::nextToken() {
	//std::cout << "\n\nin Lexer::nextToken step 1, ch is: " << ch << std::endl;
	bufPos = 0;

	for (;;) {
		if (CharTypes::isWhitespace(ch)) {
			//std::cout << "in Lexer::nextToken step 1, CharTypes::isWhitespace" << std::endl;
			scanChar();
			continue;
		}

		if (ch == '$' && charAt(pos + 1) == '{') {
			//std::cout << "in Lexer::nextToken step 1, ch == '$' && charAt(pos + 1) == '{'" << std::endl;
			scanVariable();
			return;
		}

		if (CharTypes::isFirstIdentifierChar(ch)) {
			//std::cout << "in Lexer::nextToken step 1, CharTypes::isFirstIdentifierChar(ch): " << ch << std::endl;
			if (ch == 'N') {
				//std::cout << "in Lexer::nextToken step 1, CharTypes::isFirstIdentifierChar(ch), ch == 'N'" << std::endl;
				if (charAt(pos + 1) == '\'') {
					++pos;
					ch = '\'';
					scanString();
					token = LITERAL_NCHARS;
					return;
				}
			}

			scanIdentifier();
			return;
		}
		//std::cout << "ch is: " << ch  << std::endl;

		switch (ch) {
			case '0':
				//std::cout << "in Lexer::nextToken step 1, switch case '0'" << std::endl;
				if (charAt(pos + 1) == 'x') {
					scanChar();
					scanChar();
					scanHexaDecimal();
				} else {
					scanNumber();
				}
				return;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				//std::cout << "in Lexer::nextToken step 1, switch case 1-9" << std::endl;
				scanNumber();
				return;
			case ',':
				//case '，':
				//std::cout << "in Lexer::nextToken step 1, switch case ," << std::endl;
				scanChar();
				token = COMMA;
				return;
			case '(':
				//std::cout << "in Lexer::nextToken step 1, switch case (" << std::endl;
				scanChar();
				token = LEFTPAREN;
				return;
			case ')':
				//std::cout << "in Lexer::nextToken step 1, switch case )" << std::endl;
				scanChar();
				token = RPAREN;
				return;
			case '[':
				//std::cout << "in Lexer::nextToken step 1, switch case [" << std::endl;
				scanLBracket();
				return;
			case ']':
				//std::cout << "in Lexer::nextToken step 1, switch case ]" << std::endl;
				scanChar();
				token = RBRACKET;
				return;
			case '{':
				//std::cout << "in Lexer::nextToken step 1, switch case {" << std::endl;
				scanChar();
				token = LBRACE;
				return;
			case '}':
				//std::cout << "in Lexer::nextToken step 1, switch case }" << std::endl;
				scanChar();
				token = RBRACE;
				return;
			case ':':
				//std::cout << "in Lexer::nextToken step 1, switch case :" << std::endl;
				scanChar();
				if (ch == '=') {
					scanChar();
					token = COLONEQ;
				} else if (ch == ':') {
					scanChar();
					token = COLONCOLON;
				} else {
					if (isDigit(ch)) {
						unscan();
						scanVariable();
					} else {
						unscan();
						scanVariable();
					}
				}
				return;
			case '#':
				//std::cout << "in Lexer::nextToken step 1, switch case #" << std::endl;
				scanSharp();
				if ((getToken() == LINE_COMMENT || getToken() == MULTI_LINE_COMMENT) && skipComment) {
					bufPos = 0;
					continue;
				}
				return;
			case '.':
				//std::cout << "in Lexer::nextToken step 1, switch case ." << std::endl;
				scanChar();
				if (isDigit(ch)) {
					unscan();
					scanNumber();
					return;
				} else if (ch == '.') {
					scanChar();
					if (ch == '.') {
						scanChar();
						token = DOTDOTDOT;
					} else {
						token = DOTDOT;
					}
				} else {
					token = DOT;
				}
				return;
			case '\'':
				//std::cout << "in Lexer::nextToken step 1, switch case \'" << std::endl;
				scanString();
				return;
			case '\"':
				//std::cout << "in Lexer::nextToken step 1, switch case \"" << std::endl;
				scanAlias();
				return;
			case '*':
				//std::cout << "in Lexer::nextToken step 1, switch case *" << std::endl;
				scanChar();
				token = STAR;
				return;
			case '?':
				//std::cout << "in Lexer::nextToken step 1, switch case ?" << std::endl;
				scanChar();
				token = QUES;
				return;
			case ';':
				//std::cout << "in Lexer::nextToken step 1, switch case ;" << std::endl;
				scanChar();
				token = SEMI;
				return;
			case '`':
				//std::cout << "in Lexer::nextToken step 1, switch case `" << std::endl;
				throw new ParserException("TODO"); // TODO
			case '@':
				//std::cout << "in Lexer::nextToken step 1, switch case @" << std::endl;
				scanVariable();
				return;
			case '-':
				//std::cout << "in Lexer::nextToken step 1, switch case -" << std::endl;
				//http://stackoverflow.com/questions/5685471/error-jump-to-case-label
				{
					int subNextChar = charAt(pos + 1);
					if (subNextChar == '-') {
						scanComment();
						if ((getToken() == LINE_COMMENT || getToken() == MULTI_LINE_COMMENT) && skipComment) {
							bufPos = 0;
							continue;
						}
					} else {
						scanOperator();
					}
					return;

				}
			case '/':
				//std::cout << "in Lexer::nextToken step 1, switch case /" << std::endl;
				{
					int nextChar = charAt(pos + 1);
					if (nextChar == '/' || nextChar == '*') {
						scanComment();
						if ((getToken() == LINE_COMMENT || getToken() == MULTI_LINE_COMMENT) && skipComment) {
							bufPos = 0;
							continue;
						}
					} else {
						token = SLASH;
						scanChar();
					}
					return;
				}
			default:
				//std::cout << "in Lexer::nextToken step 1, switch case default" << std::endl;
				if (isalpha(ch)) {
					scanIdentifier();
					return;
				}

				if (isOperator(ch)) {
					scanOperator();
					return;
				}

				// QS_TODO ?
				if (isEOF()) { // JLS
					token = ENDOFFILE;
				} else {
					//lexError("illegal.char", String.valueOf((int) ch));
					lexError("illegal.char", ((int) ch));
					scanChar();
				}

				return;
		}
	}
	//std::cout << "in Lexer::nextToken step done\n\n" << std::endl;
}

void Lexer::scanSharp() {
	scanVariable();
}

void Lexer::scanVariable() {
	if (ch != '@' && ch != ':' && ch != '#' && ch != '$') {
		throw new ParserException("illegal variable");
	}

	mark = pos;
	bufPos = 1;
	char xch;

	if (charAt(pos + 1) == '@') {
		xch = charAt(++pos);

		bufPos++;
	} else if (charAt(pos + 1) == '{') {
		pos++;
		bufPos++;

		for (;;) {
			xch = charAt(++pos);

			if (xch == '}') {
				break;
			}

			bufPos++;
			continue;
		}

		if (xch != '}') {
			throw new ParserException("syntax error");
		}
		++pos;
		bufPos++;

		ch = charAt(pos);

		//stringVal = addSymbol();
		addSymbol1();
		token = TOKEN_VARIANT;
		return;
	}

	for (;;) {
		xch = charAt(++pos);

		if (!CharTypes::isIdentifierChar(xch)) {
			break;
		}

		bufPos++;
		continue;
	}

	ch = charAt(pos);

	//stringVal = addSymbol();
	addSymbol1();
	token = TOKEN_VARIANT;
}


void Lexer::scanComment() {
	if (!allowComment) {
		throw new NotAllowCommentException();
	}

	if (ch != '/') {
		throw new IllegalStateException();
	}

	mark = pos;
	bufPos = 0;
	scanChar();

	if (ch == '*') {
		scanChar();
		bufPos++;

		for (;;) {
			if (ch == '*' && charAt(pos + 1) == '/') {
				bufPos += 2;
				scanChar();
				scanChar();
				break;
			}

			scanChar();
			bufPos++;
		}

		//stringVal = subString(mark, bufPos);
		subString1(mark, bufPos);
		token = MULTI_LINE_COMMENT;
		return;
	}

	if (ch == '/') {
		scanChar();
		bufPos++;

		for (;;) {
			if (ch == '\r') {
				if (charAt(pos + 1) == '\n') {
					bufPos += 2;
					scanChar();
					break;
				}
				bufPos++;
				break;
			}

			if (ch == '\n') {
				scanChar();
				bufPos++;
				break;
			}

			scanChar();
			bufPos++;
		}

		//stringVal = subString(mark + 1, bufPos);
		subString1(mark + 1, bufPos);
		token = LINE_COMMENT;
		return;
	}
}

void Lexer::keepChar() {

	tmpchar = charBuf[stringMark.endPos];
	charBuf[stringMark.startPos + stringMark.endPos ] = '\0';
}

void Lexer::restoreChar() {
	charBuf[stringMark.startPos + stringMark.endPos ] = tmpchar;
}

void Lexer::scanIdentifier() {

	//std::cout << "in Lexer::scanIdentifier step 1" << std::endl;
	char first = ch;

	bool firstFlag = CharTypes::isFirstIdentifierChar(first);
	if (!firstFlag) {
		throw new ParserException("illegal identifier");
	}

	mark = pos;
	bufPos = 1;
	char xch;
	//std::cout << "in Lexer::scanIdentifier step 2, for loop" << std::endl;
	for (;;) {
		xch = charAt(++pos);
		//std::cout << "\t\tin Lexer::scanIdentifier step 2, for loop, xch is: " << xch << std::endl;

		if (!CharTypes::isIdentifierChar(xch)) {
			break;
		}

		bufPos++;
		continue;
	}

	//std::cout << "in Lexer::scanIdentifier step 2, for loop done" << ", pos is: " << pos << ", xch is: " << xch << std::endl;

	ch = charAt(pos);
	//std::cout << "in Lexer::scanIdentifier step 2.1, ch is: " << ch << std::endl;

	//std::cout << "in Lexer::scanIdentifier step 3" << std::endl;
	//stringVal = addSymbol();
	addSymbol1();
	//stringVal = getStringVal();
	//Token tok = keywods->getKeyword(stringVal);
	//std::cout << "in Lexer::scanIdentifier step 4, stringVal is: " << stringVal << std::endl;




	char tmpch = charBuf[stringMark.endPos];


	//std::cout << __FILE__ << ": " << __LINE__ << ": in Lexer::scanIdentifier step 4, stringVal is: " << (charBuf + stringMark.startPos) <<  ", and endPos is: " << stringMark.endPos <<  std::endl;
	charBuf[stringMark.startPos + stringMark.endPos ] = '\0';
	//std::cout << __FILE__ << ": " << __LINE__ << ": in Lexer::scanIdentifier step 4, stringVal is: " << (charBuf + stringMark.startPos) << std::endl;
	Token tok = keywods->getKeyword(charBuf + stringMark.startPos);
	//std::cout << __FILE__ << ": " << __LINE__ << ": in Lexer::scanIdentifier step 4, stringVal is: " << (charBuf + stringMark.startPos) << ", and tok is: " << tok << std::endl;
	charBuf[stringMark.startPos + stringMark.endPos ] = tmpch;
	//std::cout << "in Lexer::scanIdentifier step 5" << std::endl;


	if (tok != NO_EXISTING_TOKEN) {
		token = tok;
		//std::cout << "in Lexer::scanIdentifier step 5.1, token is: " << tokenStringList.at(tok) << std::endl;
	} else {
		//std::cout << "in Lexer::scanIdentifier step 5.2, token is: " << tokenStringList.at(tok) << std::endl;
		//std::cout << "in Lexer::scanIdentifier step 5.2, token is: " << tok << std::endl;
		token = IDENTIFIER;
	}
}

void Lexer::scanNumber() {
	mark = pos;

	if (ch == '-') {
		bufPos++;
		ch = charAt(++pos);
	}

	for (;;) {
		if (ch >= '0' && ch <= '9') {
			bufPos++;
		} else {
			break;
		}
		ch = charAt(++pos);
	}

	bool isDouble = false;

	if (ch == '.') {
		if (charAt(pos + 1) == '.') {
			token = LITERAL_INT;
			return;
		}
		bufPos++;
		ch = charAt(++pos);
		isDouble = true;

		for (;;) {
			if (ch >= '0' && ch <= '9') {
				bufPos++;
			} else {
				break;
			}
			ch = charAt(++pos);
		}
	}

	if (ch == 'e' || ch == 'E') {
		bufPos++;
		ch = charAt(++pos);

		if (ch == '+' || ch == '-') {
			bufPos++;
			ch = charAt(++pos);
		}

		for (;;) {
			if (ch >= '0' && ch <= '9') {
				bufPos++;
			} else {
				break;
			}
			ch = charAt(++pos);
		}

		isDouble = true;
	}

	if (isDouble) {
		token = LITERAL_FLOAT;
	} else {
		token = LITERAL_INT;
	}
}


void Lexer::scanHexaDecimal() {
	mark = pos;

	if (ch == '-') {
		bufPos++;
		ch = charAt(++pos);
	}

	for (;;) {
		if (CharTypes::isHex(ch)) {
			bufPos++;
		} else {
			break;
		}
		ch = charAt(++pos);
	}

	token = LITERAL_HEX;
}

std::string &Lexer::hexString() {
	std::string x(charBuf + mark, bufPos );
	stringVal = x;
	//return subString(mark, bufPos);
	return stringVal;
}

bool Lexer::isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

/**
 * Return the current token's position: a 0-based offset from beginning of the raw input stream (before unicode
 * translation)
 */

int Lexer::getPos() {
	return pos;
}

/**
 * The value of a literal token, recorded as a string. For integers, leading 0x and 'l' suffixes are suppressed.
 */
std::string &Lexer::getStringVal() {
	std::string x  (charBuf + stringMark.startPos, stringMark.endPos );
	stringVal = x;
	return stringVal;
}
char * Lexer::getStringVal1() {
	return charBuf + stringMark.startPos + stringMark.endPos;
}

// QS_TODO negative number is invisible for lexer
//Number Lexer::integerValue() {
//int Lexer::integerValue() {
RNumber* Lexer::integerValue() {
	//std::cout << "in Lexer::integerValue "  << std::endl;
	long result = 0;
	bool negative = false;
	int i = mark, max = mark + bufPos;
	long limit;
	long multmin;
	int digit;

	if (charAt(mark) == '-') {
		negative = true;
		limit = LONG_MIN;
		i++;
	} else {
		limit = -LONG_MAX;
	}
	multmin = negative ? MULTMIN_RADIX_TEN : N_MULTMAX_RADIX_TEN;
	if (i < max) {
		digit = digits[charAt(i++)];
		result = -digit;
	}
	while (i < max) {
		// Accumulating negatively avoids surprises near LONG_MAX
		digit = digits[charAt(i++)];
		if (result < multmin) {
			//return new BigInteger(numberString());
			throw new NumberFormatException( "result < multmin" + numberString());
		}
		result *= 10;
		if (result < limit + digit) {
			//return new BigInteger(numberString());
			throw new NumberFormatException( "result < limit + digit" + numberString());
		}
		result -= digit;
	}

	if (negative) {
		if (i > mark + 1) {
			if (result >= LONG_MIN) {

				RNumber *n = new RNumber((int) result);

				//return (int) result;
				return n;
			}
			RNumber *n = new RNumber(result);
			return n;
			//return result;
		} else { /* Only got "-" */
			throw new NumberFormatException(numberString());
		}
	} else {
		result = -result;
		if (result <= LONG_MAX) {
			//return (int) result;
			//std::cout << "in Lexer::integerValue, result is: " << result << std::endl;
			RNumber *n = new RNumber((int) result);
			return n;
		}

		//std::cout << "in Lexer::integerValue, result is: " << result << std::endl;
		RNumber *n = new RNumber(result);
		return n;
		//return result;
	}
}

int Lexer::bp() {
	return pos;
}

char Lexer::current() {
	return ch;
}

void Lexer::reset(int mark, char markChar, Token token) {
	pos = mark;
	ch = markChar;
	token = token;
}

std::string &Lexer::numberString() {
	//return subString(mark, bufPos);
	std::string x (charBuf + stringMark.startPos, stringMark.endPos );
	stringVal = x;
	return stringVal;
}

//std::decimal::decimal128 Lexer::decimalValue() {
RNumber *Lexer::decimalValue() {

	//std::string tmp = text.substr(mark, bufPos);
	std::string tmp (charBuf + stringMark.startPos, stringMark.endPos);
	double d = boost::lexical_cast<double>(tmp);
	RNumber *n = new RNumber(d);
	return n;
	//return new std::decimal::decimal128(text.toCharArray(), mark, bufPos);
}

//static interface Lexer::CommentHandler {
	//bool handle(Token lastToken, std::string comment);
//}


void Lexer::initBuff(int size) {
	if (tmpBuf == NULL) {
		if (size < 1024) {
			//buf = new char[1024];
			tmpBuf = new char[1024];
			tmpbufLength = 1024;

		} else {
			//buf = new char[size + 1024];
			tmpBuf = new char[size + 1024];
			tmpbufLength = size + 1024;
		}
	} else if (tmpbufLength < size) {
		//buf = Arrays.copyOf(buf, size);
		char * tmp = tmpBuf;
		tmpBuf = new char[size];
		delete[] tmp;
	}
}

//void Lexer::scanChar() {

	////std::cout << "in Lexer::scanChar, step 1 " << charBuf[0] << std::endl;
	//ch = charAt(++pos);
	////std::cout << "in Lexer::scanChar, step 2 " << charBuf[0] << std::endl;
//}

void Lexer::unscan() {
	ch = charAt(--pos);
}

/**
 * Report an error at the given position using the provided arguments.
 */
void Lexer::lexError(std::string &key, ...) {
	token = TOKEN_ERROR;
}

void Lexer::lexError( const char *key, ...) {
	token = TOKEN_ERROR;
}

void Lexer::scanLBracket() {
	scanChar();
	token = LBRACKET;
}

void Lexer::scanString() {
	mark = pos;
	bool hasSpecial = false;

	for (;;) {
		if (isEOF()) {
			lexError("unclosed.str.lit");
			return;
		}

		ch = charAt(++pos);

		if (ch == '\'') {
			scanChar();
			if (ch != '\'') {
				token = LITERAL_CHARS;
				break;
			} else {
				if (!hasSpecial) {
					initBuff(bufPos);
					memcpy(charBuf + mark + 1, tmpBuf +  0, bufPos);
					//arraycopy(mark + 1, buf, 0, bufPos);

					//public void arraycopy(int srcPos, char[] dest, int destPos, int length) {
						//text.getChars(srcPos, srcPos + length, dest, destPos);
					//}

					//std::string tmp = text.substr(mark + 1, bufPos);
					//for (int i = 0; i < tmp.size(); i++)
					//{
						//buf.push_back(tmp.at(i));
					//}


					hasSpecial = true;
				}
				putChar('\'');
				continue;
			}
		}

		if (!hasSpecial) {
			bufPos++;
			continue;
		}

		if (bufPos == tmpbufLength) {
			putChar(ch);
		} else {
			//buf[bufPos++] = ch;
			//buf.push_back(ch);
			//bufPos++;
			tmpBuf[bufPos++] = ch;
		}
	}

	if (!hasSpecial) {
		//stringVal = subString(mark + 1, bufPos);
		stringMark.startPos = mark + 1;
		stringMark.endPos = bufPos;
	} else {
		//stringVal = std::string(buf, 0, bufPos);
		//stringVal = std::string (buf.begin(),buf.end());

		stringMark.startPos = 0;
		stringMark.endPos = charbufLength;
	}
}

/**
 * Append a character to sbuf.
 */
void Lexer::putChar(char ch) {

	if (bufPos == tmpbufLength) {
		char * tmp = tmpBuf;
		char * newsbuf = new char[tmpbufLength * 2];
		memcpy(tmpBuf, newsbuf, tmpbufLength);
		//System.arraycopy(buf, 0, newsbuf, 0, buf.length);
		tmpBuf = newsbuf;
		tmpbufLength *= 2;
		delete[] tmp;
	}
	tmpBuf[bufPos++] = ch;

	//buf.push_back(ch);
	//bufPos++;
	//buf[bufPos++] = ch;
}


void Lexer::scanOperator() {
	switch (ch) {
		case '+':
			scanChar();
			token = PLUS;
			break;
		case '-':
			scanChar();
			token = SUB;
			break;
		case '*':
			scanChar();
			token = STAR;
			break;
		case '/':
			scanChar();
			token = SLASH;
			break;
		case '&':
			scanChar();
			if (ch == '&') {
				scanChar();
				token = AMPAMP;
			} else {
				token = AMP;
			}
			break;
		case '|':
			scanChar();
			if (ch == '|') {
				scanChar();
				token = BARBAR;
			} else {
				token = BAR;
			}
			break;
		case '^':
			scanChar();
			token = CARET;
			break;
		case '%':
			scanChar();
			token = PERCENT;
			break;
		case '=':
			scanChar();
			if (ch == '=') {
				scanChar();
				token = EQEQ;
			} else {
				token = EQ;
			}
			break;
		case '>':
			scanChar();
			if (ch == '=') {
				scanChar();
				token = GTEQ;
			} else if (ch == '>') {
				scanChar();
				token = GTGT;
			} else {
				token = GT;
			}
			break;
		case '<':
			scanChar();
			if (ch == '=') {
				scanChar();
				if (ch == '>') {
					token = LTEQGT;
					scanChar();
				} else {
					token = LTEQ;
				}
			} else if (ch == '>') {
				scanChar();
				token = LTGT;
			} else if (ch == '<') {
				scanChar();
				token = LTLT;
			} else {
				token = LT;
			}
			break;
		case '!':
			scanChar();
			if (ch == '=') {
				scanChar();
				token = BANGEQ;
			} else if (ch == '>') {
				scanChar();
				token = BANGGT;
			} else if (ch == '<') {
				scanChar();
				token = BANGLT;
			} else {
				token = BANG;
			}
			break;
		case '?':
			scanChar();
			token = QUES;
			break;
		case '~':
			scanChar();
			token = TILDE;
			break;
		default:
			throw new ParserException("TODO");
	}
}

void Lexer::scanAlias() {
	mark = pos;

	for (;;) {
		if (isEOF()) {
			lexError("unclosed.str.lit");
			return;
		}

		ch = charAt(++pos);

		if (ch == '\"') {
			scanChar();
			token = LITERAL_ALIAS;
			break;
		}

		if (bufPos == tmpbufLength) {
			putChar(ch);
		} else {
			tmpBuf[bufPos++] = ch;
			//buf.push_back(ch);
			//bufPos++;
		}
	}

	//stringVal = subString(mark + 1, bufPos);
	stringMark.startPos = mark + 1;
	stringMark.endPos = bufPos;
}

bool Lexer::isOperator(char ch) {
	switch (ch) {
		case '!':
		case '%':
		case '&':
		case '*':
		case '+':
		case '-':
		case '<':
		case '=':
		case '>':
		case '^':
		case '|':
		case '~':
		case ';':
			return true;
		default:
			return false;
	}
}
