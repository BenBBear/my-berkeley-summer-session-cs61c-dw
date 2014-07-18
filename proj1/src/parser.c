#include "parser.h"
#include "lexer.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#define NULL_CHECK(x) if(x == NULL){			\
		return;									\
	}
#define ASTREE_NODE(r_tree,n_type,m_child,m_last_child)do {	\
		r_tree = malloc(sizeof(AST));						\
		r_tree->type = n_type;								\
		r_tree->val = malloc(strlen(lex->buffer)+1);		\
		strcpy(r_tree->val,lex->buffer);					\
		r_tree->children = m_child;							\
		r_tree->last_child =m_last_child;					\
	} while(0)
int conditional_branch = 0;
int fun_call_mark = 0;
#define None 10
#define FUNCALL_MARK() fun_call_mark = 1
#define FUNCALL_UNMARK() fun_call_mark = 0
#define FUNCTION_DEFINE_MARK() fun_call_mark = 2
#define FUNCALL_MARK_OR_NOT() fun_call_mark == 1
#define FUNCTION_DEFINE_MARK_OR_NOT() fun_call_mark == 2
#define NOTHING ;
#define Totally_Fine ;
#define VALUE 1
#define NOT_EXIST -1
#define ARGUMENT 4
#define NOT(x) !(x)
#define SHOULD_NOT_EXPLORE(x) x == node_VAR || x == node_INT || x == node_STRING


#define INSIDE_CONDITION 1


#define PLUS_ENV(x) do{							\
		strcat(x, "-");							\
		strcat(x,env);							\
	} while(0)

#define PLUS_TOP_ENV(x) do{						\
		strcat(x, "-");							\
	} while(0)




#define NOTHING ;
#define MARK 1
#define FUN_DEFINE_MARK 2

/** An array of the different string values of keywords. */
char *keywords[] = {"and", "or", "+", "-", "*", "/", "lt", "eq",
					"function", "struct", "arrow", "assign", "if",
					"while", "for", "sequence", "intprint", "stringprint",
					"readint"};

/** Sister array of keywords. Keeps track of the corresponding enum. */
int enums[] = {node_AND, node_OR, node_PLUS, node_MINUS, node_MUL, node_DIV,
			   node_LT, node_EQ, node_FUNCTION, node_STRUCT,
			   node_ARROW, node_ASSIGN, node_IF, node_WHILE, node_FOR,
			   node_SEQ, node_I_PRINT, node_S_PRINT, node_READ_INT};
/** A hashmap used for more efficient lookups of (keyword, enum) pairs. */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define AND 2
#define OR 2
#define PLUS 2
#define MINUS 2
#define MUL 2
#define DIV 2
#define LT 2
#define EQ 2
#define FUNCTION -1  			/* at least one */
#define STRUCT -1				/* could be empty */
#define ARROW 2
#define ASSIGN 2
#define IF 3
#define WHILE -1 				/* at least one */
#define FOR -1 					/* at least 3 */
#define SEQ -1					/* at least 1 */
#define I_PRINT 1
#define S_PRINT 1
#define READ_INT 0
int key_arg_nums[] = {AND,OR,PLUS,MINUS,MUL,DIV,LT,EQ,FUNCTION,STRUCT,ARROW,ASSIGN,IF,WHILE,FOR,SEQ,I_PRINT,S_PRINT,READ_INT};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

smap *keyword_str_to_enum;
smap *keyword_or_not;

/** Initializes keyword_str_to_enum so that it contains a map
 *  from the string value of a keyword to its corresponding enum. */
void initialize_keyword_to_enum_mapping();
void initialize_keyword_function_to_numargs();
int lookup_num_args();

void pack_name_env(char * _x_,int _ma_,char *env, int is_top_level) {
	if (is_top_level == 1){
		smap_put(decls, _x_, _ma_);
	}else{
		/* if (smap_get(decls, _x_) == NOT_EXIST){ */
		strcat(_x_, "-");
		strcat(_x_,env);
		smap_put(decls, _x_, _ma_);
	}
	return ;
	/* } */
}

char* cut_env(char* str){
	int i = 0;
	while(str[i] != '-'){
		i++;
	}
	str[i] = '\0';
	return str;
}

void pack_check_name_env(char * _x_,int _ma_,char *env, int is_top_level) {
	if (is_top_level == 1){
		if (smap_get(decls, _x_) == NOT_EXIST)
		{
			if(conditional_branch == 0)
				my_perror("Variable %s used before define", _x_);
			else
				my_perror("Variable %s declaration inside a conditional branch", _x_);
		}else{
			smap_put(decls, _x_, _ma_);
		}
	}else{
		strcat(_x_, "-");
		strcat(_x_,env);
		if (smap_get(decls, _x_) == NOT_EXIST)
		{
			if(smap_get(decls,cut_env(_x_)) == NOT_EXIST)
			{
				if(conditional_branch == 0)
					my_perror("Variable %s used before define", _x_);
				else
					my_perror("Variable %s declaration inside a conditional branch", _x_);
			}
		}else{
			smap_put(decls, _x_, _ma_);
		}
	}
	return ;
	/* } */
}

