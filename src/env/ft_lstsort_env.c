/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 08:17:44 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/17 08:49:35 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echangerValeurs(t_kv* a, t_kv* b) {
    char* temp_key = a->key;
    char* temp_value = a->value;
    a->key = b->key;
    a->value = b->value;
    b->key = temp_key;
    b->value = temp_value;
}

void	ft_lstsort_env(t_kv	*top)
{
    t_kv* current;
    t_kv* parc;
    for (current = top; current != NULL; current = current->next) {
        for (parc = current->next; parc != NULL; parc = parc->next) {
            if (ft_strncmp(current->key, parc->key, ft_strlen(current->key)) > 0) {
                echangerValeurs(current, parc);
            }
        }
    }
}
