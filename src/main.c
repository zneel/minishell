/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/23 10:09:27 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "ft_printf.h"
#include "lexer.h"
#include "minishell.h"

char    *node_type_to_str(t_node_type type)
{
    switch (type)
    {
    case COMMAND:
        return ("COMMAND");
    case PIPE:
        return ("PIPE");
    case AND:
        return ("AND");
    case OR:
        return ("OR");
    case LESS:
        return ("LESS");
    case GREAT:
        return ("GREAT");
    case DGREAT:
        return ("DGREAT");
    case L_PAREN:
        return ("L_PAREN");
    case R_PAREN:
        return ("R_PAREN");
    default:
        return ("UNKNOWN");
    }
}

void    pretty_print_ast(t_node *node, char *prefix)
{
    int        len;
    char    *new_prefix;

    if (node == NULL)
        return ;
    printf("%s├── Type: %s\n", prefix, node_type_to_str(node->type));
    if (node->raw_command != NULL)
        printf("%s|   ├── Command: %s\n", prefix, node->raw_command);
    len = strlen(prefix);
    new_prefix = malloc(len + 5);
    strcpy(new_prefix, prefix);
    strcat(new_prefix, node->right != NULL ? "|   " : "    ");
    if (node->left != NULL)
    {
        printf("%s|   └── Left:\n", prefix);
        pretty_print_ast(node->left, new_prefix);
    }
    else
        printf("%s|   └── Left: NULL\n", prefix);
    if (node->right != NULL)
    {
        printf("%s└── Right:\n", prefix);
        pretty_print_ast(node->right, new_prefix);
    }
    else
        printf("%s└── Right: NULL\n", prefix);
    free(new_prefix);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	// t_node command1 = {
	// 	.type = COMMAND,
	// 	.raw_command = "cat Makefile",
	// 	.parent = NULL,
	// 	.left = NULL,
	// 	.right = NULL,
	// };
	// t_node command2 = {
	// 	.type = COMMAND,
	// 	.raw_command = "head",
	// 	.parent = NULL,
	// 	.left = NULL,
	// 	.right = NULL,
	// };
	// t_node pipe1 = {
	// 	.type = PIPE,
	// 	.left = &command1,
	// 	.right = &command2,
	// 	.parent = NULL,
	// };
	// command1.parent = &pipe1;
	// command2.parent = &pipe1;
	// t_node command3 = {
	// 	.type = COMMAND,
	// 	.raw_command = "cat -e",
	// 	.parent = NULL,
	// 	.left = NULL,
	// 	.right = NULL,
	// };
	// t_node pipe2 = {
	// 	.type = PIPE,
	// 	.left = &pipe1,
	// 	.right = &command3,
	// 	.parent = NULL,
	// };
	// pipe1.parent = &pipe2;
	// command3.parent = &pipe2;
	// t_node command4 = {
	// 	.type = COMMAND,
	// 	.raw_command = "grep cc",
	// 	.parent = NULL,
	// 	.left = NULL,
	// 	.right = NULL,
	// };
	// t_node ast = {
	// 	.type = PIPE,
	// 	.left = &pipe2,
	// 	.right = &command4,
	// 	.parent = NULL,
	// };
	// pipe2.parent = &ast;
	// command4.parent = &ast;
	// t_node command1test = {
	// 	.type = COMMAND,
	// 	.raw_command = "cat",
	// 	.parent = NULL,
	// 	.left = NULL,
	// 	.right = NULL,
	// };
	// t_node command2test = {
	// 	.type = COMMAND,
	// 	.raw_command = "ls",
	// 	.parent = NULL,
	// 	.left = NULL,
	// 	.right = NULL,
	// };
	// t_node test = {
	// 	.type = PIPE,
	// 	.left = &command1test,
	// 	.right = &command2test,
	// 	.parent = NULL,
	// };
	// command1test.parent = &test;
	// command2test.parent = &test;
	// (void)argv;
	minishell.env = env_cpy(env);
	// if (argc == 1)
	// 	prep_exec(&test, &minishell);
	// else
	// 	prep_exec(&ast, &minishell);

	
	// while (1)
	// {
	// 	line = readline("minishell> ");
	// 	if (!line)
	// 		return (1);
	// 	if (line && *line && *line != ' ' && *line != '\t')
	// 		add_history(line);
	// 	lexed = lexer(line);
	// 	debug_lexer(lexed);
	// 	delete_lexer(lexed);
	// }

(void)argc;
(void)argv;
(void)env;

	 t_node redirin = {
        .type = DLESS,
        .raw_command = "end",
        .left = NULL,
        .right = NULL,
        .parent = NULL};
    t_node redirout = {
        .type = DGREAT,
        .raw_command = "out",
        .left = NULL,
        .right = NULL,
        .parent = NULL,
    };
    t_node command4 = {
        .type = COMMAND,
        .raw_command = "head -n 2",
        .left = NULL,
        .right = &redirout,
        .parent = NULL};
    t_node command3 = {
        .type = COMMAND,
        .raw_command = "cat -e",
        .left = NULL,
        .right = NULL,
        .parent = NULL};
    t_node command2 = {
        .type = COMMAND,
        .raw_command = "head",
        .left = NULL,
        .right = NULL,
        .parent = NULL};
    t_node command1 = {
        .type = COMMAND,
        .raw_command = "cat",
        .left = &redirin,
        .right = NULL,
        .parent = NULL};
    t_node pipe1 = {
        .type = PIPE,
        .left = &command1,
        .right = &command2,
        .parent = NULL};
    command1.parent = &pipe1;
    command2.parent = &pipe1;
    t_node pipe2 = {
        .type = PIPE,
        .left = &pipe1,
        .right = &command3,
        .parent = NULL};
    pipe1.parent = &pipe2;
    command3.parent = &pipe2;
    t_node astre = {
        .type = PIPE,
        .left = &pipe2,
        .right = &command4,
        .parent = NULL};
    pipe2.parent = &astre;
    command4.parent = &astre;
    redirin.parent = &command1;
	
	//pretty_print_ast(&astre, "");
    t_node alone = {
        .type = COMMAND,
        .raw_command = "cat",
        .left = &redirin,
        .right = &redirout,
        .parent = NULL};
	prep_exec(&alone, &minishell);
	ft_lstclear_env(&minishell.env, free);
	return (0);
}
