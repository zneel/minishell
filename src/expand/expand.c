/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:04:12 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/29 22:24:19 by ebouvier         ###   ########.fr       */
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

void	expand_args(t_list *lst, t_minishell *minishell)
{
	char			*tmp;
	t_expand_str	exp_struct;
	t_list			*prev;

	if (!lst)
		return ;
	prev = NULL;
	while (lst)
	{
		init_expand(&exp_struct, lst->content);
		tmp = lst->content;
		lst->content = expand(minishell, &exp_struct);
		if (((char *)(lst->content))[0] == '\0')
		{
			if (prev)
				prev->next = lst->next;
			else
				lst = lst->next;
		}
		prev = lst;
		free(tmp);
		lst = lst->next;
	}
}

void	expand_redirs(t_list *lst, t_minishell *minishell)
{
	char			*tmp;
	t_expand_str	exp_struct;
	t_list			*prev;

	if (!lst && !lst->content)
		return ;
	prev = NULL;
	while (lst)
	{
		prev = lst;
		init_expand(&exp_struct, ((t_redirect *)lst->content)->file);
		tmp = ((t_redirect *)lst->content)->file;
		((t_redirect *)lst->content)->file = expand(minishell, &exp_struct);
		if (((((t_redirect *)lst->content)->file))[0] == '\0')
		{
			if (prev)
				prev->next = lst->next;
			else
				lst = lst->next;
		}
		free(tmp);
		lst = lst->next;
	}
}
