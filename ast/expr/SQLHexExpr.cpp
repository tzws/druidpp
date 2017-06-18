#include "SQLHexExpr.h"
SQLHexExpr::SQLHexExpr(std::string &theHex){
	hex = theHex;
}
SQLHexExpr::~SQLHexExpr(){

}

std::string &SQLHexExpr::getHex() {
	return hex;
}

void SQLHexExpr::output(std::string & buf) {
	//buf.append("0x");
	buf += "0x";
	//buf.append(hex);
	buf += hex;

	std::string xusing = "USING";
	Object * o =  getAttribute(xusing);

	std::string *charset = dynamic_cast<std::string *>(o);
	//std::string charset = (std::string) getAttribute(xusing);

	if (*charset != "") {
		////buf.append(" USING ");
		buf += " USING ";
		////buf.append(charset);
		buf += *charset;
	}

}

void SQLHexExpr::accept0(SQLASTVisitor *visitor) {
	visitor->visit(this);
	visitor->endVisit(this);
}

//int SQLHexExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((hex == NULL) ? 0 : hex.hashCode());
	//return result;
//}

//bool SQLHexExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLHexExpr other = (SQLHexExpr) obj;
	//if (hex == NULL) {
		//if (other.hex != NULL) {
			//return false;
		//}
	//} else if (!hex.equals(other.hex)) {
		//return false;
	//}
	//return true;
//}

//char[] toBytes() {
	//return HexBin.decode(hex);
//}

