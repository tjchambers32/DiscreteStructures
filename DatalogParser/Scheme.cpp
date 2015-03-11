#pragma once

#include "Scheme.h"
#include "Lex.h"
#include "Datalog.h"
#include "Token.h"
#include<iostream>
#include <string>
#include <sstream>
int count = 0;
vector<string> SchemeString;

using namespace std;

Scheme::Scheme()
{
	
}
Scheme::Scheme(Lex* lex) 
{
	lex->fail = NULL;
	if (!ParseSchemes(lex))
	{
//		lex->fail = lex->getCurrentToken();
		cout << "Failure!" << endl << "  " << lex->fail->toString();
	}
	//else 
		//cout << toString() <<endl;


}
Scheme::~Scheme()
{

}

string Scheme::getCount()
{	
	stringstream ss;
	ss << count;
	string stringcount = ss.str();
	return stringcount;
}
string Scheme::toString() 
 {
	string str = "  " ;
	//vector<string> 
	for (int i = 0; i < SchemeString.size(); i++)
	{		
		str += SchemeString[i];
		
	}
	//cout << str << endl;
return str;
}

bool Scheme::ParseSchemes(Lex* lex)
{
	count ++;
	if (lex->getCurrentToken()->getTokenType() == ID)
		{
			SchemeString.push_back(lex->getCurrentToken()->getTokensValue());
			

			lex->advance();
			
			if (lex->getCurrentToken()->getTokenType() == LEFT_PAREN)
			{
				SchemeString.push_back(lex->getCurrentToken()->getTokensValue());
				
				lex->advance();
				if (lex->getCurrentToken()->getTokenType() == ID)
				{
					SchemeString.push_back(lex->getCurrentToken()->getTokensValue());
					
					lex->advance();
					if (ParseIDList(lex))
					{
						SchemeString.push_back(lex->getCurrentToken()->getTokensValue());
						
						lex->advance();
						if (lex->getCurrentToken()->getTokenType() == ID)
						{
							SchemeString.push_back("\n");
							//count++;
							SchemeString.push_back("  ");

							ParseSchemes(lex);
						}
						else if (lex->getCurrentToken()->getTokenType() == FACTS)
						{
							/*for(int i = 0; i < SchemeString.size(); i++)
							{
								cout << SchemeString[i];
							}*/
							
							
							return true;
						}
						else
						{
							lex->fail = lex->getCurrentToken();
							return false;
						}
					}
					else
					{
						lex->fail = lex->getCurrentToken();	
						return false;
					}
				}
				else
				{
					lex->fail = lex->getCurrentToken();
					return false;
				}
			}
			else
			{
				lex->fail = lex->getCurrentToken();
				return false;
			}
		}
	else 
	{
		lex->fail = lex->getCurrentToken();
		return false;
	}
	if (lex->fail != NULL)
		return false;
	else
		return true;
}
bool Scheme::ParseIDList(Lex* lex)
{
		if (lex->getCurrentToken()->getTokenType() == COMMA)
		{
			SchemeString.push_back(lex->getCurrentToken()->getTokensValue());
			lex->advance();
			if (lex->getCurrentToken()->getTokenType() == ID)
			{
				SchemeString.push_back(lex->getCurrentToken()->getTokensValue());
				lex->advance();
				ParseIDList(lex);
			}
			else
			{	
				lex->fail = lex->getCurrentToken();
				return false;
			}
		}
		else if (lex->getCurrentToken()->getTokenType() == RIGHT_PAREN)
			return true;
		else
		{	
			lex->fail = lex->getCurrentToken();
			return false;
		}
	return true;
}