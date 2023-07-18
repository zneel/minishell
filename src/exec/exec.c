/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:37:55 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/18 11:02:57 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int nb_node(t_ast *node)
{
    int nb;

    nb = 0;
    if (!node)
        return (1);
    return (nb +  nb_node(node->left) + nb_node(node->right));
}

void	exec(t_ast *node)
{
    pid_t   pid;
    int     fd_pipe[2];

    if (!node)
        return ;
    if (node->token->type == T_PIPE)
    {
        pipe(fd_pipe);
        pid = fork();
        if (pid == -1)
            exit(1);
        if (pid == 0)
        {
            dup2(fd_pipe[1], 1);
            close(fd_pipe[0]);
            close(fd_pipe[1]);
            exec(node->left);
        }
        pid = fork();
        if (pid == -1)
            exit(1);
        if (pid == 0)
        {
            dup2(fd_pipe[0], 0);
            close(fd_pipe[0]);
            close(fd_pipe[1]);
            exec(node->right);
        }
        close(fd_pipe[0]);
        close(fd_pipe[1]);
    }
    else if (node->token->type == T_OR)
    {
        exec(node->left);
    }
    else if (node->token->type == T_AND)
    {
        exec(node->left);
        exec(node->right);
    }
    else if (node->token->type == T_WORD)
    {
        pid = fork();
        if (pid == -1)
            exit(1);
        if (pid == 0)
        {
            char **splited;
            splited = ft_split(node->token->value, " ");
            if (execve(ft_strjoin("/usr/bin/", splited[0]), splited, NULL) == -1)
            {
                exit (1);
            }
        }
    }
}
