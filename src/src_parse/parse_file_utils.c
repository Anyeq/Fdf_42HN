/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:30:39 by asando            #+#    #+#             */
/*   Updated: 2025/10/02 18:44:17 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static uint32_t	ft_atohex(char *str)
{
	uint32_t	result;
	uint8_t		digit;
	char		c;
	int			i;

	result = 0;
	digit = 0;
	i = 0;
	c = '\0';
	if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
		str += 2;
	while (*str && i++ < 8)
	{
		c = *(str++);
		if (ft_isdigit(c))
			digit = c - '0';
		else if (c >= 'a' && c <= 'f')
			digit = 10 + (c - 'a');
		else if (c >= 'A' && c <= 'F')
			digit = 10 + (c - 'A');
		else
			return (0);
		result = (result << 4) | digit;
	}
	return (result);
}

static uint32_t	color_normalizer(char *str, uint32_t user_color)
{
	uint32_t	result;
	int			i;
	int			n;

	i = 0;
	n = 0;
	result = user_color;
	if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
		str += 2;
	while (*(str++))
		i++;
	while (i == 2 && n++ < 2)
		result = (result << 8) | 0xFF;
	if (i == 4)
		result = (result << 8) | 0;
	if (i != 8)
		result = (result << 8) | 0xFF;
	return (result);
}

void	grab_color_data(char *str, t_point_data *point)
{
	char		*temp;
	uint32_t	user_color;

	user_color = 0;
	temp = ft_strchr(str, ',');
	if (temp)
	{
		user_color = ft_atohex(temp + 1);
		if (user_color != 0)
		{
			point->has_color = true;
			point->color_data = color_normalizer(temp + 1, user_color);
		}
		else
			point->has_color = false;
	}
	else
		point->has_color = false;
	return ;
}
