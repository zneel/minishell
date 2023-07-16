/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:33:20 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/13 09:03:38 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ast_attach_binary(t_node *root, t_node *left, t_node *right)
{
	if (!root)
		return ;
	root->left = left;
	root->right = right;
}

void	ast_delete(t_node *node)
{
	if (!node)
		return ;
	free(node->raw_command);
	ast_delete(node->left);
	ast_delete(node->right);
	free(node);
}
