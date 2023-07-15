/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:05:07 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/15 10:09:58 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAUX_H
# define SIGNAUX_H

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

void	sigint();
void	sigquit();

#endif