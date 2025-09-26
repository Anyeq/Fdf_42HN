/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:30:39 by asando            #+#    #+#             */
/*   Updated: 2025/09/26 12:17:40 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	ft_atohex(char *str)
{
	uint32_t	result;
	uint8_t		digit;
	char		c;
	int			i;

	i = 0;
	result = 0;
	digit = 0;
	c = '\0';
	if (*str == '0' && (*str + 1 == 'x' || *str + 1 == 'X'))
		i = 2;
	while (str[i])
	{
		c = str[i];
		if (ft_isdigit(c))
			digit = c - '0';
		else if (c >= 'a' && c <= 'f')
			digit = 10 + (c - 'a');
		else if (c >= 'A' && c <= 'F')
			digit = 10 + (c - 'A');
		else
			return (0);
		result = (result << 4) | digit;
		i++;
	}
	return (result);
}
