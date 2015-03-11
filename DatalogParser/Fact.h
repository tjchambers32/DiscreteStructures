#pragma once

#include <istream>
#include "Lex.h"
#include "Datalog.h"
#include <string>
using namespace std;

class Fact {
public:
	Fact();
	~Fact();
	string toString();

	Fact(Lex* lex);
	void ParseFacts(Lex* lex);
	bool ParseStringList(Lex* lex);
	int getNumber();
	string getCount();

private:
	int TotalFacts;
};