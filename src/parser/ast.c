/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:33:20 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/28 15:58:29 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		free(node->data);
		node->data = NULL;
	}
	free(node);
	node = NULL;
}
