/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:40:08 by asando            #+#    #+#             */
/*   Updated: 2025/09/25 18:00:12 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	deep_free(void *content)
{
	char	**str_arr;
	char	**curr;

	str_arr = (char **)content;
	curr = str_arr;
	while (*curr)
	{
		free(*curr);
		curr++;
	}
	free(str_arr);
}

static int	store_line(t_list **raw_data, char **str_arr, void (*del)(void *))
{
	t_list	*new_node;

	new_node = ft_lstnew(str_arr);
	if (new_node == NULL)
	{
		ft_lstclear(raw_data, del);
		return (-1);
	}
	ft_lstadd_back(raw_data, new_node);
	return (0);
}

static int	*grab_column(char **str_arr, t_map_data *file_map)
{
	int		*result;
	int		i;

	i = 0;
	file_map->column_size = 0;
	while (str_arr[file_map->column_size])
		file_map->column_size++;
	result = malloc(file_map->column_size * sizeof(int));
	if (result == NULL)
		return (NULL);
	while (i <= file_map->column_size)
		result[i] = ft_atoi(str_arr[i++]);
	return (result);
}

static int	**grab_element(t_list **raw_data, t_map_data *file_map)
{
	int		**map;
	int		i;
	t_list	*current;

	file_map->row_size = ft_lstsize(*raw_data);
	map = malloc(file_map->row_size * sizeof(int *));
	i = 0;
	if (map == NULL)
		return (NULL);
	current = *raw_data;
	while (current)
	{
		map[i++] = grab_column((char **)current->content, file_map);
		if (map[i] == NULL)
		{
			clean_map(file_map, i);
			return (NULL);
		}
		current = current->next;
	}
	ft_lstclear(raw_data, deep_free);
	return (map);
}

int	parse_file(int file_fd, t_map_data *file_map)
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
		buff = NULL;
		if (store_line(&raw_data_stack, line_element, deep_free) == -1)
			break ;
		buff = get_next_line(file_fd);
	}
	close(file_fd);
	if (buff == NULL && raw_data_stack == NULL)
		return (-1);
	file_map->z_data = grab_element(&raw_data_stack, file_map);
	if (file_map->z_data == NULL)
		exit_malloc_failed(&raw_data_stack, deep_free);
	return (0);
}
