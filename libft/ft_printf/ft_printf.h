/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:22:01 by thtay             #+#    #+#             */
/*   Updated: 2025/12/19 21:22:02 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/////////////////////////////////////////////|   //////////////|
//                                          ||   //           ||
//   malloc, free, write                    ||   //  libft.h  ||
//                                          ||   //           ||
//   va_start, va_arg, va_copy, va_end      ||   //|||||||||||||
//                                          ||
//||||||||||||||||||||||||||||||||||||||||||||

////////////////////////////////////////////////////||
//  c char       d decimal     x small hex          ||
//  s string     i integer     X UPPER HEX          ||
//  p pointer    u unsigned    % Control / escape   ||
////////////////////////////////////////////////////||

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include "../libft.h"

int		ft_printf(const char *str, ...);
int		pf_handle(char flag, va_list args);
int		handle_char(char c);
int		handle_str(char *str);
int		handle_int(int num);
int		handle_float(double num);

int		pf_handle2(char flag, va_list args);
int		handle_uint(unsigned int num);
int		handle_hex(unsigned int hexa, int mode);
int		handle_point(unsigned long ptr);
int		handle_err_einval(char flag);

#endif
