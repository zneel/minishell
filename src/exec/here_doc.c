/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:51:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/19 15:52:33 by mhoyer           ###   ########.fr       */
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

int	check_limiter(char *line, char *limiter)
{
	if (!line)
    	return (1);
    if (str_cmpend(line, limiter) == 0)
    {
    	free(line);
        return (1);
    }
	return (0);
}

void	here_doc(char *limiter)
{
	int		fd;
	char	*line;

	fd = open(FILE_HEREDOC, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return ;
	line = NULL;
	while (1)
	{
		signal(SIGINT, sig_handler_here_doc);
		if (g_sigint == 1)
		{
			close(fd);
			unlink(FILE_HEREDOC);
			return ;
		}
		line = readline("> ");
		if (check_limiter(line, limiter))
			break;
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}
