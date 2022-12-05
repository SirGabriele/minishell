#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_tokens
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
}	t_tokens;

typedef struct s_redir_ms
{
	struct s_redir_ms	*next;
	char				*file_name;
	t_tokens			mode;
}	t_redir_ms;

typedef struct s_node_ms
{
	
	struct s_node_ms	*left;
	struct s_node_ms	*right;
	char				*content;
	struct s_redir_ms	*first_redir;
	char				*infile;
	char				*outfile;
	t_tokens			infile_mode;
	t_tokens			outfile_mode;
	t_tokens			shell;
	t_tokens			operator;
}	t_node_ms;

typedef struct s_token_ms
{
	t_tokens			type;
	char				*content;
	struct s_token_ms	*next;
}	t_token_ms;

# endif
