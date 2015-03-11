#pragma once

#include <istream>
#include "Lex.h"
#include "Datalog.h"
#include "Predicate.h"
#include <vector>

using namespace std;

class Rule {
public:
	Rule();
	~Rule();
	string toString();
	Rule(Lex* lex);
	void ParseRuleList(Lex*);
	void ParseHeadPredicate(Lex*);
	void ParseIDList(Lex*);
	void ParseCheckEnd(Lex*);
	void AddPredicate(Lex*);
	string getCount();

private:
	//vector<Predicate*> preds;
};