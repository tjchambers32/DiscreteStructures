#pragma once

#include "Lex.h"
#include "Input.h"
#include "TokenType.h"
#include "Utils.h"
#include "Token.h"
#include "Datalog.h"
#include "Scheme.h"
#include <iostream>
#include <cctype>
#include <fstream>

using namespace std;

Lex::Lex() {
	input = new Input();
	generateTokens(input);
}

Lex::Lex(const char* filename) {
	input = new Input(filename);
	generateTokens(input);
}

Lex::Lex(istream& istream) {
	input = new Input(istream);
	generateTokens(input);
}

Lex::Lex(const Lex& lex) {
	input = new Input(*lex.input);
	tokens = new vector<Token*>();

	vector<Token*>::iterator iter;
	for(iter=lex.tokens->begin(); iter != lex.tokens->end(); iter++) {
		Token* newToken = new Token(**iter);
		tokens->push_back(newToken);
	}

	index = lex.index;
	state = lex.state;
}

Lex::~Lex() {
	for (int i = 0; i < tokens->size(); i++) {
		delete (*tokens)[i];
	}
	delete tokens;
	delete input;
}

bool Lex::operator==(const Lex& lex) {
	bool result = (tokens->size() == lex.tokens->size()) && (index == lex.index);
	if(result) {
		vector<Token*>::iterator iter1;
		vector<Token*>::iterator iter2;
		iter1 = tokens->begin();
		iter2 = lex.tokens->begin();
		while(result && iter1 != tokens->end() && iter2 != lex.tokens->end()) {
			result = **iter1 == **iter2;
			iter1++;
			iter2++;
		}
		result = result && iter1 == tokens->end() && iter2 == lex.tokens->end();
	}
	return result;
}

string Lex::toString() const {
	int count = 0;
	string result;
	while(count < tokens->size()) {
		Token* token = (*tokens)[count];
		result += token->toString();
		count++;
	}
	result += "Total Tokens = ";
	string countToString;
	result += itoa(countToString, count);
	result += "\n";
	return result;
}

void Lex::generateTokens(Input* input) {
	tokens = new vector<Token*>();
	index = 0;

	state = Start;
	while(state != End) {
		state = nextState();
	}
}

Token* Lex::getCurrentToken() {
	return (*tokens)[index];
}

void Lex::advance() {
	index++;
}

bool Lex::hasNext() {
	return index < tokens->size();
}

