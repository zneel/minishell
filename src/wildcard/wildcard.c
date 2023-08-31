/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:12:00 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/31 12:33:58 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"
#include "structs.h"
#include <dirent.h>
#include <errno.h>

static struct dirent	*get_dirent(DIR *dir, struct dirent *entry)
{
	errno = 0;
	entry = readdir(dir);
	if (errno)
		return (NULL);
	return (entry);
}

static t_bool	get_current_dir(t_list **files)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return (false);
	while (dirent(dir, &entry))
		ft_lstadd_back(files, ft_lstnew(ft_strdup(entry->d_name)));
	closedir(dir);
	if (errno != 0)
		return (ft_lstclear(files, free), false);
	return (true);
}

t_list	*expand_wildcard(t_list **lst, t_minishell *minishell)
{
	t_list	*files;

	files = NULL;
	while (*lst)
	{
		if (ft_strchr((*lst)->content, '*'))
		{
			if (!get_current_dir(&files))
				return (NULL);
		}
		else
			ft_lstadd_back(&files, ft_lstnew(ft_strdup((*lst)->content)));
		lst = &(*lst)->next;
	}
}
