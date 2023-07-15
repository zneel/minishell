/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:37:55 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/14 12:24:59 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_line(t_ast *line)
{
	if (line == NULL)
		return ;
	if (line->token->type == T_PIPE) {
		
	}
	else if (line->token->type == T_WORD) {
		
	}
	
}

void	exec_tree(t_ast *top_tree)
{
	exec_line(top_tree);
}

int	main()
{
	  t_ast ast = {
        .token = new_token(T_OR, ft_strdup("||")),
        .left = &(t_ast){
            .token = new_token(T_AND, ft_strdup("&&")),
            .left = &(t_ast){
                .token = new_token(T_PIPE, ft_strdup("|")),
                .left = &(t_ast){
                    .token = new_token(T_PIPE, ft_strdup("|")),
                    .left = &(t_ast){
                        .token = new_token(T_WORD, ft_strdup("echo -n hello")),
                        .left = NULL,
                        .right = NULL,
                    },
                    .right = &(t_ast){
                        .token = new_token(T_WORD, ft_strdup("cat -e")),
                        .left = NULL,
                        .right = NULL,
                    }},
                .right = &(t_ast){.token = new_token(T_WORD, ft_strdup("grep x")), .left = NULL, .right = NULL},
            },
            .right = &(t_ast){
                .token = new_token(T_WORD, ft_strdup("tail -n5")),
                .left = NULL,
                .right = NULL,
            },
        },
        .right = &(t_ast){
            .token = new_token(T_WORD, ft_strdup("echo fail"), 9),
            .left = NULL,
            .right = NULL,
        }};
	exec_tree(&ast);
	return (0);
}