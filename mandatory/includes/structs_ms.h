/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_ms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 23:09:17 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/20 01:14:28 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_MS_H
# define STRUCTS_MS_H

/*	waitpid()	*/
# include <sys/wait.h>

extern int	g_signal;

typedef enum e_tokens
{
	TOK_NULL,
	TOK_STRING,
	TOK_INFILE,
	TOK_TRUNC,
	TOK_HEREDOC,
	TOK_APPEND,
	TOK_PIPE,
	TOK_SHELL,
	TOK_SUBSHELL,
}	t_enum_token;

typedef struct s_node_ms
{
	struct s_node_ms	*left;
	struct s_node_ms	*right;
	struct s_redir_ms	*first_redir;
	char				**content;
	char				*infile;
	char				*outfile;
	t_enum_token		infile_mode;
	t_enum_token		outfile_mode;
	t_enum_token		shell;
	t_enum_token		operator;
}	t_node_ms;

typedef struct s_token_ms
{
	struct s_token_ms	*next;
	char				*content;
	t_enum_token		type;
}	t_token_ms;

typedef struct s_redir_ms
{
	struct s_redir_ms	*next;
	char				*file_name;
	t_enum_token		mode;	
}	t_redir_ms;

typedef struct s_env_ms
{
	struct s_env_ms	*next;
	char			*key;
	char			*value;
}	t_env_ms;

typedef struct s_children_ms
{
	pid_t	*pid_arr;
	int		index;
}	t_children_ms;

typedef struct s_pipe_ms
{
	t_node_ms		*tree_root;
	t_children_ms	*children;
	int				before[2];
	int				after[2];
	int				last_cmd_executed;
}	t_pipes_ms;

#endif
