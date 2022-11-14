/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:01:53 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/24 10:48:33 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

typedef struct s_pipex_cmd
{
	char				*correct_path;
	char				**tab_cmd;
	struct s_pipex_cmd	*next;
}	t_pipex_cmd;

typedef struct s_pipex
{
	pid_t				*tab_pid;
	int					pipefd[2];
	int					infile;
	int					outfile;
	int					argc;
	char				**tab_env_paths;
	struct s_pipex_cmd	*first_cmd;
}	t_pipex;

void		clear_program(t_pipex *pipex, char *perror_str);

//init
void		init_pipex(t_pipex *pipex, int argc);

//check
void		check_args(t_pipex *pipex, int argc, char **argv, char **env);
void		verify_files_access(t_pipex *pipex, int argc, char **argv);
void		verify_cmd_access(t_pipex *pipex, int ac, char **av, char **env);

//LL
void		ft_lstaddback_pipex(t_pipex *pipex, t_pipex_cmd *new);
t_pipex_cmd	*ft_lstnew_pipex(t_pipex *pipex);

//exec
void		two_commands_requested(t_pipex *pipex, char **argv, char **env);

#endif