State Lex::nextState() {
	State result;
	char character;
	switch(state) {
		/*case Schemes:			  emit(SCHEMES); result = getNextState();
		case Facts:				  emit(FACTS); result = getNextState();
		case Rules:				  emit(RULES); result = getNextState();
		case Queries:			  emit(QUERIES); result = getNextState();*/
	case Undefined:			  emit(UNDEFINED); result = getNextState(); break;
	case Multiply:			  emit(MULTIPLY); result = getNextState(); break;
	case Add:				  emit(ADD); result = getNextState(); break;
	case Left_Paren:          emit(LEFT_PAREN); result = getNextState(); break;
	case Right_Paren:         emit(RIGHT_PAREN); result = getNextState(); break;
	case Q_Mark:			  emit(Q_MARK); result = getNextState(); break;
	case Whitespace:		  result = getNextState(); break;
	case Start:               result = getNextState(); break;
	case Comma:               emit(COMMA); result = getNextState(); break;
	case Period:              emit(PERIOD); result = getNextState(); break;
	case Comment:
		character = input->getCurrentCharacter();
		if(character == '|') {
			result = MultiLine;
			input->advance();
		}
		else if (character == -1 || character == '/n' || character == 10) { // WHY DOES THIS WORK??????
			emit(COMMENT);
			result = getNextState();
		}
		else {
			result = SingleLine;
			input->advance();
		}
		break;
	case MultiLine:
		character = input->getCurrentCharacter();
		if (character == '|' ) {
			result = CommentEnd;
			input->advance();
		}
		else if (character == -1) {
			result = Undefined;
		}
		else {
			result = MultiLine;
			input->advance();
		}
		break;
	case CommentEnd:
		character = input->getCurrentCharacter();
		if (character == '#') {
			input->advance();
			//emit(COMMENT);
			result = getNextState();
		}
		break;
	case SingleLine:
		character = input->getCurrentCharacter();
		if (character == -1 || character == '/n' || character == '/r' || character == 10) {
			//emit(COMMENT);
			result = getNextState();
		}
		else { //comment continues
			input->advance();
			result = SingleLine;
		}
		break;
	case SawColon:
		character = input->getCurrentCharacter();
		if(character == '-') {
			result = Colon_Dash;
			input->advance();
		} else { //Every other character
			//throw "ERROR:: in case SawColon:, Expecting  '-' but found " + character + '.';
			emit(COLON); result = getNextState(); break;
		}
		break; 
	case Colon_Dash:          emit(COLON_DASH); result = getNextState(); break;
	case SawAQuote:  
		character = input->getCurrentCharacter();
		if(character == '\'') {
			result = PossibleEndOfString;
		} else if(character == -1) {
			//throw "ERROR:: in Saw_A_Quote::nextState, reached EOF before end of string.";
			result = Undefined;
		} else { //Every other character
			result = ProcessingString;
		}
		input->advance();
		break;
	case ProcessingString:  
		character = input->getCurrentCharacter();
		if(character == '\'') {
			result = PossibleEndOfString;
		} else if(character == -1) {
			//throw "ERROR:: in ProcessingString::nextState, reached EOF before end of string.";
			result = Undefined;
		} else { //Every other character
			result = ProcessingString;
		}
		input->advance();
		break;
	case PossibleEndOfString:
		if(input->getCurrentCharacter() == '\'') {
			input->advance();
			result = ProcessingString;
		} else { //Every other character
			emit(STRING);
			result = getNextState();
		}
		break;
	case End:
		//throw "ERROR:: in End state:, the Input should be empty once you reach the End state.";
		break;
	case Id:
		character = input->getCurrentCharacter();
		if (isalpha(character) || isdigit(character)) {
			input->advance();
			result = Id;
		}
		else {
			string PossibleKeyword = input->getTokensValue();
			if (PossibleKeyword == "Schemes")
				emit(SCHEMES);
			else if(PossibleKeyword == "Facts")
				emit(FACTS);
			else if (PossibleKeyword == "Queries")
				emit(QUERIES);
			else if (PossibleKeyword == "Rules")
				emit(RULES);
			else
				emit(ID);
			result = getNextState();
		}
		break;

	};
	return result;
}

State Lex::getNextState() {
	State result;
	char currentCharacter = input->getCurrentCharacter();

	//The handling of checking for whitespace and setting the result to Whitespace and
	//checking for letters and setting the result to Id will probably best be handled by
	//if statements rather then the switch statement.
	if (isspace(currentCharacter)) {
		result = Whitespace;
		input->advance();
		input->mark();
		return result;
	}
	else if (isalpha(currentCharacter))  {
		input->advance();
		result = Id;
		return result;
	}
	else {
		switch(currentCharacter) {
		case '#'  : result = Comment; break; 
		case '*'  : result = Multiply; break;
		case '+'  : result = Add; break;
		case '('  : result = Left_Paren; break;
		case ')'  : result = Right_Paren; break;
		case '?'  : result = Q_Mark; break;
		case ','  : result = Comma; break;
		case '.'  : result = Period; break;
		case ':'  : result = SawColon; break;
		case '\'' : result = ProcessingString; break;
		case -1   : emit(Eof); result = End; break;
		default:
			result = Undefined; break;
			/*	string error = "ERROR:: in Lex::getNextState, Expecting  ";
			error += "'\'', '.', '?', '(', ')', '+', '*', '=', '!', '<', '>', ':' but found ";
			error += currentCharacter;
			error += '.';
			throw error.c_str()*/;
		}
	}
	input->advance();
	return result;
}

void Lex::emit(TokenType tokenType) {
	Token* token = new Token(tokenType, input->getTokensValue(), input->getCurrentTokensLineNumber());
	storeToken(token);
	input->mark();
}

void Lex::storeToken(Token* token) {
	//This section shoud ignore whitespace and comments and change the token type to the appropriate value
	//if the value of the token is "Schemes", "Facts", "Rules", or "Queries".


	//maybe... if tokenType == Whitespace DON'T push_back.
	tokens->push_back(token);
}

int main(int argc, char* argv[]) {
	Lex lex(argv[1]);
	string str;
	Scheme schemes;
	//cout << lex.toString();
	Datalog parser = Datalog(&lex);
	cout << parser.toString(&lex, str);

	cout << str;
	system("pause");
	return 0;
}
