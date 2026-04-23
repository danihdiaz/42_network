/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:57:03 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/16 19:09:14 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
int		has_newline(char *stash);
char	*extract_line(char *stash);
char	*update_stash(char *stash, size_t *stash_len);
char	*stash_join(char *stash, char *buffer, size_t *stash_len);
size_t	ft_strlen(const char *str);

#endif