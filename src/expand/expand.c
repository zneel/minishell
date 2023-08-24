/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:04:12 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/24 14:42:41 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	handle_expand(t_expand_str *expand, t_minishell *minishell)
{
	if (*expand->input == '\'')
	{
		if (expand->state & EX_DOUBLE_QUOTE)
			copy_and_increment(expand);
		else
			change_state(EX_SINGLE_QUOTE, expand);
	}
	else if (*expand->input == '\"')
	{
		if (expand->state & EX_SINGLE_QUOTE)
			copy_and_increment(expand);
		else
			change_state(EX_DOUBLE_QUOTE, expand);
	}
	else if (*expand->input == '$')
	{
		if (expand->state & EX_SINGLE_QUOTE)
			copy_and_increment(expand);
		else
			handle_dollar(expand, minishell);
	}
	else
		copy_and_increment(expand);
}

char	*expand(t_minishell *minishell, t_expand_str *expand)
{
	expand->result = ft_calloc(expand->input_size + 1, sizeof(char));
	if (!expand->result)
		return (NULL);
	while (*expand->input)
		handle_expand(expand, minishell);
	return (expand->result);
}

void	init_expand(t_expand_str *expand, char *input)
{
	expand->result = NULL;
	expand->result_size = 0;
	expand->input = input;
	if (input)
		expand->input_size = ft_strlen(input);
	else
		expand->input_size = 0;
	expand->i = 0;
	expand->state = EX_NONE;
}

t_bool	should_expand(t_node_type type)
{
	return (type == COMMAND || type == GREAT || type == LESS || type == DGREAT);
}

void	expand_tree(t_node *root, t_minishell *minishell)
{
	char			*tmp;
	int				i;
	t_expand_str	exp_struct;

	i = -1;
	if (!root)
		return ;
	expand_tree(root->left, minishell);
	if (should_expand(root->type))
	{
		while (root->data[++i])
		{
			init_expand(&exp_struct, root->data[i]);
			tmp = root->data[i];
			root->data[i] = expand(minishell, &exp_struct);
			free(tmp);
		}
	}
	expand_tree(root->right, minishell);
}
