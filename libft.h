/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:13:47 by dhontani          #+#    #+#             */
/*   Updated: 2026/01/15 12:39:53 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int ft_isalnum(int c);
int ft_isalpha(int c);
int ft_isdigit(int c);
int ft_isascii(int c);
int ft_isprint(int c);
size_t ft_strlen(const char *str);
int ft_strncmp(const char *s1, const char *s2, size_t n);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
int ft_tolower(int c);
int ft_toupper(int c);
size_t ft_strlcat(char *dst, const char *src, size_t dstsize);
void ft_bzero(void *s, size_t n);

#endif