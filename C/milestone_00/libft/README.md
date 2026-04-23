*Este proyecto ha sido creado como parte del currículo de 42 por <dhontani>.*

# Libft

## Descripción

**Libft** es un proyecto introductorio del currículo de 42 cuyo objetivo es crear una librería personal en C que reimplemente un conjunto de funciones estándar de la libc, además de añadir funciones auxiliares y una implementación de listas enlazadas.

Este proyecto permite comprender en profundidad conceptos fundamentales del lenguaje C como el manejo de memoria dinámica, el uso de punteros, la gestión de strings y la creación de estructuras de datos reutilizables. La librería resultante servirá como base para muchos proyectos posteriores del currículo.

## Instrucciones

### Compilación

Para compilar la librería, ejecuta el siguiente comando en la raíz del repositorio:

```
make
```

Esto generará el archivo `libft.a`.

### Uso

Para utilizar la librería en otro proyecto, incluye el header y enlaza la librería durante la compilación:

```
#include "libft.h"
```

Ejemplo de compilación:

```
gcc main.c -L. -lft
```

### Reglas de Makefile

```
make        # compila la librería
make clean  # elimina archivos objeto
make fclean # elimina archivos objeto y libft.a
make re     # recompila todo desde cero
```

## Descripción detallada de la librería

La librería **libft** está organizada en varias partes:

### Funciones de la libc

Reimplementaciones de funciones estándar de la libc, respetando su comportamiento original:

* Manipulación de memoria (`ft_memset`, `ft_memcpy`, `ft_memmove`, `ft_memcmp`, `ft_memchr`)
* Manipulación de strings (`ft_strlen`, `ft_strdup`, `ft_strlcpy`, `ft_strlcat`, `ft_strncmp`, `ft_strchr`, `ft_strrchr`, `ft_strnstr`)
* Conversión y comprobación de caracteres (`ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`, `ft_tolower`, `ft_toupper`)
* Conversión de tipos (`ft_atoi`)

Estas funciones permiten entender cómo se implementan internamente operaciones básicas sin depender de la libc.

### Funciones adicionales

Funciones que no forman parte de la libc estándar pero que resultan útiles en proyectos posteriores:

* `ft_substr`
* `ft_strjoin`
* `ft_strtrim`
* `ft_split`
* `ft_itoa`
* `ft_strmapi`
* `ft_striteri`
* Funciones de escritura en file descriptor (`ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`)

Estas funciones refuerzan el trabajo con memoria dinámica, iteración sobre strings y callbacks.


Libft también introduce una estructura de lista enlazada simple:

```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

Se implementan funciones para:

* Crear nuevos nodos
* Añadir nodos al inicio y al final
* Recorrer la lista
* Eliminar nodos y listas completas
* Aplicar funciones sobre los elementos

Este apartado es clave para comprender el uso de punteros dobles y la correcta liberación de memoria.

## Recursos

* Manual de C (`man 3 <función>`)
* *The C Programming Language* — Kernighan & Ritchie
* cppreference.com
* Documentación oficial del proyecto Libft (42)

### Uso de IA

La inteligencia artificial se ha utilizado exclusivamente como herramienta de apoyo para el aprendizaje, en particular para:

* Comprender conceptos teóricos (punteros, memoria dinámica, listas enlazadas)
* Aclarar errores de compilación y comportamiento inesperado
* Mejorar la comprensión del enunciado del proyecto

La IA no ha sido utilizada para generar directamente el código final entregado.

## Notas

El proyecto cumple con la Norminette de 42 y ha sido verificado para evitar fugas de memoria, utilizando herramientas como `valgrind` durante el desarrollo.
