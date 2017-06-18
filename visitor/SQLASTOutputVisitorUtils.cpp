#include "SQLASTOutputVisitorUtils.h"


bool visit(PrintableVisitor visitor, SQLIntegerExpr x) {
	visitor.print(x.getNumber().toString());
	return false;
}

bool visit(PrintableVisitor visitor, SQLNumberExpr x) {
	visitor.print(x.getNumber().toString());
	return false;
}

bool visit(PrintableVisitor visitor, SQLCharExpr x) {
	visitor.print('\'');

	String text = x.getText();
	text = text.replaceAll("'", "''");
	text = text.replaceAll("\\\\", "\\\\");

	visitor.print(text);

	visitor.print('\'');
	return false;
}

