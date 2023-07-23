/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:51:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/23 20:10:14 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	here_doc(char *limiter)
{
	int	fd;
	char	*line;
	
	fd = open(file_heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return ;
	line = readline("here_doc> ");
	while (ft_strncmp(line, limiter, ft_strlen(limiter) - 1) != 0)
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("here_doc> ");
	}
	close(fd);
}