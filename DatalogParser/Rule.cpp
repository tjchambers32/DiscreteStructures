#include "Rule.h"
#include<iostream>
#include<sstream>

using namespace std;

vector<string> RuleString;
vector<Predicate*> PredString;
int rulecount;
Rule::Rule() 
{


}
Rule::~Rule()
{

}
string Rule::toString() 
{
	string str = "  " ;

	for (int i = 0; i < RuleString.size(); i++)
	{		
		str += RuleString[i];
		
	}


return str;
}
string Rule::getCount()
{
	stringstream ss;
	ss << rulecount;
	string stringcount = ss.str();
	return stringcount;
}
Rule::Rule(Lex* lex)
{
	lex->fail = NULL;
	ParseHeadPredicate(lex);

	if(lex->getCurrentToken()->getTokenType() == COLON_DASH)
	{
		RuleString.push_back(lex->getCurrentToken()->getTokensValue());
		lex->advance();
		AddPredicate(lex);
	}
	if (lex->fail != NULL)
	{
		cout << "Failure!" << endl << "  " << lex->fail->toString() << endl;
	}
}

void Rule::ParseRuleList(Lex* lex)
{

}

void Rule::AddPredicate(Lex* lex)
{
	Predicate* pred = new Predicate(lex);
	PredString.push_back(pred);
	RuleString.push_back(pred->toString("Rule"));
	for (int i = 0; i < PredString.size(); i++)
	{
		cout << endl << endl << endl;
		cout << PredString[i]->toString("Rule");
		cout << endl << endl << endl;
	}
	if (lex->getCurrentToken()->getTokenType() == COMMA && lex->fail == NULL)
	{
		RuleString.push_back(lex->getCurrentToken()->getTokensValue());
		lex->advance();
		AddPredicate(lex);
	}
	else if(lex->getCurrentToken()->getTokenType() == PERIOD)
	{
		RuleString.push_back(lex->getCurrentToken()->getTokensValue());
		Predicate* predicate = new Predicate;
		lex->advance();
		return;
	}
	else
		lex->fail = lex->getCurrentToken();
}





//Head Predicate Stuff
void Rule::ParseHeadPredicate(Lex* lex)
{	
	rulecount++;
	if (lex->getCurrentToken()->getTokenType() == ID)
	{
		RuleString.push_back(lex->getCurrentToken()->getTokensValue());
		lex->advance();
		if (lex->getCurrentToken()->getTokenType() == LEFT_PAREN)
		{
			RuleString.push_back(lex->getCurrentToken()->getTokensValue());
			lex->advance();
			ParseIDList(lex);
		}
		else 
			lex->fail = lex->getCurrentToken();
	}
	else
		lex->fail = lex->getCurrentToken();
}
void Rule::ParseIDList(Lex* lex)
{
	if (lex->getCurrentToken()->getTokenType() == ID)
	{
		RuleString.push_back(lex->getCurrentToken()->getTokensValue());
		lex->advance();
		ParseCheckEnd(lex);
	}
	else
		lex->fail = lex->getCurrentToken();
}
void Rule::ParseCheckEnd(Lex* lex)
{
	if (lex->getCurrentToken()->getTokenType() == COMMA)
	{
		RuleString.push_back(lex->getCurrentToken()->getTokensValue());
		lex->advance();
		ParseIDList(lex);
	}
	else if (lex->getCurrentToken()->getTokenType() == RIGHT_PAREN)
	{
		RuleString.push_back(lex->getCurrentToken()->getTokensValue());
		lex->advance();
	}
	else 
		lex->fail = lex->getCurrentToken();
}