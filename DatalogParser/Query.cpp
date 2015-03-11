#pragma once
#include "Query.h"

#include<iostream>
#include "Lex.h"
using namespace std;

Query::Query() 
{


}

Query::~Query()
{

}
string Query::toString() 
{
	return NULL;
}


Query::Query(Lex* lex)
{
	lex->fail = NULL;
	ParsePredicate(lex);

	if (lex->fail != NULL)
	{
		cout << "Failure!" << endl << "  " << lex->fail->toString() << endl;
	}
}

void Query::ParsePredicate(Lex* lex)
{
	
	Predicate* pred = new Predicate(lex);
	//preds.push_back(pred);
	Check_Q_mark(lex);

}

void Query::Check_Q_mark (Lex* lex)
{
	if (lex->getCurrentToken()->getTokenType() == Q_MARK)
	{
		lex->advance();
		if (lex->getCurrentToken()->getTokenType() == Eof)
		{
			return;
		}
		else
			lex->fail = lex->getCurrentToken();
	}
	else
	{
		ParsePredicate(lex);
	}
}