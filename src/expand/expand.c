/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:20:09 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/25 15:04:01 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void expand_quotes(t_node *node)
{
    int i;
    int j;
    char *new;
    char first_quote;
    
    i = 0;
    if (node->type == PIPE || node->type == AND || node->type == OR || !node->data)
        return ;
    j = ft_strlen(node->data);
    new = ft_calloc(sizeof(char), j);
    if (!new)
        return ;
    first_quote = -1;
    while (node->data[i])
    {
           if (first_quote == -1 && node->data[i] == '\'' || node->data[i] == '\"')
            first_quote = node->data[i];
        i++;
    }
    free(node->data);
    node->data = new;
    ft_printf("expand>node->data:%s\n", node->data);
}


void expand_tree(t_node *root)
{
    if (!root)
        return ;
    expand_tree(root->left);
    expand_quotes(root);
    expand_tree(root->right);
}