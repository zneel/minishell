/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliotbouvier <elliotbouvier@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:25:00 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/05 16:04:04 by elliotbouvi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"
typedef struct s_ast
{
    t_token            *token;
    struct s_ast    *left;
    struct s_ast    *right;
}                    t_ast;

#endif