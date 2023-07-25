/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:51:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/25 10:10:58 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

	fd = open(file_heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return ;
	line = readline("here_doc> ");
	while (line && str_cmpend(line, limiter) != 0)
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("here_doc> ");
	}
	close(fd);
}
