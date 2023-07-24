# MINISHELL

- [ ] lexer  
- [ ] parser
- [ ] exec
## LEXER / PARSER

We first define a BNF grammar then we implement the lexer and finally the parser.
#### BNF (Backnus-Naur Form) grammar:
```abnf
command_line    ::= expr command_rest
command_rest    ::= AND expr command_rest
                |   OR expr command_rest
                |   EPSILON
expr            ::= group
                |   pipeline
group           ::= LPAREN command_line RPAREN
pipeline        ::= command pipeline_rest
pipeline_rest   ::= PIPE command pipeline_rest
                |   EPSILON
command         ::= cmd_word
                |   cmd_word io_redirect
                |   io_redirect cmd_word
                |   cmd_word io_redirect cmd_word
io_redirect     ::= LESS WORD
                |   GREAT WORD
                |   DGREAT WORD
                |   DLESS WORD
cmd_word        ::= WORD
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
