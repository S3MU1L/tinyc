** TinyC EBNF

```{ebnf}
program ::= { top_level } ;

top_level ::= declaration | function_definition | struct_declaration ;

struct_declaration ::= "struct" identifier "{" { var_declaration } "}" ";"
| "struct" identifier ";" ;

function_definition ::= type_specifier declarator "(" [ parameter_list ] ")" compound_statement ;

declaration ::= type_specifier init_declarator_list ";" ;

var_declaration ::= type_specifier init_declarator_list ";" ;

init_declarator_list ::= init_declarator { "," init_declarator } ;

init_declarator ::= declarator [ "=" initializer ] ;

initializer ::= expression | "{" initializer_list "}" ;

initializer_list ::= initializer { "," initializer } ;

parameter_list ::= parameter { "," parameter } ;

parameter ::= type_specifier declarator ;

type_specifier ::= "int" | "char" | "bool" | "unsigned" | struct_type ;

struct_type ::= "struct" identifier | "struct" "{" { var_declaration } "}" ;

declarator ::= pointer_opt direct_declarator ;

pointer_opt ::= { "*" } ;

direct_declarator ::= identifier { "[" constant_expression? "]" }
| "(" declarator ")" ;

constant_expression ::= expression ; (* used for array sizes; may be a number *)

compound_statement ::= "{" { var_declaration } { statement } "}" ;

statement ::= expression_statement
| compound_statement
| selection_statement
| iteration_statement
| jump_statement
| print_statement ;
| assert_statement ;
| ";" ;

expression_statement ::= [ expression ] ";" ;

selection_statement ::= "if" "(" expression ")" statement [ "else" statement ] ;

iteration_statement ::= "while" "(" expression ")" statement
| "for" "(" [ expression ] ";" [ expression ] ";" [ expression ] ")" statement ;

jump_statement ::= "return" [ expression ] ";" ;

print_statement ::= "print" "(" expression ")" ";" ;

assert_statement ::= "assert" "(" expression ")" ";" ;

expression ::= assignment_expression ;

assignment_expression ::= logical_or_expression
| unary_expression "=" assignment_expression ;

logical_or_expression ::= logical_and_expression { "||" logical_and_expression } ;

logical_and_expression ::= equality_expression { "&&" equality_expression } ;

equality_expression ::= relational_expression { ( "==" | "!=" ) relational_expression } ;

relational_expression ::= additive_expression { ( "<" | ">" | "<=" | ">=" ) additive_expression } ;

additive_expression ::= multiplicative_expression { ( "+" | "-" ) multiplicative_expression } ;

multiplicative_expression ::= unary_expression { ( "*" | "/" | "%" ) unary_expression } ;

unary_expression ::= ( "!" | "-" | "&" | "*" ) unary_expression
| postfix_expression ;

postfix_expression ::= primary_expression { postfix_suffix } ;

postfix_suffix ::= "[" expression "]"
| "." identifier
| "->" identifier
| "(" [ argument_expression_list ] ")" ;

argument_expression_list ::= assignment_expression { "," assignment_expression } ;

primary_expression ::= identifier
| constant
| string_literal
| "(" expression ")" ;

constant ::= integer_constant | character_constant ;

identifier ::= /* token: identifier */ ;
integer_constant ::= /* token: decimal | hex | octal */ ;
character_constant ::= /* token: 'a', '\n', etc. */ ;
string_literal ::= /* token: "..." */ ;
```