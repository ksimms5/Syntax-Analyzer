#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
void addChar(); 
void getChar(); 
void getNonBlank();
int lex();
int lookup(char c); 
bool isKeyword();
#define LETTER 0
#define DIGIT 1
#define DOLLAR 2
#define UNKNOWN 41
#define INT_LIT 3 
#define IDENT 4 
#define FLOAT_LIT 38 
#define ASSIGN_OP 5 
#define INT_CODE 35     
#define FLOAT_CODE 36    
#define SWITCH_CODE 37
#define FOR_CODE 30 
#define IF_CODE 31 
#define ELSE_CODE 32 
#define WHILE_CODE 33 
#define DO_CODE 34 
#define POS_SIGN 8  //- 
#define NEG_SIGN 9  //+ 
#define DIV_SIGN  10 
#define MULT_SIGN 11 
#define LEFT_PAREN 12 //( 
#define RIGHT_PAREN 13  //) 
#define SEMICOLON 14 //; 
#define E_SIGN 40 
bool flag;
void program(); 
void optDeclarationList(); 
void declarationList(); 
void declaration(); 
void statement(); 
void statementList(); 
void assign(); 
void expression(); 
void term(); 
void factor(); 
void primary(); 
void expressionPrime(); 
void termPrime(); 
void loop_statement();
void  loop_while();
void  loop_do();
void  loop_for();
void type(){
	 if( nextToken == INT_CODE) 
        { 
			cout<<" Enter <Integer>"<<endl; 
			cout<<" Exit <Integer>"<<endl; 
            lex(); 
        } 
	 else if ( nextToken == FLOAT_CODE) 
        { 
			cout<<" Enter <Float>"<<endl; 
			cout<<" Exit <Float>"<<endl; 
            lex(); 
        } 
    else 
		cout<<"????????Error: Type not properly given \n"<<endl; 
  
} 
  
