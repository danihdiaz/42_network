/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:57:03 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/17 19:48:32 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# define MAX_FD 1024
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		has_newline(char *stash);
char	*extract_line(char *stash);
char	*update_stash(char *stash);
char	*stash_join(char *stash, char *buffer);
size_t	ft_strlen(const char *str);

#endif