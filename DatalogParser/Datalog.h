#pragma once

#include <istream>
#include "Token.h"
#include "TokenType.h"
#include "Fact.h"
#include "Query.h"
#include "Rule.h"
#include "Scheme.h"
#include "Input.h"
#include <set>
#include <vector>
#include "Lex.h"
#include "Parse.h"

using namespace std;

class Datalog {
public:
	Datalog();
	~Datalog();
	Datalog(Lex* lex);

	void Parse(Lex* lex);
	bool match(TokenType);
	string toString(Lex*, string);

private:
	//vector<string> schemes;
//	vector<Fact> facts;
//	vector<Rule> rules;
//	vector<Query> queries;
	set<string> domain;
	vector<TokenType> types;
//	Fact* facts;

};