void parse_init() {
    decls = smap_new();  //smap --> easy to use string hashmap
	smap_put(decls, "None", None);

	stack_sizes = smap_new();
    num_args = smap_new();
    /* strings = smap_l_new(); */


    keyword_str_to_enum = smap_new();
	keyword_or_not = smap_new();
}

void parse_close() {

    smap_del(decls);
    smap_del(stack_sizes);
    smap_del(num_args);

    /* smap_l_del(strings); */

    smap_del(keyword_str_to_enum);
}

void my_perror(const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
	exit(EXIT_FAILURE);
}



AST *build_ast (lexer *lex) { 	/* a big one!! */
    /* TODO: Implement me. */
    /* Hint: switch statements are pretty cool, and they work
     *       brilliantly with enums. */

	AST* r_tree = NULL;
	switch(lex->type){
	case token_STRING:
		ASTREE_NODE(r_tree, node_STRING,NULL,NULL);
		break;
	case token_INT:
		ASTREE_NODE(r_tree, node_INT, NULL, NULL);
		break;
	case token_OPEN_PAREN:
		/* here we need a while loop */
		read_token(lex);

		if(FUNCTION_DEFINE_MARK_OR_NOT()){
			NOTHING;
		}else{
			FUNCALL_MARK();
		}

		r_tree = build_ast(lex); /* here we expect a keyword,var_name */
		/* read_token(lex); */
		if (lex->type != token_CLOSE_PAREN){
			free_ast(r_tree);
			my_perror("Parentheses not match!!");

		}else{
			NOTHING;/* read_token(lex); */	/* if ok,skip this close  parentheses */
		}
		break;
	case token_END:
		r_tree = NULL;
		break;
	case token_SENTINEL:		/* impossible in here */
		read_token(lex);
		r_tree = build_ast(lex);
		break;
	case token_CLOSE_PAREN: 	/* also impossible in here */
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case token_KEYWORD:			/* todo *///only build the tree here,don't modify the symbol table
		FUNCALL_UNMARK();
		ASTREE_NODE(r_tree, lookup_keyword_enum(lex->buffer), NULL, NULL); /* the node_keyword and node_name only differs in here */
		if (lookup_keyword_enum(lex->buffer) == node_FUNCTION){
			FUNCTION_DEFINE_MARK();
		}

		while(1){
			read_token(lex);
			if (lex->type == token_CLOSE_PAREN){
				break;
			}
			if (lex->type == token_END){
				my_perror("parentheses not match!!\n");
			}
			if(r_tree->children == NULL){
				r_tree->children  = malloc(sizeof(AST_lst));
				r_tree->children->next = NULL;
				r_tree->children->val = build_ast(lex);  //first is the (name arg1 arg2) then is the body
				r_tree->last_child = r_tree->children;
			}else{
				r_tree->last_child->next = malloc(sizeof(AST_lst));
				r_tree->last_child = r_tree->last_child->next;

				r_tree->last_child->val = build_ast(lex);
				r_tree->last_child->next = NULL;
			}

		}
		break;					/* must leave  */
	case token_NAME:
		if(FUNCALL_MARK_OR_NOT()){
			FUNCALL_UNMARK();
			ASTREE_NODE(r_tree, node_CALL, NULL, NULL); /* the node_keyword and node_name only differs in here */
			while(1){
				read_token(lex);
				if (lex->type == token_CLOSE_PAREN){
					break;
				}
				if (lex->type == token_END){
					my_perror("parentheses not match!!\n");
				}
				if(r_tree->children == NULL){
					r_tree->children  = malloc(sizeof(AST_lst));
					r_tree->children->next = NULL;
					r_tree->children->val = build_ast(lex);
					r_tree->last_child = r_tree->children;
				}else{
					r_tree->last_child->next = malloc(sizeof(AST_lst));
					r_tree->last_child = r_tree->last_child->next;

					r_tree->last_child->val = build_ast(lex);
					r_tree->last_child->next = NULL;
				}

			}
		}else{
			if (FUNCTION_DEFINE_MARK_OR_NOT()){ //deal with function definition
				FUNCALL_UNMARK();
				ASTREE_NODE(r_tree, node_VAR, NULL, NULL);
				while(1){
					read_token(lex);
					if (lex->type == token_CLOSE_PAREN){
						break;
					}
					if (lex->type == token_END){
						my_perror("parentheses not match!!\n");
					}
					if(r_tree->children == NULL){
						r_tree->children  = malloc(sizeof(AST_lst));
						r_tree->children->next = NULL;
						r_tree->children->val = build_ast(lex);
						r_tree->last_child = r_tree->children;
					}else{
						r_tree->last_child->next = malloc(sizeof(AST_lst));
						r_tree->last_child = r_tree->last_child->next;

						r_tree->last_child->val = build_ast(lex);
						r_tree->last_child->next = NULL;
					}
				}
			}else{
				ASTREE_NODE(r_tree, node_VAR, NULL, NULL);
			}
		}
		break;
	}
    return r_tree;
}
/* struct AST { */
/*     node_type type; /\* The type of  *\/ */
/*     char *val; /\* The source text which spawned this node. *\/ */
/*     AST_lst *children; /\* A list of all of the children of this node*\/ */
/*     AST_lst *last_child; /\* A minor kludge to avoid O(n) insertion times. *\/ */
/* }; */

