#pragma once

#include <istream>
#include "Lex.h"
#include "Datalog.h"

using namespace std;

class Parameter {
public:
	Parameter();
	~Parameter();
	Parameter(Lex*);
	void ParseParameter(Lex*);
	void ParseExpression(Lex*);
	string toString();

};