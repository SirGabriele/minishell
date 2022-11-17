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
}	t_tokens;

typedef struct s_redir_list_ms
{
	struct s_redir_list_ms	*next;
	char					*file_name;
	t_tokens				mode;
}	t_redir_list_ms;

typedef struct s_cmd_list_ms
{
	struct s_cmd_list_ms	*next;
	char					*cmd_and_args;
	char					*correct_path;
}	t_cmd_list_ms;

typedef struct s_all_redir_ms
{
	struct s_redir_list_ms	*output_redir;
	char					*outfile;
	t_tokens				outfile_mode;
	struct s_redir_list_ms	*input_redir;
	char					*infile;
	t_tokens				infile_mode;
}	t_all_redir_ms;

typedef struct s_context_ms
{
	struct s_context_ms		*next;
	struct s_all_redir_ms	*all_redirs;
	t_tokens				what_is_pipeline_after;
	char					*pipeline;
}	t_context_ms;

typedef struct s_token_ms
{
	t_tokens			type;
	char				*content;
	struct s_token_ms	*next;
}	t_token_ms;

# endif
