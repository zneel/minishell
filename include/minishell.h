/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:31:13 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/06 09:19:20 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "lists.h"

typedef struct minishell
{
	t_list	*env;
}	t_minishell;

t_list	*env_cpy(char **env);

#endif