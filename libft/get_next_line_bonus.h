/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:35:48 by kbrousse          #+#    #+#             */
/*   Updated: 2022/07/20 20:17:10 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_listgnl
{
	int					fd;
	char				*buf;
	char				*line;
	int					tdl;
	int					i;
	int					hmb_read;
	int					nb_of_read;
	struct s_listgnl	*next;
}	t_listgnl;

char		*get_next_line(int fd);
void		ft_read_file_and_fill_buf(t_listgnl *temp);
void		ft_fill_line(t_listgnl *temp);
char		*ft_increase_string_size(t_listgnl *temp);
char		*ft_erase_link(t_listgnl **first_elem, t_listgnl *temp);

t_listgnl	*ft_lstnewgnl(int entry_fd);
t_listgnl	*ft_go_to_link(t_listgnl **first_elem, int fd);
void		ft_lst_addbackgnl(t_listgnl **first_elem, t_listgnl *new);
int			check_string(char *str);
void		*ft_callocgnl(int size);

#endif
