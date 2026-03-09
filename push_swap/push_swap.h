/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugarcia <lugarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:50:23 by lugarcia          #+#    #+#             */
/*   Updated: 2026/03/02 17:09:00 by lugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <stdio.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

t_stack	*ft_parse_input(int argc, char **argv);
float	compute_disorders(t_stack *stack_a);
int		ft_is_valid_number(char *str);
int		ft_check_args(int offset, char **argv);
long	ft_atol(char *str);
void	sa(t_stack *stack);
void	sb(t_stack *stack);
void	ss(t_stack *a, t_stack *b);
void	ra(t_stack **stack_a);
void	rb(t_stack **stack_b);
void	rr(t_stack **stack_a, t_stack **stack_b);
void	pa(t_stack **stack_a, t_stack **stack_b);
void	pb(t_stack **stack_a, t_stack **stack_b);
void	print_stacks(t_stack *a, t_stack *b);
t_stack	*ft_stack_init(int offset, char **argv);
size_t	ft_find_flags(int argc, char **argv);
void	free_splt(char **splt);
void	ft_lstad_back(t_stack **lst, t_stack *new);
t_stack	*ft_new_node(int num);
void	set_index(t_stack *stack_a);
int		ft_sqrt_int(int n);
int		ft_ceil_div(int n, int i);
int		ft_listsize(t_stack *lst);
int		get_chunk(int chunk_size, int index);
int		ft_find_pos(t_stack **stack, int index);
void	ft_rot_stack(t_stack **stack, int lst_sz, int pos, char ab);
void	rot_down(t_stack **stack, char ab);
void	rot_up(t_stack **stack, char ab);

#endif