/* struct AST_lst { */
/*     AST *val; */
/*     AST_lst *next; */
/* }; */
void free_ast (AST *ptr) {
	if (ptr == NULL){
		return;
	}
	free(ptr->val);
	AST_lst* cursor = ptr->children,*prev = cursor;
	while(cursor){
		free_ast(cursor->val);
		prev = cursor;
		cursor = cursor->next;
		free(prev);
	}
	free(ptr);
	return;
}
/* #define FUNCTION -1  			/\* at least one *\/ */
/* #define STRUCT -1				/\* could be empty *\/ */
/* #define ARROW 2 */
/* #define ASSIGN 2 */
/* #define IF 3 */
/* #define WHILE -1 				/\* at least one *\/ */
/* #define FOR -1 					/\* at least 3 *\/ */
/* #define SEQ -1					/\* at least 1 *\/ */


void check_tree_shape(AST *ptr) { /* only check the keyword and function call */
	NULL_CHECK(ptr);
	if (SHOULD_NOT_EXPLORE(ptr->type))
		return;					/* no shape for them */

	int num = lookup_num_args(ptr->val);
	AST_lst* def;
	char* fun_name,*fun_name_call;
	int a_num;
	int call_num;
	switch(num){
	case 2:
		if (AST_lst_len(ptr->children) != 2){
			my_perror("%s requires 2 arguments but now %d given",ptr->val,AST_lst_len(ptr->children));
		}
		break;
	case 1:
		if (AST_lst_len(ptr->children) != 1){
			my_perror("%s requires 1 arguments but now %d given",ptr->val,AST_lst_len(ptr->children));
		}
		break;
	case 3:
		if (AST_lst_len(ptr->children) != 3){
			my_perror("%s requires 3 arguments but now %d given",ptr->val,AST_lst_len(ptr->children));
		}
		break;
	case -1:					/* all those others */
		switch(ptr->type){
		case node_FUNCTION:		/* also collect defun information */
			if (AST_lst_len(ptr->children) == 0){
				/* break; /\* empty function *\/ */
				my_perror("you define a illegal function");
			}
			def = ptr->children;
			fun_name = def->val->val;
			a_num = AST_lst_len(def->val->children);
			if (smap_get(num_args, fun_name)  == -1){
				/* save this function argu number in the smap */

				smap_put(num_args, fun_name, a_num);
			}
			break;
		case node_WHILE:
			if (AST_lst_len(ptr->children) == 0){
				my_perror("you could not use a empty while");
				/* Totally_Fine; */
			}
			break;
		case node_FOR:
			if (AST_lst_len(ptr->children) < 3){
				my_perror("you could not use a for with less than 3 arguments");
				/* Totally_Fine; */
			}
			break;
		case node_STRUCT:
			NOTHING;
			break;

		case node_SEQ:
			if (AST_lst_len(ptr->children) == 0){
				my_perror("your arguments to sequence is too few");
			}
			break;
		case node_CALL:
			fun_name_call = ptr->val;
			call_num = smap_get(num_args, fun_name_call);
			if (call_num == -1){
				/* save this function argu number in the smap */
				my_perror("the function %s is unbound!",fun_name_call);
			}else if((unsigned int)call_num != AST_lst_len(ptr->children)){
				my_perror("the function %s need %d arguments,but %d given!",fun_name_call,call_num,AST_lst_len(ptr->children));
			}
			break;
		case node_INT:case node_STRING:
			if (AST_lst_len(ptr->children) != 0){
				my_perror("You can't use int or string as a function or keyword");
			}
			break;
		default:
			NOTHING;
			break;
		}
		break;
	}
	AST_lst* chd = ptr->children;
	while(chd){
		check_tree_shape(chd->val);
		chd = chd->next;
	}
}


int string_to_int(char *str){
	return strtol(str, (char **)NULL, 10);
}
/* (assign x 1) (function (fib x) (+ x y) (sequence x y)) */

