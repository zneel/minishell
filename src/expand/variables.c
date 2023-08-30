/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:02:49 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/30 12:59:03 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static t_bool	valid_expand_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*get_end_variable(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] && !valid_expand_char(input[i]))
			break ;
		i++;
	}
	return (input + i);
}

static t_expand_var	*get_variable(t_minishell *minishell, char *input)
{
	t_expand_var	*var;

	var = malloc(sizeof(t_expand_var));
	if (!var)
		return (NULL);
	var->end = get_end_variable(input);
	var->name = ft_substr(input, 0, var->end - input);
	var->value = get_env(minishell, var->name);
	return (var);
}

static void	expand_last_status(t_expand_str *expand, t_minishell *minishell)
{
	char	*last_status;

	last_status = ft_itoa(minishell->last_status);
	expand->result_size += ft_strlen(last_status);
	expand->result = ft_realloc(expand->result, expand->result_size);
	ft_strlcpy(expand->result + expand->i, last_status, ft_strlen(last_status)
		+ 1);
	expand->i += ft_strlen(last_status);
	expand->input++;
	free(last_status);
}

void	handle_dollar(t_expand_str *expand, t_minishell *minishell)
{
	t_expand_var	*var;

	var = get_variable(minishell, ++expand->input);
	if (var->value)
	{
		expand->result_size += ft_strlen(var->value);
		expand->result = ft_realloc(expand->result, expand->result_size);
		ft_strlcpy(expand->result + expand->i, var->value, ft_strlen(var->value)
			+ 1);
		expand->i += ft_strlen(var->value);
		expand->input += ft_strlen(var->name);
	}
	else
	{
		if (*expand->input == '?')
			expand_last_status(expand, minishell);
		else if (ft_strlen(var->name) == 0)
		{
			expand->result = ft_realloc(expand->result, ++expand->result_size);
			expand->result[expand->i++] = '$';
		}
		else
			expand->input = var->end;
	}
	free_expand_var(var);
}
