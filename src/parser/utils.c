/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:00:29 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/18 14:39:42 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <stdio.h>

t_node_type	lexer_to_node(t_type type)
{
	if (type == T_LESS)
		return (LESS);
	else if (type == T_GREAT)
		return (GREAT);
	else if (type == T_DGREAT)
		return (DGREAT);
	else if (type == T_DLESS)
		return (HERE_DOC);
	else if (type == T_PIPE)
		return (PIPE);
	else if (type == T_AND)
		return (AND);
	else if (type == T_OR)
		return (OR);
	else if (type == T_WORD)
		return (COMMAND);
	return (UNKNOWN);
}

/**
 * !DELETE
 */
char	*node_type_to_str(t_node_type type)
{
	if (type == COMMAND)
		return ("COMMAND");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == AND)
		return ("AND");
	else if (type == OR)
		return ("OR");
	else if (type == LESS)
		return ("LESS");
	else if (type == GREAT)
		return ("GREAT");
	else if (type == DGREAT)
		return ("DGREAT");
	else if (type == HERE_DOC)
		return ("HERE_DOC");
	else
		return ("UNKNOWN");
}

/**
 * !DELETE
 */
void	pretty_print_ast(t_node *node, char *prefix)
{
	int		len;
	char	*new_prefix;

	if (node == NULL)
		return ;
	printf("%s├── Type: %s\n", prefix, node_type_to_str(node->type));
	if (node->data != NULL)
	{
		printf("%s|   ├── Data: ", prefix);
		while (node->data != NULL)
		{
			printf("%s", *node->data);
			if (*(node->data + 1) != NULL)
				printf(" ");
			node->data++;
		}
		printf("\n");
	}
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
