/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 04:52:10 by bdomitil          #+#    #+#             */
/*   Updated: 2021/10/23 19:57:20 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int ft)
{
	char	q;

	q = 0;
	if (n == -2147483648)
	{
		write(ft, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write(ft, "-", 1);
	}
	if (n > 0)
	{
		q = n % 10 + 48;
		if (n / 10 > 0)
			ft_putnbr_fd(n / 10, ft);
		write(ft, &q, 1);
	}
	if (n == 0)
		write(ft, "0", 1);
}
