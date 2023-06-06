/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 00:42:28 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/07 00:46:52 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

char	*state_to_str(enum e_state state)
{
	if (state == STATE_DEFAULT)
		return ("STATE_DEFAULT");
	else if (state == STATE_IN_QUOTE)
		return ("STATE_IN_QUOTE");
	else if (state == STATE_IN_DQUOTE)
		return ("STATE_IN_DQUOTE");
	else if (state == STATE_IN_ASTERISK)
		return ("STATE_IN_ASTERISK");
	else
		return ("STATE_UNKNOWN");
}

void	debug_lexer(t_lexer *lexer)
{
	ft_printf("lexer->state=%s\n", state_to_str(lexer->state));
}
