#pragma once

#include "Predicate.h"
#include "Parameter.h"
#include "Lex.h"
#include "Datalog.h"

#include<iostream>

using namespace std;
vector<string> PredicateRuleString;
vector<string> PredicateQueryString;
vector<Parameter*> params;

Predicate::Predicate()
{

}
Predicate::~Predicate()
{

}
Predicate::Predicate(Lex* lex)
{
	ParsePredicate(lex);
}

string Predicate::toString(string type) 
{
	string str = "" ;
	if(type == "Rule")
	{
		for (int i = 0; i < PredicateRuleString.size(); i++)
		{		
			str += PredicateRuleString[i];
			for (int j = 0; j < params.size(); j++)
			{
				str += params[j]->toString();
			}
		}
	}
	else if (type == "Query")
	{
		for (int i = 0; i < PredicateQueryString.size(); i++)
		{		
			str += PredicateQueryString[i];
		}
	}
return str;
}
void Predicate::ParsePredicate(Lex* lex)
{
	if (lex->getCurrentToken()->getTokenType() == ID)
	{
		PredicateRuleString.push_back(lex->getCurrentToken()->getTokensValue());
		lex->advance();
		if (lex->getCurrentToken()->getTokenType() == LEFT_PAREN)
		{
			PredicateRuleString.push_back(lex->getCurrentToken()->getTokensValue());
			lex->advance();
			ParseParameters(lex);
		}

	}
}
void Predicate::ParseParameters(Lex* lex)
{
	if (lex->getCurrentToken()->getTokenType() == PERIOD)
	{
		PredicateRuleString.push_back(lex->getCurrentToken()->getTokensValue());
		lex->advance();
		return;
	}
	else
	{
		Parameter* parameter = new Parameter(lex);
		params.push_back(parameter);
		ParameterEnd(lex);
	}
}
void Predicate::ParameterEnd(Lex* lex)
{
	if (lex->getCurrentToken()->getTokenType() == COMMA)
	{
		lex->advance();
		ParseParameters(lex);
	}
	else if (lex->getCurrentToken()->getTokenType() == RIGHT_PAREN)
	{
		lex->advance();
		if (lex->getCurrentToken()->getTokenType() == COMMA)
		{
			PredicateRuleString.push_back(lex->getCurrentToken()->getTokensValue());
			lex->advance();
			ParsePredicate(lex);
		}
		else if (lex->getCurrentToken()->getTokenType() == Q_MARK)
		{
			return;
		}
		else if (lex->getCurrentToken()->getTokenType() != PERIOD)
			lex->fail = lex->getCurrentToken();
		else
			return;
	}
	else
		lex->fail = lex->getCurrentToken();
}