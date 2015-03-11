#pragma once

#include <istream>
#include "Lex.h"
#include "Parameter.h"
#include <vector>

using namespace std;

class Predicate {
public:
	Predicate();
	~Predicate();
	Predicate(Lex*);
	void ParsePredicate(Lex*);
	void ParseParameters(Lex*);
	void ParameterEnd(Lex*);
	string toString(string);

private:
	//vector<Parameter*> params;
};