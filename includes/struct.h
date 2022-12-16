#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_enum_token
{
	TOK_NULL,
	TOK_STRING,
	TOK_OP_PAR,
	TOK_CL_PAR,
	TOK_INFILE,
	TOK_TRUNC,
	TOK_HEREDOC,
	TOK_APPEND,
	TOK_PIPE,
	TOK_AND_OPER,
	TOK_OR_OPER,
	TOK_SHELL,
	TOK_SUBSHELL,
}	t_enum_token;

typedef struct s_redir_ms
{
	struct s_redir_ms	*next;
	char				*file_name;
	t_enum_token		mode;
}	t_redir_ms;

typedef struct s_node_ms
{
	struct s_node_ms	*left;
	struct s_node_ms	*right;
	char				**content;
	struct s_redir_ms	*first_redir;
	char				*infile;
	char				*outfile;
	t_enum_token		infile_mode;
	t_enum_token		outfile_mode;
	t_enum_token		shell;
	t_enum_token		operator;
}	t_node_ms;

typedef struct s_token_ms
{
	t_enum_token		type;
	char				*content;
	struct s_token_ms	*next;
}	t_token_ms;

typedef struct s_env_ms
{
	struct s_env_ms	*next;
	char			*key;
	char			*value;
}	t_env_ms;

# endif
