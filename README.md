# MINISHELL

- [ ] lexer  
- [ ] parser
- [ ] exec
## LEXER / PARSER

We first define a BNF grammar then we implement the lexer and finally the parser.
#### BNF (Backnus-Naur Form) grammar:
```
commandline     ::= list
                |   list ";"
list            ::= conditional
                |   list ";" conditional
conditional     ::= "(" conditional ")"
                |   pipeline
                |   conditional "&&" pipeline
                |   conditional "||" pipeline
pipeline        ::= command
                |   pipeline "|" command
command         ::= word
                |   redirection
                |   command word
                |   command redirection
redirection     ::= redirectionop filename
                |   "<<" word newline text word newline
redirectionop   ::=  "<" | ">" | ">>"
text            ::= strings newline
                |   strings
strings         ::= string
                |   strings string
word            ::= quoted_string | plain_string | variable
quoted_string   ::= "'" plain_string "'" | "\"" plain_string "\""
variable        ::= "$" plain_string
```
### LEXER
The goal there is to tokenise a string.
for exemple the command: `ls -l | grep x` we tokenise `ls -l` as a `COMMAND` the keyword `|` as a `PIPE` and `x` as `COMMAND`
### PARSER
The goal there is to make an ast from the tokens:  
If we take the exemple from the lexer we have:
```
           PIPE
            |
           / \
          /   \
         /     \
    COMMAND  COMMAND
    ls -l    grep x
```
## EXECUTION  
