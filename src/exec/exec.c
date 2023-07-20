/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:37:55 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/20 11:47:23 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <stdio.h>

int	nb_node(t_node *node)
{
	int	nb;

	nb = 0;
	if (!node)
		return (1);
	return (nb + nb_node(node->left) + nb_node(node->right));
}
t_command	*node_to_command(t_node *node, char **env)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL); // free all exit
	command->command = get_cmd(node->raw_command, env);
	command->fd_in = -1;
	command->fd_out = -1;
	return (command);
}

void	execute_first(t_command *cmd, char **env,int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	(void)cmd;
	if (pid == 0)
	{
		dup2(0, STDIN_FILENO);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (execve(cmd->command[0], cmd->command, env) == -1)
			printf("exitlast");
	}
	else
	{
		close(pipefd[1]);
	}
}

void	execute_middle(t_command *cmd, char **env, int pipefd[2])
{
	pid_t	pid;

	(void)cmd;
	(void)pipefd;
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		if (execve(cmd->command[0], cmd->command, env) == -1)
			printf("exitmiddle");
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	execute_last(t_command *cmd, char **env, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		if (execve(cmd->command[0], cmd->command, env) == -1)
			printf("exitlast");
	}
	else
	{
		close(pipefd[0]);
	}
}

void	execute_pipeline(t_node *node, char **env)
{
	t_command	*command;
	int pipefd[2];

	if (node->left->type == PIPE)
		execute_pipeline(node->left, env);
    pipe(pipefd);
	if (node->left->type != PIPE)
	{
		printf("first : (%s)\n", node->left->raw_command);
		command = node_to_command(node->left, env);
		execute_first(command, env, pipefd);
	}
	if ((node->parent && node->parent->type != PIPE) || (!node->parent
			&& node->right->type == COMMAND))
	{
		printf("last : (%s)\n", node->right->raw_command);
		command = node_to_command(node->right, env);
		execute_last(command, env, pipefd);
	}
	else
	{
	    printf("middle : (%s)\n", node->right->raw_command);
	    command = node_to_command(node->right, env);
	    execute_middle(command, env, pipefd);
	}
}

void    wait_all(int nb_cmd)
{
    int i;
    
    i = 0;
    while (i < nb_cmd)
    {
        wait(NULL);
        i++;
    }
}

void	exec(t_node *node, t_minishell *minishell)
{
	// t_command	*command;

	if (!node)
		return ;
	if (node->type == PIPE)
		execute_pipeline(node, convert_env(minishell->env));
	// else if (node->type == COMMAND)
	// {
	// 	command = node_to_command(node, convert_env(minishell->env));
	// 	execute_command(command, convert_env(minishell->env));
	// }
	// if (node->token->type == T_PIPE)
	// {
	//     printf("(((T_PIPE : %s)))\n", node->token->value);
	//     pipe(fd_pipe);
	//     pid = fork();
	//     if (pid == -1)
	//         exit(1);
	//     if (pid == 0)
	//     {
	//         dup2(fd_pipe[1], 1);
	//         close(fd_pipe[0]);
	//         close(fd_pipe[1]);
	//         exec(node->left);
	//     }
	//     pid = fork();
	//     if (pid == -1)
	//         exit(1);
	//     if (pid == 0)
	//     {
	//         dup2(fd_pipe[0], 0);
	//         close(fd_pipe[0]);
	//         close(fd_pipe[1]);
	//         exec(node->right);
	//     }
	//     close(fd_pipe[0]);
	//     close(fd_pipe[1]);
	// }
	// else if (node->token->type == T_OR)
	// {
	//     printf("(((T_OR : %s)))\n", node->token->value);
	//     exec(node->left);
	// }
	// else if (node->token->type == T_AND)
	// {
	//     printf("(((T_AND : %s)))\n", node->token->value);
	//     exec(node->left);
	//     exec(node->right);
	// }
	// else if (node->token->type == T_WORD)
	// {
	//     printf("(((T_WORD : %s)))\n", node->token->value);
	//     pid = fork();
	//     if (pid == -1)
	//         exit(1);
	//     if (pid == 0)
	//     {
	//         char **splited;
	//         splited = ft_split(node->token->value, " ");
	//         if (execve(ft_strjoin("/usr/bin/", splited[0]), splited, NULL) ==
	// -1)
	//         {
	//             exit (1);
	//         }
	//     }
	// }
}

void	prep_exec(t_node *node, t_minishell *minishell)
{
	minishell->stdin = dup(0);
	minishell->stdout = dup(1);
	exec(node, minishell);
	wait_all(3);
}