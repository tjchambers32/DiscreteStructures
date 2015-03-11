#pragma once

#include "Parameter.h"
#include "Lex.h"
#include "Datalog.h"
#include <iostream>
#include "Token.h"
#include "TokenType.h"

vector<Token*> ParamList;
using namespace std;

Parameter::Parameter()
{

}
Parameter::~Parameter()
{
	for (int i = 0; i < ParamList.size(); i++)
	{
		delete ParamList[i];
	}
}
Parameter::Parameter(Lex* lex)
{
	ParseParameter(lex);
}
void Parameter::ParseParameter(Lex* lex)
{		// *********REALLY NOT SURE ON THIS PART********* //
	if (lex->getCurrentToken()->getTokenType() == STRING || lex->getCurrentToken()->getTokenType() == ID)
	{
		ParamList.push_back(lex->getCurrentToken());
		if (lex->getCurrentToken()->getTokenType() == STRING)
		{
			//set.insert(lex->getCurrentToken()->getTokenValue())			//something like this
		}
	lex->advance();
	}
	else if (lex->getCurrentToken()->getTokenType() == LEFT_PAREN)
	{
		ParseExpression(lex);
	}
}
void Parameter::ParseExpression(Lex* lex)
{
	lex->advance();

	ParseParameter(lex);

	if (lex->getCurrentToken()->getTokenType() == ADD || lex->getCurrentToken()->getTokenType() == MULTIPLY)
	{
		lex->advance();
	}
	else
		lex->fail = lex->getCurrentToken();

	ParseParameter(lex);

	if (lex->getCurrentToken()->getTokenType() == RIGHT_PAREN)
	{
		lex->advance();
	}
	else
		lex->fail = lex->getCurrentToken();
}

string Parameter::toString()
{
	string str;
	for (int i = 0; i < ParamList.size(); i++)
	{
		str += ParamList[i]->getTokensValue();
	}
	return str;
}