void declaration(){ 
  
		cout<<" Enter <Declaration>"<<endl; 
	type(); 		// Type 
	        if ( nextToken != IDENT) 
	            cout<<"	Error: no identifier "<<endl; 
			else 
			{ 
    	        lex(); 
    	        if(nextToken != SEMICOLON) 
    	        { 
    	        	if( nextToken != ASSIGN_OP) 
    	        		cout<<"????????Error: No Assignment Operator. \n"<<endl; 
    	        	lex(); 
    	        	if( nextToken != INT_LIT && nextToken != FLOAT_LIT) 
    	        		cout<<"????????Error: No Integral Literal. \n"<<endl; 
    	        	lex(); 
    	    	} 
					if( nextToken == SEMICOLON) 
                		{ 
							cout<<" Exit <Declaration>"<<endl; 
							lex(); 
						} 
                	 
                else 
                	cout<<"????????Error: no semicolon after declaration. \n"<<endl; 
            } 
  
} 
void declarationList() 
{ 
		cout<<" Enter <DeclarationList>"<<endl; 
  
	if( nextToken == INT_CODE || nextToken == FLOAT_CODE ) 
     	declaration(); 
     
	while( nextToken == INT_CODE|| nextToken == FLOAT_CODE ) 
     	{ 
			declaration(); 
		} 
		cout<<" Exit <DeclarationList>"<<endl; 
} 
void optDeclarationList() 
{ 
	cout<<" Enter <OptDeclarationList>"<<endl; 
	if( nextToken == INT_CODE || nextToken == FLOAT_CODE ) 
	{ 
     	declarationList(); 
     } 
		cout<<" Exit <OptDeclarationList>"<<endl; 
} 
void factor() 
{ 
	cout<<" Enter <Factor>"<<endl; 
  
	if (nextToken == LEFT_PAREN) 
	{ 
		lex(); 
		expression(); 
		if(nextToken != RIGHT_PAREN ) 
			cout<<"????????ERROR: Right Parenthesis is missing."<<endl; 
	}	 
		lex(); 
		cout<<" Exit <Factor>"<<endl; 
  
} 
void termPrime() 
{ 
		cout<<" Enter <TermPrime>"<<endl; 
  
		if(nextToken == MULT_SIGN || nextToken == DIV_SIGN) 
		{ 
			lex(); 
			factor(); 
			termPrime(); 
		} 
		cout<<" Exit <TermPrime>"<<endl; 
} 
void expressionPrime() 
{ 
	cout<<" Enter <ExpressionPrime>"<<endl; 
		if(nextToken == POS_SIGN || nextToken == NEG_SIGN) 
		{ 
			lex(); 
			term(); 
			expressionPrime(); 
		} 
	cout<<" Exit <ExpressionPrime>"<<endl; 
}	 
void term() 
{ 
	cout<<" Enter <Term>"<<endl; 
	factor(); 
	termPrime(); 
	cout<<" Exit <Term>"<<endl; 
} 
void expression() 
{ 
	cout<<" Enter <Expression>"<<endl; 
	term(); 
	expressionPrime(); 
	cout<<" Exit <Expression>"<<endl; 
} 
void assign() 
{ 
	cout<<" Enter <Assignment>"<<endl; 
  
	lex(); 
	if(nextToken != ASSIGN_OP) 
		cout<<"????????ERROR: Assignment Operator is missing."<<endl; 
	lex(); 
	expression(); 
	if(nextToken != SEMICOLON) 
		cout<<"????????ERROR: Semicolon is missing."<<endl; 
	cout<<" Exit <Assignment>"<<endl; 
	lex(); 
  
} 
void statement() 
{ 
	cout<<" Enter <Statement>"<<endl; 
	    if( nextToken == IDENT) 
     	assign(); 
	cout<<" Exit <Statement>"<<endl; 
     
} 
void statementList(){ 
	 
	cout<<" Enter <StatementList>"<<endl; 
		while( nextToken != EOF) 
    	{ 
			statement(); 
		} 
	cout<<" Exit <StatementList>"<<endl; 
  
} 
void program(){ 
		cout<<" Enter <Program>"<<endl; 
		optDeclarationList(); 
		 
		statementList(); 
		cout<<" Exit <Program>"<<endl; 
		 
} 
void  loop_statement() { 
	cout<<" Enter <LoopStatement>"<<endl; 
if (nextToken != IF_CODE)  
cout<<"????ERROR"<<endl; 
else{ 
lex(); 
if(nextToken!= LEFT_PAREN) 
cout<<"????ERROR"<<endl; 
		else{ 
lex(); 
expression(); 
if(nextToken!= RIGHT_PAREN) 
cout<<"????ERROR"<<endl; 
	else{  
	lex(); 
	statement(); 
	if(nextToken == ELSE_CODE) 
	lex(); 
	statement(); 
		} 
	}	 
}  
	cout<<" Exit <LoopStatement>"<<endl; 
} 
void  loop_while() { 
	cout<<" Enter <LoopWhile>"<<endl; 
if(nextToken != WHILE_CODE)  
cout<<"????ERROR"<<endl; 
else{ 
lex(); 
if(nextToken!= LEFT_PAREN) 
cout<<"????ERROR"<<endl; 
		else{ 
lex(); 
expression(); 
if(nextToken!= RIGHT_PAREN) 
cout<<"????ERROR"<<endl; 
	else{  
	lex(); 
	statement(); 
	 
} 
	}	 
} 
	cout<<" Exit <LoopWhile>"<<endl; 
} 
void  loop_do() { 
	cout<<" Enter <LoopDo>"<<endl; 
if(nextToken != DO_CODE)  
cout<<"????ERROR"<<endl; 
else{ 
lex(); 
if(nextToken!= LEFT_PAREN) 
cout<<"????ERROR"<<endl; 
		else{ 
lex(); 
expression(); 
if(nextToken!= RIGHT_PAREN) 
cout<<"????ERROR"<<endl; 
	else{  
	lex(); 
	statement(); 
	}	 
}  
} 
	cout<<" Exit <LoopStatement>"<<endl; 
} 
void  loop_for() { 
	cout<<" Enter <LoopFOR>"<<endl; 
if(nextToken != FOR_CODE)  
cout<<"????ERROR"<<endl; 
else{ 
lex(); 
if(nextToken!= LEFT_PAREN) 
cout<<"????ERROR"<<endl; 
		else{ 
lex(); 
expression(); 
if(nextToken!= SEMICOLON) 
cout<<"????ERROR"<<endl; 
	else{  
	lex(); 
	if(nextToken!= SEMICOLON) 
cout<<"????ERROR"<<endl; 
		else{ 
		lex(); 
		expression(); 
		if(nextToken!= RIGHT_PAREN) 
cout<<"????ERROR"<<endl; 
	else{ 
			lex(); 
			statement(); 
} 
	}	 
}  
} 
} 
	cout<<" Exit <LoopStatement>"<<endl; 
}      
int lookup(char ch) 
{ 
  
switch(ch){ 
  case ';': 
         addChar(); 
         nextToken=SEMICOLON; break; 
  case '(': 
         addChar(); 
         nextToken=LEFT_PAREN; break; 
  case ')': 
    addChar(); 
    nextToken=RIGHT_PAREN; break; 
  case '=': 
    addChar(); 
    getChar(); 
    nextToken=ASSIGN_OP; break; 
  case '-': 
    addChar(); 
    nextToken=NEG_SIGN; break; 
  
  case '+': 
      addChar(); 
      nextToken=POS_SIGN; break; 
   
  case '/': 
	addChar();   //put character from nextChar into the place the lexeme  is being accumulated 
	nextToken = DIV_SIGN; break; 
  
  case '*': 
    addChar();   //put character from nextChar into the place the lexeme  is being accumulated 
	nextToken = MULT_SIGN; break; 
  
  case '#' : addChar(); nextToken = EOF; break; 
  
  default: addChar(); nextToken = EOF; break; 
  
            }//end switch 
  
return nextToken; 
}
//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
ifstream infile;
int main() {
infile.open("input.txt");
if(!infile)
{
	cout<<"????? Error opening input file." <<endl;
return 0;
}
else
{
getChar();
lex();
program();
system("pause");
}
return(0);
}
void addChar(){ 
    if ( lexLen<=500) 
    { 
        lexeme[lexLen++]=nextChar; 
        lexeme[lexLen]=0; 
    } 
    else 
        cout<<"????????Error- lexeme is too long "<<endl; 
              } 
