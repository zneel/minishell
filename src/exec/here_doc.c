/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:51:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/02 15:31:23 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"

int	str_cmpend(char *line, char *limiter)
{
	int	i;

	i = 0;
	while (line[i] == limiter[i] && line[i] && limiter[i])
		i++;
	if (line[i] == '\0' && limiter[i] == '\0')
		return (0);
	return (1);
}

void	here_doc(char *limiter)
{
	int		fd;
	char	*line;

	fd = open(FILE_HEREDOC, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return ;
	while (1)
	{
		signal(SIGINT, sig_handler_here_doc);
		line = readline("> ");
		if (!line || str_cmpend(line, limiter) != 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
		if (g_sigint == 1)
		{
			free(line);
			close(fd);
			unlink(FILE_HEREDOC);
			return ;
		}
	}
	close(fd);
}
