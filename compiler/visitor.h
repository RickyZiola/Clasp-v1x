#ifndef VISITOR_H
#define VISITOR_H

#include "lexer.h"
#include "parser.h"

void visitor_num_literal(void *val, Type *typ);

void  visitor_op_unary(TokenTyp operator_type);
void visitor_op_binary(TokenTyp operator_type);

void visitor_var_decl(Token name, Type *typ);
void visitor_var_read(Token name);

#endif