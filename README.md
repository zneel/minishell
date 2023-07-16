# MINISHELL

- [ ] lexer  
- [ ] parser
- [ ] exec
## LEXER / PARSER

We first define a BNF grammar then we implement the lexer and finally the parser.
#### BNF (Backnus-Naur Form) grammar:
```abnf
command_line    ::= pipeline command_rest
                |   group command_rest
command_rest    ::= AND pipeline command_rest
                |   OR pipeline command_rest
                |   EPSILON
group           ::= LPAREN command_line RPAREN
pipeline        ::= command pipeline_rest
pipeline_rest   ::= PIPE command pipeline_rest
                |   EPSILON
command         ::= prefix cmd_word suffix
                |   prefix io_redirect suffix
cmd_word        ::= WORD
prefix          ::= WORD
                |   io_redirect
suffix          ::= WORD
                |   io_redirect
io_redirect     ::= io_file
                |   io_here
io_file         ::= LESS filename
                |   GREAT filename
                |   DGREAT filename
filename        ::= WORD
io_here         ::= DLESS here_end
here_end        ::= WORD
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
