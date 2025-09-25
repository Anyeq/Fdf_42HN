/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:40:08 by asando            #+#    #+#             */
/*   Updated: 2025/09/25 15:53:07 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	deep_free(void *content)
{
	char	**str_arr;
	char	**curr;

	str_arr = (char **)content;
	curr = str_arr;
	while(*curr)
	{
		free(*curr);
		curr++;
	}
	free(str_arr);
}

static int	store_line(t_list **raw_data, char **str_arr)
{
	t_list	*new_node;
	new_node = ft_lstnew(str_arr);
	if (new_node == NULL)
	{
		ft_lstclear(raw_data, deep_free);
		return (-1);
	}
	ft_lstadd_back(raw_data, new_node);
	return (0);
}

static int	**grab_element(t_list **raw_data)
{
	int		**map;
	t_list	*current;
	int		n_column;
	int		n_row;

	map = malloc((ft_lstsize(*raw_data) + 1) * sizeof(int *));
	if (map == NULL)
	{
		ft_lstclear(raw_data, deep_free);
		perror("Error");
		exit(EXIT_FAILURE);
	}
	current = *raw_data;
	while (current)
	{
		(char **)current->content
		current++;
	}
	return (0);
}

int	parse_file(int file_fd, int ***map_data)
{
	char	*buff;
	char	**line_element;
	t_list	*raw_data_stack;

	buff = get_next_line(file_fd);
	line_element = NULL;
	raw_data_stack = NULL;
	while (buff)
	{
		line_element = ft_split(buff, ' ');
		free(buff);
		buff == NULL;
		if (store_line(&raw_data_stack, line_element) == -1)
			break ;
		buff = get_next_line(file_fd);
	}
	close(file_fd);
	if (buff == NULL && raw_data_Stack == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	*map_data = grab_element(&raw_data_stack);
	return (0);
}
