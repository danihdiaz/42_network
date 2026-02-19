/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 19:32:55 by dhontani          #+#    #+#             */
/*   Updated: 2026/02/19 20:09:40 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

void	test_file(const char *filename)
{
	char	*line;
	int		fd;

	printf("=== Test: %s ===\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("No se pudo abrir el archivo\n");
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	printf("=== Fin ===\n\n");
}

int	main(void)
{
	char	*line;
	int		fd1;
	int		fd2;

	// Archivo normal
	test_file("tests.txt");

	// Archivo vacío
	test_file("empty.txt");

	// Archivo sin \n al final
	test_file("nonewline.txt");

	// fd inválido
	printf("=== Test fd invalido ===\n");
	line = get_next_line(-1);
	printf("fd -1 devuelve: %s\n\n", line ? line : "NULL (correcto)");
	free(line);

	// Múltiples fds a la vez (bonus)
	printf("=== Test multiples fds ===\n");
	fd1 = open("tests.txt", O_RDONLY);
	fd2 = open("nonewline.txt", O_RDONLY);
	line = get_next_line(fd1);
	printf("fd1: %s", line); free(line);
	line = get_next_line(fd2);
	printf("fd2: %s", line); free(line);
	line = get_next_line(fd1);
	printf("fd1: %s", line); free(line);
	line = get_next_line(fd2);
	printf("fd2: %s", line); free(line);
	close(fd1);
	close(fd2);

	return (0);
}