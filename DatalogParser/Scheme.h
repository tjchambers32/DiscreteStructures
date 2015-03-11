#pragma once

#include <istream>
#include "Token.h"
#include "TokenType.h"
#include "Lex.h"
#include "Datalog.h"
#include <vector>
#include <string>
using namespace std;

class Scheme {
public:
	Scheme();
	~Scheme();
	Scheme(Lex* lex);
	bool ParseSchemes(Lex* lex);
	string getCount();
	string toString();
	bool ParseIDList(Lex* lex);
	
private:
	vector<Scheme> List_of_Schemes;
	//int count;

	vector<Token*> tokens;
};