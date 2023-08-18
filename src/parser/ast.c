/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:33:20 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/18 14:57:18 by ebouvier         ###   ########.fr       */
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
	node->data = NULL;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}

t_node	*append_node_left(t_node *head, t_node *append)
{
	t_node	*tmp;

	tmp = head;
	if (!head)
		return (append);
	while (tmp->left)
		tmp = tmp->left;
	tmp->left = append;
	return (head);
}

t_node	*append_node_right(t_node *head, t_node *append)
{
	t_node	*tmp;

	tmp = head;
	if (!head)
		return (append);
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = append;
	return (head);
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

void	ast_delete(t_node *node)
{
	if (!node)
		return ;
	ast_delete(node->left);
	ast_delete(node->right);
	if (node->data)
	{
		free_mat(node->data);
		node->data = NULL;
	}
	free(node);
	node = NULL;
}
