#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.h"
#include "util/util.h"
#include "parser.h"

#define INIT_BUFFER_SIZE 256
#define FIRST 0
#define END_OF_STRING '\0'
#define NUMBER_SIGN(x) x == '+' || x == '-'

#define NUMBER(x) (x >= '0' && x<= '9') || x == '+' || x == '-'

#define NUMBER_OR_NUMBER_SIGN(x) (x >= '0' && x<= '9')

#define VARIABLE_FIRST(x) (x>'A' && x <'Z') || (x>'a' && x<'z') || x == '_'

#define VARIABLE_REST(x) (x>'A' && x <'Z') || (x>'a' && x<'z') || x == '_' || (x > '0' && x< '9')
#define NOT(x) !(x)
#define NOT_EXIST -1
#define TRIVIAL(x) x == ' '|| x == '\n' || x == '\t'


void init_lex(lexer *luthor) {
    luthor->file = NULL;
    luthor->buffer = NULL;
    luthor->type = token_SENTINEL;
    luthor->buff_len = 0;
}

void open_file(lexer *lex, char *filename) {
    if (lex) {
		lex->file = fopen(filename, "r");
		lex->buff_len = INIT_BUFFER_SIZE;
		lex->buffer = safe_calloc(INIT_BUFFER_SIZE * sizeof(char));
    }
}

void close_file(lexer *lex) {
    if (lex) {
	fclose(lex->file);
	free(lex->buffer);
	lex->buff_len = 0;
	lex->buffer = NULL;
    }
}
void read_generic(FILE *file,char *buffer,char end){

}

void read_str(FILE *file,char *buffer){
	char c = fgetc(file);
	int l = 0;
	while(c != '"')
	{
		buffer[l] = c;
		l++;
		c = fgetc(file);
	}
	buffer[l] = END_OF_STRING;
}
void read_int(lexer *lex){
	FILE * file = lex->file;
	char* buffer = lex->buffer;
	char c = fgetc(file);
	int l = 0; // need cope with the +,- in the beginning
	if(NUMBER_SIGN(c)){
		buffer[l] = c;
		l++;
		c = fgetc(file);
	}
	if (NUMBER(c)){
		while(NUMBER(c)){
			buffer[l] = c;
			l++;
			c = fgetc(file);
		}
		ungetc(c,file);
		buffer[l] = END_OF_STRING;
		lex->type = token_INT;
		return;
	}else{ //only a + or - no number
		ungetc(c,file);
		buffer[l] = END_OF_STRING;
		lex->type = token_KEYWORD;
		return;
	}
}
void read_name(FILE *file,char *buffer){
	char c = fgetc(file);
	int l = 0;
	if (NOT(VARIABLE_FIRST(c))){
		perror("Variable Name should only begin with [a-zA-Z_]!");
		return;
	} else {
		buffer[l] = c;
		l++;
		c = fgetc(file);
	}
	while(VARIABLE_REST(c))
	{
		buffer[l] = c;
		l++;
		c = fgetc(file);
	}
	ungetc(c,file);
	buffer[l] = END_OF_STRING;
}


void read_token(lexer *lex) {
	char c;
	int l = 0;
	token_type prev_type = lex->type;
	switch (prev_type){
	case token_OPEN_PAREN:  //the token after a ( must be a function or keyword so
		while(1){ //could be anything
			c = fgetc(lex->file);
			if (TRIVIAL(c)){
				continue;
			}
			if (c == EOF){
				lex->type = token_END;
				lex->buffer[FIRST] = END_OF_STRING;
				return;
			}
			if (c == '('){//parenthesis
				lex->type = token_OPEN_PAREN;
				lex->buffer[FIRST] = '(';
				lex->buffer[FIRST+1] = END_OF_STRING;
				return;
			}
			if (c == ')'){
				lex->type = token_CLOSE_PAREN;
				lex->buffer[FIRST] = ')';
				lex->buffer[FIRST+1] = END_OF_STRING;
				return;
			}

			///////read a keyword or a token_name
			while(NOT(TRIVIAL(c))){
				lex->buffer[l] = c;
				l++;
				c = fgetc(lex->file);
			}
			ungetc(c,lex->file);
			lex->buffer[l] = END_OF_STRING;

			if (keyword_enum_or_not(lex->buffer) == NOT_EXIST){
				lex->type = token_NAME;
				return;
			}else{
				lex->type = token_KEYWORD;
				return;
			}
		}
		break;

	default:
		while(1){ //could be anything
			c = fgetc(lex->file);
			if (c == EOF){
				lex->type = token_END;
				lex->buffer[FIRST] = END_OF_STRING;
				return;
			}
			if (TRIVIAL(c)){
				continue;
			}
			if (c == '('){//parenthesis
				lex->type = token_OPEN_PAREN;
				lex->buffer[FIRST] = '(';
				lex->buffer[FIRST+1] = END_OF_STRING;
				return;
			}
			if (c == ')'){
				lex->type = token_CLOSE_PAREN;
				lex->buffer[FIRST] = ')';
				lex->buffer[FIRST+1] = END_OF_STRING;
				return;
			}

			if (c == '"'){//this is a string
				lex->type = token_STRING;
				read_str(lex->file,lex->buffer);
				return;
			}
			if (NUMBER_OR_NUMBER_SIGN(c)){  //this is a interger,because we do away with returning function as values
				ungetc(c,lex->file);
				read_int(lex);
				return;
			}
			//otherwise is a  variable
			ungetc(c, lex->file);
			lex->type = token_NAME;
			read_name(lex->file,lex->buffer);
			return;
		}
		break;
	}


}

token_type peek_type(lexer *lex) {
    if (!lex) {
	return token_SENTINEL;
    }
    if (lex->type == token_SENTINEL) { //token_SENTINEL ---> mark begin of lexing
		read_token(lex); //this line would lex out a token,the SENTINEL only used once in the begin, and END vice visa.
    }
    return lex->type;
}

char *peek_value(lexer *lex) {
    if (!lex) {
	return NULL;
    }
    if (lex->type == token_SENTINEL) {
	read_token(lex);
    }
    return lex->buffer;
}
