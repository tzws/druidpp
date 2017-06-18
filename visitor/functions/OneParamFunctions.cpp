#include "OneParamFunctions.h"
OneParamFunctions::~OneParamFunctions()
{

}

OneParamFunctions * OneParamFunctions::instance()
{
	static OneParamFunctions x;
	return &x;
}

Object *OneParamFunctions::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	if (x.getParameters().size() == 0) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	SQLExpr param = x.getParameters().get(0);
	param.accept(visitor);

	Object paramValue = param.getAttributes().get(EVAL_VALUE);
	if (paramValue == null) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	if (paramValue == EVAL_VALUE_NULL) {
		return EVAL_VALUE_NULL;
	}

	std::string method = x.getMethodName();
	if ("md5".equalsIgnoreCase(method)) {
		std::string text = paramValue.toString();
		return Utils.md5(text);
	}

	if ("bit_count".equalsIgnoreCase(method)) {
		if (paramValue instanceof BigInteger) {
			return ((BigInteger) paramValue).bitCount();
		}

		if (paramValue instanceof BigDecimal) {
			BigDecimal decimal = (BigDecimal) paramValue;
			BigInteger bigInt = decimal.setScale(0,  BigDecimal.ROUND_HALF_UP).toBigInteger();
			return bigInt.bitCount();
		}
		Long val = SQLEvalVisitorUtils.castToLong(paramValue);
		return Long.bitCount(val);
	}

	if ("soundex".equalsIgnoreCase(method)) {
		std::string text = paramValue.toString();
		return soundex(text);
	}

	if ("space".equalsIgnoreCase(method)) {
		int intVal = SQLEvalVisitorUtils.castToInteger(paramValue);
		char[] chars = new char[intVal];
		for (int i = 0; i < chars.length; ++i) {
			chars[i] = ' ';
		}
		return new std::string(chars);
	}

	throw new UnsupportedOperationException(method);
}

std::string OneParamFunctions::soundex(std::string str) {
	if (str == null) {
		return null;
	}
	str = clean(str);
	if (str.length() == 0) {
		return str;
	}
	char out[] = {'0', '0', '0', '0'};
	char last, mapped;
	int incount = 1, count = 1;
	out[0] = str.charAt(0);
	// getMappingCode() throws IllegalArgumentException
	last = getMappingCode(str, 0);
	while ((incount < str.length()) && (count < out.length)) {
		mapped = getMappingCode(str, incount++);
		if (mapped != 0) {
			if ((mapped != '0') && (mapped != last)) {
				out[count++] = mapped;
			}
			last = mapped;
		}
	}
	return new std::string(out);
}

std::string OneParamFunctions::clean(std::string str) {
	if (str == null || str.length() == 0) {
		return str;
	}
	int len = str.length();
	char[] chars = new char[len];
	int count = 0;
	for (int i = 0; i < len; i++) {
		if (Character.isLetter(str.charAt(i))) {
			chars[count++] = str.charAt(i);
		}
	}
	if (count == len) {
		return str.toUpperCase(java.util.Locale.ENGLISH);
	}
	return new std::string(chars, 0, count).toUpperCase(java.util.Locale.ENGLISH);
}

char OneParamFunctions::getMappingCode(std::string str, int index) {
	// map() throws IllegalArgumentException
	char mappedChar = map(str.charAt(index));
	// HW rule check
	if (index > 1 && mappedChar != '0') {
		char hwChar = str.charAt(index - 1);
		if ('H' == hwChar || 'W' == hwChar) {
			char preHWChar = str.charAt(index - 2);
			char firstCode = map(preHWChar);
			if (firstCode == mappedChar || 'H' == preHWChar || 'W' == preHWChar) {
				return 0;
			}
		}
	}
	return mappedChar;
}

char OneParamFunctions::map(char ch) {
	std::string soundexMapping = "01230120022455012623010202";
	int index = ch - 'A';
	if (index < 0 || index >= soundexMapping.length()) {
		throw new IllegalArgumentException("The character is not mapped: " + ch);
	}
	return soundexMapping.charAt(index);
}


