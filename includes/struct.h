#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_tokens
{
	TOK_NULL, /*value = 0*/
	TOK_STRING, /*value = 1*/
	TOK_OP_PAR, /*value = 2*/
	TOK_CL_PAR, /*value = 3*/
	TOK_INF_REDIR, /*value = 4*/
	TOK_OUTF_TRUNC, /*value = 5*/
	TOK_HEREDOC, /*value = 6*/
	TOK_OUTF_APPEND, /*value = 7*/
	TOK_PIPE, /*value = 8*/
	TOK_AND_OPER, /*value = 9*/
	TOK_OR_OPER, /*value = 10*/
}	t_tokens;

typedef struct s_cmd_list_ms
{
	char					*correct_path;
	char					*cmd_and_args;
	struct s_cmd_list_ms	*next;
}	t_cmd_list_ms;

typedef struct s_pipeline_ms
{
	char					**to_create_trunc;
	char					**to_create_append;
	char					*infile;
	char					*outfile;
	t_tokens				outfile_mode;
	struct s_cmd_list_ms	*first_cmd;
}	t_pipeline_ms;

typedef struct s_token_ms
{
	t_tokens			type;
	char				*content;
	struct s_token_ms	*next;
}	t_token_ms;

# endif
