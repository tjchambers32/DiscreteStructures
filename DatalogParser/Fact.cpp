#pragma once

#include "Fact.h"
#include "Datalog.h"
#include "Lex.h"
#include<iostream>
#include <string>
#include <sstream>

using namespace std;

vector<string> FactString;
int factcount = 0;
Fact::Fact()
{

}
Fact::~Fact()
{

}
string Fact::getCount()
{	
	stringstream ss;
	ss << factcount;
	string stringcount = ss.str();
	return stringcount;
}
string Fact::toString()
 {
	string str = "  " ;
	
	for (int i = 0; i < FactString.size(); i++)
	{		
		str += FactString[i];
	}
	return str;
}
Fact::Fact(Lex* lex)
{
	int TotalFacts = 0;
	lex->fail = NULL;
	ParseFacts(lex);
	if (lex->fail != NULL)
	{
		cout << "Failure!" << endl << "  " << lex->fail->toString();
	}
}
void Fact::ParseFacts(Lex* lex)
{
	factcount++;
	if (lex->getCurrentToken()->getTokenType() == ID)
	{
		FactString.push_back(lex->getCurrentToken()->getTokensValue());
		lex->advance();
		if (lex->getCurrentToken()->getTokenType() == LEFT_PAREN)
		{
			FactString.push_back(lex->getCurrentToken()->getTokensValue());
			lex->advance();
			if (lex->getCurrentToken()->getTokenType() == STRING)
			{
				FactString.push_back(lex->getCurrentToken()->getTokensValue());
				lex->advance();
				if (ParseStringList(lex))
				{
					if (lex->getCurrentToken()->getTokenType() == RIGHT_PAREN)
					{
						FactString.push_back(lex->getCurrentToken()->getTokensValue());
						lex->advance();
						if (lex->getCurrentToken()->getTokenType() == PERIOD)
						{
							FactString.push_back(lex->getCurrentToken()->getTokensValue());
							lex->advance();
							if (lex->getCurrentToken()->getTokenType() == ID)
							{
								FactString.push_back("\n");
								
								FactString.push_back("  ");
								ParseFacts(lex);
							}
							else if (lex->getCurrentToken()->getTokenType() != RULES)
							{
								lex->fail = lex->getCurrentToken();
							}
							else
								return;
						}
						else 
							lex->fail = lex->getCurrentToken();
					}
					else 
						lex->fail = lex->getCurrentToken();
				}
				else 
					lex->fail = lex->getCurrentToken();
			}
			else 
				lex->fail = lex->getCurrentToken();
		}
		else
			lex->fail = lex->getCurrentToken();
	}
	else 
		lex->fail = lex->getCurrentToken();
	//TotalFacts++;
	return;
}
bool Fact::ParseStringList(Lex* lex)
{
	if (lex->getCurrentToken()->getTokenType() == COMMA)
	{
		FactString.push_back(lex->getCurrentToken()->getTokensValue());
		lex->advance();
		if (lex->getCurrentToken()->getTokenType() == STRING)
		{
			FactString.push_back(lex->getCurrentToken()->getTokensValue());
			lex->advance();
			ParseStringList(lex);
		}
		else
		{
			lex->fail = lex->getCurrentToken();
			return false;
		}
	}
	else if(lex->getCurrentToken()->getTokenType() == RIGHT_PAREN)
	{
		return true;
	}
	else
	{
		lex->fail = lex->getCurrentToken();
		return false;
	}
	return true;
}
int Fact::getNumber()
{
	return TotalFacts;
}