/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:33:20 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/24 16:07:46 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ast_attach_binary(t_node *root, t_node *left, t_node *right)
{
	if (!root)
		return ;
	root->left = left;
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
	if (node->data)
		free(node->data);
	ast_delete(node->left);
	ast_delete(node->right);
	free(node);
}