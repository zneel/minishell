/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:33:20 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/29 12:36:20 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_node	*new_node(t_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->redir = NULL;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}

void	ast_attach_binary(t_node *root, t_node *left, t_node *right)
{
	if (!root)
		return ;
	if (left)
		root->left = left;
	if (right)
		root->right = right;
	if (left)
		left->parent = root;
	if (right)
		right->parent = root;
}

void	delete_redir(void *arg)
{
	t_redirect	*redir;

	redir = (t_redirect *)arg;
	if (!redir)
		return ;
	free(redir->file);
	free(redir);
}

void	ast_delete(t_node *node)
{
	if (!node)
		return ;
	ast_delete(node->left);
	ast_delete(node->right);
	ft_lstclear(&node->redir, delete_redir);
	ft_lstclear(&node->args, free);
	node->args = NULL;
	node->redir = NULL;
	free(node);
	node = NULL;
}
