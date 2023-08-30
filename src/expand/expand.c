/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:04:12 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/30 13:03:28 by ebouvier         ###   ########.fr       */
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
	if (expand->result_size == 0)
	{
		free(expand->result);
		return (NULL);
	}
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

void	expand_args(t_list **lst, t_minishell *minishell)
{
	char			*tmp;
	t_expand_str	exp_struct;
	t_list			*current;

	current = *lst;
	if (!current || !current->content)
		return ;
	while (current)
	{
		init_expand(&exp_struct, current->content);
		tmp = current->content;
		current->content = expand(minishell, &exp_struct);
		free(tmp);
		if (!current->content)
			current = delete_expand_node(lst, current, false);
		else
			current = current->next;
	}
}

void	expand_redirs(t_list **lst, t_minishell *minishell)
{
	char			*tmp;
	t_expand_str	exp_struct;
	t_list			*current;

	current = *lst;
	if (!current || !current->content)
		return ;
	while (current)
	{
		init_expand(&exp_struct, ((t_redirect *)current->content)->file);
		tmp = ((t_redirect *)current->content)->file;
		((t_redirect *)current->content)->file = expand(minishell, &exp_struct);
		free(tmp);
		if (!current->content)
			current = delete_expand_node(lst, current, true);
		else
			current = current->next;
	}
}
