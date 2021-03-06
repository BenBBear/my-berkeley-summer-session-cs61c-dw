#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "parser.h"

/** Prints AST's string literals in the .data segment. */


/** Prints the appropriate code to allocate space in the .data segment
 *  for whatever static memory the program uses. */
void emit_static_memory();


/** Prints AST's code for the .text segment to stdout if the AST
 *  is NOT a function definition. */
void emit_main(AST *ast,int fmark);

/** Prints MIPS code which will exit the program. */
void emit_exit();


/** Prints AST's code for the .text segment to stdout if the AST
 *  IS a function definition. */
void emit_functions(AST *ast);

void emit_macro();

void emit_text();

void emit_structs(AST* ast);

void emit_globals(AST* ast);

void emit_strings(AST *ast);

extern smap* var_addr;
#endif
