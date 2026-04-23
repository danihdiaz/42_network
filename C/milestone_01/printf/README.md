*Este proyecto ha sido creado como parte del currículo de 42 por dhontani.*

ft_printf

Descripción

ft_printf es una reimplementación de la función estándar printf en C.  
El proyecto busca recrear su comportamiento básico y manejar distintos tipos de datos, reforzando conocimientos de:

- Funciones variádicas (stdarg.h)  
- Manejo de punteros y strings  
- Conversiones numéricas (decimal, hexadecimal, unsigned)  
- Modularidad y reutilización de código mediante libft  

La función soporta los siguientes especificadores:

Especificador | Descripción  
%c | Caracter  
%s | String  
%p | Puntero  
%d / %i | Enteros con signo  
%u | Enteros sin signo  
%x / %X | Hexadecimal (min/may)  
%% | Porcentaje literal  

Instrucciones

Compilación

gcc -Wall -Wextra -Werror main.c ft_printf.c libft/libft.a -Ilibft

- -Ilibft incluye las funciones auxiliares de tu libft.  
- -Wall -Wextra -Werror asegura que el código cumpla normas estrictas de compilación.

Ejecución

./a.out

Main de prueba

#include "ft_printf.h"  
#include <stdio.h>  
#include <limits.h>  

int main(void)  
{  
    printf("%d", printf());  
    ft_printf("%d", ft_printf());  
}

Qué hace:

- Llama a la función estándar printf con el parámetro que se le de y retorna el número de caracteres escritos.  
- Llama a ft_printf y hace lo mismo, para comprobar que el comportamiento es idéntico, salvo en el caso de parámetro inválido (por ejemplo, %t), que mi función simplemente devuelve 0.  
- Permite comparar el comportamiento de ambas funciones y comprobar el manejo de punteros nulos.  

⚠️ Nota: Para %s, ft_printf imprime (null) si recibe NULL para evitar comportamiento indefinido.

Elección de algoritmo y estructura de datos

- Modularización de cada tipo de conversión en funciones específicas (ft_printchar, ft_printstr, ft_printptr, etc.).  
- Uso de buffers locales y funciones de libft (ft_putstr_fd) para almacenar temporalmente los datos antes de imprimirlos.  
- Manejo de funciones variádicas con va_list, va_start, va_arg y va_end.  
- Esta estructura permite código limpio, reutilizable y fácil de mantener.

Ejemplos de uso

ft_printf("Hello %s!\n", "world");  
ft_printf("Pointer: %p\n", &main);  
ft_printf("Hexadecimal: %x\n", 255);  
ft_printf("Unsigned: %u\n", 3000000000U);  
ft_printf("Percentage: %%\n");

Ejemplo de salida:

Hello world!  
Pointer: 0x7ffee3b8a7a8  
Hexadecimal: ff  
Unsigned: 3000000000  
Percentage: %

Cada llamada devuelve el número de caracteres impresos.

Recursos

- Documentación C: ISO C Standard  
- Funciones variádicas: C Variadic Functions  
- Referencia printf: man printf  
- Uso de IA: Asistencia en redacción, estructura del README y explicación de algoritmos, sin generar código funcional automáticamente.