void getChar(){ 
     infile.get(nextChar); 
    if((nextChar) != EOF) 
    { 
        if (isalpha(nextChar)) 
            charClass=LETTER; 
        else if(isdigit(nextChar)) 
            charClass=DIGIT; 
        else if(nextChar=='$') 
            charClass=DOLLAR; 
        else 
            charClass=UNKNOWN; 
    }
 else 
        charClass=EOF; 
  
}
void getNonBlanck() 
{ 
    while(isspace(nextChar)) 
        getChar(); 
} 
int lex(){ 
   lexLen=0;//lexeme array is empty 
   getNonBlanck(); 
  
   flag = false ; 
   int count=0; 
   switch(charClass){ 
	 case LETTER: case DOLLAR: 
          addChar(); 
          getChar(); 
          while ( charClass == LETTER || charClass == DIGIT|| nextChar=='_') 
          { 
               addChar(); 
               getChar(); 
          } 
          if(isKeyword()) 
              break; 
	 else if (strcmp(lexeme, "if") == 0) {
            nextToken = IF_CODE;
        }
        else if (strcmp(lexeme, "else") == 0) {
            nextToken = ELSE_CODE;
        }
	      else if (strcmp(lexeme, "while") == 0) {
            nextToken = WHILE_CODE;
        }
        else if (strcmp(lexeme, "do") == 0) {
            nextToken = DO_CODE;
 	}
	else if (strcmp(lexeme, "for") == 0) {
            nextToken = FOR_CODE;
        }
          else 
          { 
              nextToken = IDENT; 
              break; 
          } 
case DIGIT: 
          do 
          { 
              addChar(); 
              getChar(); 
  
              if(nextChar=='.') 
                    { 
                        flag=true; 
                        count++; 
                    } 
                if(count>1) 
                { 
                    printf("Error float cannot has more than one \'.\' \n"); 
                    break; 
                } 
          }while(charClass == DIGIT || nextChar=='.'); 
  
           if(flag) 
           { 
               nextToken = FLOAT_LIT; 
               break; 
           } 
           else 
           { 
               nextToken = INT_LIT; 
                break; 
            } 
  
      case EOF: 
        nextToken = EOF; 
        lexeme[0]='E'; 
        lexeme[1]='O'; 
        lexeme[2]='F'; 
        lexeme[3]=0; 
        break; 
      case UNKNOWN: 
           lookup(nextChar); getChar(); break; 
  
  
        }
  cout<<" Next token is: "<<nextToken<<"   Next lexeme is "<<lexeme<<endl; 
		 
        return nextToken; 
  
} 
  
bool isKeyword() 
{ 
    if (!strcmp(lexeme, "int")) 
    { 
        nextToken=INT_CODE; 
        return true; 
    } 
    else if (!strcmp(lexeme, "float")) 
    { 
        nextToken = FLOAT_CODE; 
        return true; 
    } 
    else 
      return (false); 
} 

