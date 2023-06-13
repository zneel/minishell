# MINISHELL

[ ] lexer  
[ ] parser  
[ ] execution  
## LEXER / PARSER
We first define a BNF grammar then we implement the lexer and finally the parser.
#### BNF (Backnus-Naur Form) grammar:
```
commandline     ::= list
                |   list ";"
list            ::= conditional
                |   list ";" conditional
conditional     ::= pipeline
                |   conditional "&&" pipeline
                |   conditional "||" pipeline
pipeline        ::= command
                |   pipeline "|" command
command         ::= word
                |   redirection
                |   builtin
                |   command word
                |   command redirection
redirection     ::= redirectionop filename
                |   "<<" word newline text word newline
redirectionop   ::=  "<" | ">" | "2>" | ">>"
builtin         ::= echo
                |   cd
                |   pwd
                |   export
                |   unset
                |   env
                |   exit
echo            ::= "echo" ["-n"] string
cd              ::= "cd" string
pwd             ::= "pwd"
export          ::= "export" string
unset           ::= "unset" string
env             ::= "env"
exit            ::= "exit"
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
for exemple the command: `ls -l | grep x` we tokenise `ls -l` as a `WORD` the keyword `|` as a `PIPE` and `x` as `WORD`
### PARSER
The goal there is to make an ast from the tokens:
If we take the exemple we have:
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
