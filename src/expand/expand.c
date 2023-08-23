#include "expand.h"
#include "minishell.h"

char	*ft_realloc(char *ptr, size_t size)
{
	char	*new_ptr;

	new_ptr = ft_calloc(size + 1, sizeof(char));
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_strlcpy(new_ptr, ptr, size + 1);
		free(ptr);
	}
	return (new_ptr);
}

void	free_expand_var(t_expand_var *var)
{
	free(var->name);
	free(var);
}

char	*get_end_variable(char *input)
{
}

t_expand_var	*get_variable(t_minishell *minishell, char *input)
{
	t_expand_var	*var;

	var = malloc(sizeof(t_expand_var));
	if (!var)
		return (NULL);
	var->end = ft_strchr(input, '$');
	if (!var->end)
		var->end = ft_strchr(input, ' ');
	if (!var->end)
		var->end = ft_strchr(input, '\'');
	if (!var->end)
		var->end = ft_strchr(input, '\"');
	if (!var->end)
		var->end = input + ft_strlen(input);
	var->name = ft_substr(input, 0, var->end - input);
	var->value = get_env(minishell, var->name);
	return (var);
}

void	expand_last_status(t_expand_str *expand, t_minishell *minishell)
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

	expand->input++;
	var = get_variable(minishell, expand->input);
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
	}
	free_expand_var(var);
}

static void	copy_and_increment(t_expand_str *expand)
{
	*(expand->result + expand->i++) = *expand->input;
	expand->result_size++;
	expand->input++;
}

static void	change_state(unsigned int new_state, t_expand_str *expand)
{
	expand->state ^= new_state;
	expand->input++;
}

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

void	expand_tree(t_node *root, t_minishell *minishell)
{
	char			*tmp;
	int				i;
	t_expand_str	exp_struct;

	i = -1;
	if (!root)
		return ;
	expand_tree(root->left, minishell);
	if (root->type == COMMAND)
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
