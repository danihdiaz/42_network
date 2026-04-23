/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:57:17 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/05 15:37:58 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

int	ft_printf(const char *format, ...);
int	ft_printchar(int c);
int	ft_printstr(char *c);
int	ft_printvoid(void *p);
int	ft_puthex_base(uintptr_t n, int uppercase);
int	ft_printint(int n);
int	ft_printunint(unsigned int n);
int	ft_printhex_x(unsigned int n);
int	ft_printhex_up(unsigned int n);

#endif