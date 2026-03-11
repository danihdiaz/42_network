/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:34:03 by dhontani          #+#    #+#             */
/*   Updated: 2026/03/11 13:41:57 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	adaptive_alg(t_stack **a, t_stack **b, float disorder)
{
	if (disorder < 0.2)
		simple_alg(a, b);
	else if (disorder < 0.5)
		med_alg(a, b);
	else
		complex_alg(a, b);
}
