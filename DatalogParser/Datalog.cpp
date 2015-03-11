#pragma once

#include <iostream>
#include <fstream>
#include "Datalog.h"
#include "Token.h"
#include "TokenType.h"
#include "Input.h"
#include "Lex.h"
#include "Parse.h"
#include "Scheme.h"

using namespace std;
vector<Query> queries;

Datalog::Datalog()
{

}
Datalog::~Datalog()
{

}

Datalog::Datalog(Lex* lex) 
{
	types.push_back(SCHEMES);
	types.push_back(FACTS);
	types.push_back(RULES);
	types.push_back(QUERIES);
	Scheme* schemes = new Scheme();
	Parse(lex);
}
//vector<string> Schemes = SchemeString;
string Datalog::toString(Lex* lex, string str)
{
	if (lex->fail == NULL)
	{
	
		Scheme* schemes = new Scheme;
		Fact* facts = new Fact;
		Rule* rules = new Rule;
		Predicate* predicate = new Predicate;
		Query* queries = new Query;

		str += "Success!\n";
		
		str += "Schemes(";
		str += schemes->getCount();
		str += "):\n";
		str += schemes->toString();
		str += "\n";
		
		str += "Facts(";
		str += facts->getCount();
		str += "):\n";
		str += facts->toString();
		str += "\n";

		str += "Rules(";
		str += rules->getCount();
		str += "):\n";
		str += rules->toString();
		//str += predicate->toString("Rule");
		str += "\n";
		/*
		str += "Queries(";
		str += queries->getCount();
		str += "):\n";
		str += queries->toString();
		str += "\n";
		*/
	}
	return str;
}

void Datalog::Parse(Lex* lexer)
{
	int i = 0;
	while (i < types.size())
	{
		TokenType type = lexer->getCurrentToken()->getTokenType();
		if (type == types[i]) {
			lexer->advance();
			if (lexer->getCurrentToken()->getTokenType() == COLON)
			{
				lexer->advance();
				if (type == SCHEMES)
				{
					// need to figure out what our output of ParseScheme will be and what object to put it in
					Scheme SchemeList = Scheme(lexer);
					//schemes.push_back(SchemeList);
				}
				else if (type == FACTS)
				{
					Fact FactList = Fact(lexer);
				}
				else if (type == RULES)
				{
					Rule RuleList = Rule(lexer);
				}
				else if (type == QUERIES)
				{
					Query QueryList = Query(lexer);
					queries.push_back(QueryList);
				}
			}
			else
			{
				lexer->fail = lexer->getCurrentToken();
				cout << "Failure!" << endl << "  " << lexer->fail->toString();
			}
		}
		if (lexer->fail != NULL)
			break;
		i++;
	}

}