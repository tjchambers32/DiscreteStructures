#pragma once

#include <iostream>
#include <vector>
#include <set>
#include "Datalog.h"

using namespace std;

class Parse {
public:
	Parse();
	~Parse();
	void ParseScheme(Lex* lex);
	void ParseFact(Lex* lex);
	void ParseRule(Lex* lex);
	void ParseQuery(Lex* lex);

private:
	
};