void gather_decls(AST *ast, char *env, int is_top_level) { /* fill in those strings,and desl */
	NULL_CHECK(ast);
	char *varname = NULL;								   /* also need to check use before define */
	AST_lst* function_body = NULL;
	AST_lst* arg_body = NULL;
	varname = ast->val;
	AST_lst* subseq = NULL;
	subseq = ast->children;
	//////////////////////////////////////////////
	switch(ast->type){
	case node_ASSIGN:
		if (conditional_branch == 0){
			gather_decls(ast->children->next->val, env, is_top_level);
			pack_name_env(ast->children->val->val,VALUE,env,is_top_level);
		}else{
			gather_decls(ast->children->next->val, env, is_top_level);
			pack_check_name_env(ast->children->val->val,VALUE,env,is_top_level);
		}

		break;
		////////////////////////////////////////////////////////////////////////////////////////////////////
	case node_VAR:
		pack_check_name_env(varname,VALUE,env,is_top_level);

		break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////
	case node_FUNCTION:			/* new env in here */
		if(is_top_level == 0){
			my_perror("Function define inside a function.");
		}
		arg_body = ast->children->val->children;
		while(arg_body){
			pack_name_env(arg_body->val->val,ARGUMENT,ast->children->val->val,0);
			arg_body=arg_body->next;
		}

		function_body = ast->children->next;
		while(function_body){
			gather_decls(function_body->val, ast->children->val->val, 0);
			function_body = function_body->next;
		}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
		break;
	case node_IF:
		if(conditional_branch == 0){
			conditional_branch = 1;
			while(subseq){
				gather_decls(subseq->val,env, is_top_level);
				subseq = subseq->next;
			}
			conditional_branch = 0;
		}else{
			while(subseq){
				gather_decls(subseq->val,env, is_top_level);
				subseq = subseq->next;
			}
		}
		break;

	case node_WHILE:
		if(conditional_branch == 0){
			gather_decls(subseq->val,env, is_top_level);
			subseq = subseq->next;

			conditional_branch = 1;
			while(subseq){
				gather_decls(subseq->val,env, is_top_level);
				subseq = subseq->next;
			}
			conditional_branch = 0;
		}else{
			while(subseq){
				gather_decls(subseq->val,env, is_top_level);
				subseq = subseq->next;
			}
		}
		break;

	case node_FOR:
		if(conditional_branch == 0){
			gather_decls(subseq->val,env, is_top_level);
			subseq = subseq->next;
			gather_decls(subseq->val,env, is_top_level);
			subseq = subseq->next;

			conditional_branch = 1;
			while(subseq){
				gather_decls(subseq->val,env, is_top_level);
				subseq = subseq->next;
			}
			conditional_branch = 0;
		}else{
			while(subseq){
				gather_decls(subseq->val,env, is_top_level);
				subseq = subseq->next;
			}
		}
		break;

	default:
		while(subseq){
			gather_decls(subseq->val,env, is_top_level);
			subseq = subseq->next;
		}
		break;
	}

}
/////////////////////////////////////////////////////////////////////////////////////////
node_type lookup_keyword_enum(char *str) {
    if (smap_get(keyword_str_to_enum, keywords[0]) == -1) {
		initialize_keyword_to_enum_mapping();
    }
    return smap_get(keyword_str_to_enum, str);
}

int keyword_enum_or_not(char *str) {
    if (smap_get(keyword_or_not, keywords[0]) == -1) {
		initialize_keyword_to_enum_mapping();
    }
    return smap_get(keyword_or_not, str);
}
int lookup_num_args(char *str){
	if (smap_get(num_args, keywords[0]) == -1) {
		initialize_keyword_function_to_numargs();
    }
	return smap_get(num_args, str);
}

///////////////////////////////////////////////////////////////////////


void initialize_keyword_to_enum_mapping() {
    /* Note that enums is an *array*, not a pointer, so this
     * sizeof business is reasonable. */
    size_t num_keywords = sizeof(enums) / sizeof(int);
    for (size_t i = 0; i < num_keywords; i += 1) {
		smap_put(keyword_str_to_enum, keywords[i], enums[i]);
		smap_put(keyword_or_not, keywords[i], 1);
    }
}
void initialize_keyword_function_to_numargs(){
	size_t num_keywords = sizeof(enums) / sizeof(int);
	for (size_t i = 0; i < num_keywords; i += 1) {
		smap_put(num_args, keywords[i], key_arg_nums[i]);
    }
}

//////////////////////////////////////////////////////////////////////


size_t AST_lst_len(AST_lst *lst) {
    int num_fields = 0;
    while (lst) {
		num_fields += 1;
		lst = lst->next;
    }
    return num_fields;
}


smap *num_args;					/* these one only used in the syntax checking phase ,keyword and function args num all store */
/////////////////////////////////////////////////////////
smap *stack_sizes;
smap *decls;
/* smap_l *strings; */
