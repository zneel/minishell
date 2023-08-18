//
	/* ************************************************************************** */
//
	/*                                                                            */
//
	/*                                                        :::      ::::::::   */
//
	/*   expand.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+        
	+:+     */
// /*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+      
	+#+        */
// /*                                                +#+#+#+#+#+  
	+#+           */
//
	/*   Created: 2023/07/25 14:20:09 by ebouvier          #+#    #+#             */
//
	/*   Updated: 2023/08/17 15:11:13 by ebouvier         ###   ########.fr       */
//
	/*                                                                            */
//
	/* ************************************************************************** */

// #include "expand.h"
// #include <string.h>

// char	*expand_variable(char *input)
// {
// 	char		*result;
// 	size_t		result_size;
// 	char		*r;
// 	const char	*var_end;
// 	char		*var_name;
// 	const char	*var_value;
// 	size_t		new_size;
// 	size_t		r_offset;

// 	var_end = strchr(input, ' ');
// 	if (!var_end)
// 		var_end = strchr(input, '\'');
// 	if (!var_end)
// 		var_end = strchr(input, '\"');
// 	if (!var_end)
// 		var_end = input + strlen(input);
// 	var_name = malloc(var_end - input + 1);
// 	strncpy(var_name, input, var_end - input);
// 	var_name[var_end - input] = '\0';
// 	var_value = getenv(var_name);
// 	if (var_value)
// 	{
// 		new_size = r - result + strlen(var_value) + strlen(input) + 1;
// 		if (new_size > result_size)
// 		{
// 			result_size = new_size;
// 			r_offset = r - result;
// 			result = realloc(result, result_size);
// 			r = result + r_offset;
// 		}
// 		strcpy(r, var_value);
// 		r += strlen(var_value);
// 	}
// 	else
// 	{
// 		*r++ = '$';
// 		strcpy(r, var_name);
// 		r += strlen(var_name);
// 	}
// 	free(var_name);
// 	input = var_end;
// }

// char	*expand(const char *input)
// {
// 	char			*result;
// 	size_t			result_size;
// 	char			*r;
// 	unsigned int	state;

// 	result = malloc(strlen(input) * 2 + 1);
// 	result_size = strlen(input) * 2 + 1;
// 	r = result;
// 	state = NONE;
// 	while (*input != '\0')
// 	{
// 		switch (*input)
// 		{
// 		case '\'':
// 			if (state & DOUBLE_QUOTE)
// 				*r++ = *input++;
// 			else
// 			{
// 				state ^= SINGLE_QUOTE;
// 				input++;
// 			}
// 			break ;
// 		case '\"':
// 			if (state & SINGLE_QUOTE)
// 				*r++ = *input++;
// 			else
// 			{
// 				state ^= DOUBLE_QUOTE;
// 				input++;
// 			}
// 			break ;
// 		case '$':
// 			if (state & SINGLE_QUOTE)
// 				*r++ = *input++;
// 			else
// 				expand_variable(++input);
// 			break ;
// 		default:
// 			*r++ = *input++;
// 		}
// 	}
// 	*r = '\0';
// 	return (result);
// }

// char	*expand_quotes(const char *input)
// {
// 	unsigned int	state;
// 	char			*result;
// 	char			*curr;

// 	state = NONE;
// 	result = malloc(sizeof(char) * (ft_strlen(input) + 1));
// 	if (!result)
// 		return (NULL);
// 	curr = result;
// 	while (*input)
// 	{
// 		if (*input == '\'')
// 		{
// 			if (state & DOUBLE_QUOTE)
// 				*curr++ = *input;
// 			else
// 				state ^= SINGLE_QUOTE;
// 		}
// 		else if (*input == '\"')
// 		{
// 			if (state & SINGLE_QUOTE)
// 				*curr++ = *input;
// 			else
// 				state ^= DOUBLE_QUOTE;
// 		}
// 		else
// 			*curr++ = *input;
// 		input++;
// 	}
// 	*curr = '\0';
// 	return (result);
// }

// void	expand_tree(t_node *root)
// {
// 	if (!root)
// 		return ;
// 	expand_tree(root->left);
// 	if (root->type == COMMAND)
// 		root->data = expand(root->data);
// 	expand_tree(root->right);
// }
