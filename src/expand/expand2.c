#include "expand.h"

char	*ft_realloc(char *ptr, size_t size)
{
	char	*new_ptr;

	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}

void	handle_quotes(int *state, char input, char **result, int *i)
{
	if (input == '\'')
	{
		if (*state & DOUBLE_QUOTE)
		{
			*(*result + *i) = input;
			*i += 1;
		}
		else
			*state ^= SINGLE_QUOTE;
	}
	else if (input == '\"')
	{
		if (*state & SINGLE_QUOTE)
		{
			*(*result + *i) = input;
			*i += 1;
		}
		else
			*state ^= DOUBLE_QUOTE;
	}
	else
	{
		*(*result + *i) = input;
		*i += 1;
	}
}

char	*expand_quotes(char *input)
{
	int		state;
	char	*result;
	int		i;

	state = NONE;
	result = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (*input)
	{
		handle_quotes(&state, *input, &result, &i);
		input++;
	}
	result[i] = '\0';
	return (result);
}

void	expand_tree(t_node *root)
{
	char *tmp;
	if (!root)
		return ;
	expand_tree(root->left);
	if (root->type == COMMAND)
	{
		tmp = root->data;
		root->data = expand_quotes(root->data);
		free(tmp);
	}
	expand_tree(root->right);
}