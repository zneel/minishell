/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/24 16:36:46 by mhoyer           ###   ########.fr       */
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
    t_lexer     *lexed;
    char        *line;

	
    (void)argc;
    (void)argv;
	minishell.env = env_cpy(env);
    minishell.pids = NULL;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			return (1);
		if (line && *line && *line != ' ' && *line != '\t')
			add_history(line);
		lexed = lexer(line);
		debug_lexer(lexed);
		delete_lexer(lexed);
	}
	free_minishell(&minishell);
	return (0);
}
