/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/20 11:15:02 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "lexer.h"
#include "minishell.h"
#include "builtin.h"
#include "exec.h"

int	main(int argc, char **argv, char **env)
{
    	t_node ast = {
        .type = PIPE,
        .left = &(t_node){
            .type = PIPE,
            .left = &(t_node){
                .type = COMMAND,
                .raw_command = "yes",
                .parent = &ast,
                .left = NULL,
                .right = NULL,
            },
            .right = &(t_node){
                .type = COMMAND,
                .raw_command = "head",
                .parent= &ast,
                .left = NULL,
                .right = NULL,
            },
            .parent = &ast,
        },
        .right = &(t_node){
            .type = COMMAND,
            .raw_command = "cat -e",
            .parent = &ast,
            .left = NULL,
            .right = NULL,
        },
        .parent = NULL
    };
	// t_node ast = {
    //     .token = new_token(T_OR, ft_strdup("||")),
    //     .left = &(t_node){
    //         .token = new_token(T_AND, ft_strdup("&&")),
    //         .left = &(t_node){
    //             .token = new_token(T_PIPE, ft_strdup("|")),
    //             .left = &(t_node){
    //                 .token = new_token(T_PIPE, ft_strdup("|")),
    //                 .left = &(t_node){
    //                     .token = new_token(T_WORD, ft_strdup("echo -n hello")),
    //                     .left = NULL,
    //                     .right = NULL,
    //                 },
    //                 .right = &(t_node){
    //                     .token = new_token(T_WORD, ft_strdup("cat -e")),
    //                     .left = NULL,
    //                     .right = NULL,
    //                }},
    //             .right = &(t_node){.token = new_token(T_WORD, ft_strdup("grep x")), .left = NULL, .right = NULL},
    //         },
    //         .right = &(t_node){
    //             .token = new_token(T_WORD, ft_strdup("tail -n5")),
    //             .left = NULL,
    //             .right = NULL,
    //         },
    //     },
    //     .right = &(t_node){
    //         .token = new_token(T_WORD, ft_strdup("echo fail")),
    //         .left = NULL,
    //         .right = NULL,
    //     }};
	
	// t_lexer		*lexed;
	t_minishell	minishell;
	// char		*line;

	(void)argc;
	(void)argv;
	minishell.env = env_cpy(env);
    prep_exec(&ast, &minishell);
	// while (1)
	// {
	// 	line = readline("minishell> ");
	// 	if (!line)
	// 		return (1);
	// 	if (line && *line && *line != ' ' && *line != '\t')
	// 		add_history(line);
	// 	lexed = lexer(line);
	// 	debug_lexer(lexed);
	// 	delete_lexer(lexed);
	// }
	// ft_lstclear_env(&minishell.env, free);
	return (0);
}
