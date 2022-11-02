/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:54:37 by kbrousse          #+#    #+#             */
/*   Updated: 2022/07/11 14:26:56 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_next_line(int fd)
{
	static t_listgnl	*first_elem;
	t_listgnl			*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (first_elem == NULL)
		first_elem = ft_lstnewgnl(fd);
	temp = ft_go_to_linkgnl(&first_elem, fd);
	temp->i = 0;
	temp->nb_of_read = 0;
	temp->line = NULL;
	ft_read_file_and_fill_buf(temp);
	if (temp->hmb_read < BUFFER_SIZE)
	{
		if (temp->line == NULL || temp->line[0] == '\0')
		{
			ft_erase_linkgnl(&first_elem, temp);
			return (NULL);
		}
	}
	return (temp->line);
}

void	ft_read_file_and_fill_buf(t_listgnl *temp)
{
	if (check_string(temp->buf) != 0 && temp->tdl != 0)
	{
		temp->nb_of_read++;
		ft_fill_line(temp);
	}
	while (check_string(temp->line) == 0 && temp->tdl == 0)
	{
		temp->buf = ft_callocgnl(BUFFER_SIZE + 1);
		if (temp->buf == NULL)
			return ;
		temp->nb_of_read++;
		temp->hmb_read = read(temp->fd, temp->buf, BUFFER_SIZE);
		if (temp->buf[0] == '\0')
		{
			free(temp->buf);
			temp->buf = NULL;
			return ;
		}
		ft_fill_line(temp);
	}
}

void	ft_fill_line(t_listgnl *temp)
{
	temp->line = ft_increase_string_size(temp);
	if (temp->line == NULL)
		return ;
	while (temp->buf[temp->tdl] != '\0')
	{
		if (temp->buf[temp->tdl] == '\n')
		{
			temp->line[temp->i++] = temp->buf[temp->tdl++];
			break ;
		}
		temp->line[temp->i++] = temp->buf[temp->tdl++];
	}
	if (temp->tdl == temp->hmb_read)
	{
		free(temp->buf);
		temp->buf = NULL;
		temp->tdl = 0;
	}
}

char	*ft_increase_string_size(t_listgnl *temp)
{
	char	*dup;
	int		i;

	if (temp->line == NULL)
	{
		temp->line = ft_callocgnl(BUFFER_SIZE * temp->nb_of_read + 1);
		return (temp->line);
	}
	i = -1;
	dup = ft_callocgnl(BUFFER_SIZE * temp->nb_of_read + 1);
	if (dup == NULL)
		return (NULL);
	while (temp->line[++i] != '\0')
		dup[i] = temp->line[i];
	free(temp->line);
	temp->line = NULL;
	return (dup);
}

void	ft_erase_linkgnl(t_listgnl **first_elem, t_listgnl *temp)
{
	t_listgnl	*copy;
	t_listgnl	*current;

	copy = *first_elem;
	current = NULL;
	free(temp->buf);
	free(temp->line);
	temp->buf = NULL;
	temp->line = NULL;
	while (copy != NULL && copy->fd != temp->fd)
	{
		current = copy;
		copy = copy->next;
	}
	if (current == NULL)
	{
		copy = *first_elem;
		*first_elem = copy->next;
		free(copy);
		return ;
	}
	if (copy != NULL)
		current->next = copy->next;
	free(temp);
}
