/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:04:56 by emkalkan          #+#    #+#             */
/*   Updated: 2024/10/06 19:07:57 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int		ft_printf(const char *format, ...);

int		print_format(char sign, va_list args);

int		print_char(int c);

int		print_str(char *str);

int		print_digit(long nbr, int base, int yesoryes);

int		print_unsigned(unsigned int num);

int		print_ptr(unsigned long long nbr);

int		print_pointer(va_list ap);

#endif
