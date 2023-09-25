#include "parser.h"

void parse_err(Token tok, const char *errf, ...) {
    hadErr    = true;
    panicMode = true;
    va_list args;
    va_start(args, errf);

    fprintf(stderr, "Parse error at line %d of file %s: \"", tok.line, get_current_file());
    vfprintf(stderr, errf, args);
    fprintf(stderr, "\"\n");
    parser_synchronize();
}

void parser_synchronize() {
    panicMode = false;
    return; // TODO
}

void consume(TokenTyp typ, const char *errf, ...) {
    va_list args;
    va_start(args, errf);

    if (token_current().typ != typ) parse_err(token_current(), errf, args);
    advance();
}

void advance() {
    token_next();
}

void parse_precedence(OperatorPrecedence precedence) {
    advance();
    ParseFn prefixRule = get_rule(token_previous().typ)->prefix;
    if (prefixRule == NULL) {
            parse_err(token_current(), "Expected expression.");
        return;
    }
    prefixRule();


    while (precedence <= get_rule(token_current().typ)->precedence) {
      advance();
      ParseFn infixRule = get_rule(token_previous().typ)->infix;
      infixRule();
    }
}


void expression() {
    parse_precedence(PREC_ASSIGNMENT);
}

void number() {
    Token num = token_previous();
    char *str = malloc(num.length + 1);
    memcpy(str, num.str, num.length);
    str[num.length] = '\0';
    if (strchr(str, '.') ==  NULL) {
        int value = (int)strtol(str, NULL, 10);
        Type typ = { TYPE_FINAL, "int" };
        visitor_num_literal(&value, &typ);
    } else {
        float value = (float)strtof(str, NULL);
        Type typ = { TYPE_FINAL, "float" };
        visitor_num_literal(&value, &typ);
    }
}

void variable() {
    Token name = token_previous();  // TODO: function calls
    visitor_var_read(name);
}

void grouping() {
    expression();
    consume(TOKEN_RIGHT_PAREN, "Expected ')' after expression");
}
void unary() {
    TokenTyp typ = token_previous().typ;
    parse_precedence(PREC_UNARY); // Operand, assume the result is on the stack.
    visitor_op_unary(typ);
}
void binary() {
    TokenTyp typ = token_previous().typ;
    ParseRule *rule = get_rule(typ);
    parse_precedence((OperatorPrecedence) (rule->precedence + 1)); // Operand, assume the result is on the stack

    visitor_op_binary(typ);
}

static bool match(TokenTyp typ) {
  if (token_current().typ != typ) return false;
  advance();
  return true;
}

void compile() {
    while (!match(TOKEN_EOF)) declaration();
}

void declaration() {
    statement();
}

static Type *parse_type() {  // TODO: enclosing types (lists, lambdas, etc.)
    Token typename = token_next();
    if (typename.typ != TOKEN_IDENTIFIER) { parse_err(typename, "Expected typename"); return NULL; }
    Type ret = { .typ = TYPE_FINAL, .final = typename.str };
    Type *out = malloc(sizeof(Type));

    memcpy(out, &ret, sizeof(Type));

    return out;
}

void variable_decl() {
    // 'var' 'name' ':' 'type' ('=' <initializer>)? ';'  \
              ^
    
    Token name = token_next();
    if (name.typ != TOKEN_IDENTIFIER) parse_err(name, "Expected identifier after 'var' keyword");

    // 'var' 'name' ':' 'type' ('=' <initializer>)? ';'  \
                     ^
    if (!match(TOKEN_COLON)) parse_err(token_current(), "Expected ':' after variable name");

    // 'var' 'name' ':' 'type' ('=' <initializer>)? ';'  \
                         ^
    Type *typ = parse_type();

    // 'var' 'name' ':' 'type' ('=' <initializer>)? ';'  \
                                 ^?                  ^?

    if (match(TOKEN_EQ)) {  // We have an initializer,
        expression();       // compile it.
    } else {                // No initializer,
        int null=0;         // output a 0.
        Type typ = { TYPE_FINAL, "int" };
        visitor_num_literal(&null, &typ);
    }

    visitor_var_decl(name, typ);

    if (!match(TOKEN_SEMICOLON)) parse_err(token_current(), "Expected ';' after variable declaration");
 }

void statement() {
    if (match(TOKEN_VAR)) return variable_decl();
    expression();
}