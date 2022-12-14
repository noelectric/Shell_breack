/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:02:19 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/22 01:13:38 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	lenint(long n)
{
	int	len;

	len = 0;
	if (n < 0 || n == 0)
	{
		len = 1;
		n = -n;
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;

	size = lenint(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (printf("allocation failed"), exit(0), NULL);
	str[size] = '\0';
	while (size-- > 0)
	{
		if (n < 0)
		{
			str[0] = '-';
			n = -n;
		}
		str[size] = n % 10 + 48;
		n = n / 10;
		if (n == 0)
			break ;
	}
	return (str);
}
