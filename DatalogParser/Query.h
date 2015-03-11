#pragma once

#include <istream>
#include "Lex.h"
#include "Datalog.h"

using namespace std;

class Query {
public:
	Query();
	~Query();
	string toString();
	Query(Lex* lex);
	void ParsePredicate(Lex*);
	void Check_Q_mark (Lex*);
};