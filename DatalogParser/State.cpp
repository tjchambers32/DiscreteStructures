#include "State.h"

using namespace std;

string StateToString(State tokenType){
    string result = "";
    switch(tokenType){
		case Id:						 result = "Id"; break;
		case Multiply:					 result = "Multiply"; break;
		case Add:						 result = "Add"; break;
		case Undefined:					 result = "Undefined"; break;
		case Right_Paren:                result = "Right_Paren"; break;
		case Left_Paren:				 result = "Left_Paren"; break;
		case Q_Mark:                     result = "Q_Mark"; break;
		case Whitespace:				 result = "Whitespace"; break;
        case Comma:                      result = "Comma"; break;
        case Period:                     result = "Period"; break;
        case SawColon:                   result = "SawColon"; break;
        case Colon_Dash:                 result = "Colon_Dash"; break;
        case SawAQuote:                  result = "SawAQuote"; break;
        case ProcessingString:           result = "ProcessingString"; break;
        case PossibleEndOfString:        result = "PossibleEndOfString"; break;
        case Start:                      result = "Start"; break;
		case MultiLine:				     result = "MultiLine"; break;
		case SingleLine:				 result = "SingleLine"; break;
		case Comment:					 result = "Comment"; break;
		case CommentEnd:				 result = "CommentEnd"; break;
        case End:                        result = "End"; break;

    }
    return result;
};
