/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:04:12 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/29 13:59:52 by mhoyer           ###   ########.fr       */
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

void	expand_args(t_list *lst, t_minishell *minishell)
{
	char			*tmp;
	t_expand_str	exp_struct;

	if (!lst)
		return ;
	while (lst)
	{
		if (lst->content)
		{
			init_expand(&exp_struct, lst->content);
			tmp = lst->content;
			lst->content = expand(minishell, &exp_struct);
			free(tmp);
		}
		lst = lst->next;
	}
}

void	expand_redirs(t_list *lst, t_minishell *minishell)
{
	char			*tmp;
	t_expand_str	exp_struct;
	t_redirect		*redirect;

	if (!lst && !lst->content)
		return ;
	redirect = (t_redirect *)lst->content;
	while (lst)
	{
		if (redirect)
		{
			init_expand(&exp_struct, redirect->file);
			tmp = redirect->file;
			redirect->file = expand(minishell, &exp_struct);
			free(tmp);
		}
		lst = lst->next;
		if (!lst)
			break ;
		redirect = (t_redirect *)lst->content;
	}
}
