#include "../../includes/minishell.h"

/*static void	printf_info_structs(t_context_ms *context_struct)
{
	t_context_ms	*context;
	t_redir_ms		*all_redir;
//	t_cmd_list_ms	*cmd;

	context = context_struct;
	while (context != NULL)
	{
		ft_putstr_fd("╔═══════════════════════════════════════════════════════════════════════╗\n", 1);
		ft_putstr_fd("║\tcontext\n", 1);
		ft_printf("║\t\tcontext->what_is_pipeline_after = %d\n", context->what_is_pipeline_after);
		ft_printf("║\t\tpipeline = %s\n", context->pipeline);
		all_redir = context->all_redirs->first_redir;
		ft_putstr_fd("║\t╔═══════════════════════════════════════════════════════╗\n", 1);
		ft_putstr_fd("║\t║\tall_redirs:\n", 1);
		while (all_redir != NULL)
		{
			ft_printf("║\t║\t\tfile_name = %s | mode = %d\n", all_redir->file_name, all_redir->mode);
			ft_putstr_fd("║\t║\t\t\t║\n", 1);
			all_redir = all_redir->next;
			ft_putstr_fd("║\t║\tall_redirs = all_redirs->next\n", 1);
		}
		ft_putstr_fd("║\t║\tfirst_cmd:\n", 1);
		cmd = context->first_cmd;
		while (cmd != NULL)
		{
			ft_printf("║\t║\tcmd_and_args = \"%s %s %s\" | correct_path = %s\n", cmd->cmd_and_args[0], cmd->cmd_and_args[1], cmd->cmd_and_args[2], cmd->correct_path);
			cmd = cmd->next; 
		}
		ft_putstr_fd("║\t╚═══════════════════════════════════════════════════════╝\n", 1);
		ft_putstr_fd("║\t\tcontext = context->next\n", 1);
		ft_putstr_fd("╚═══════════════════════════════════════════════════════════════════════╝\n", 1);
		if (context->next != NULL)
		{
			ft_putstr_fd("\t\t\t\t║\t\t\t\t\n", 1);
			ft_putstr_fd("\t\t\t\t║\t\t\t\t\n", 1);
		}
		context = context->next;
	}
}*/

static void	set_right_values_in_context_all_redirs_2(t_all_redirs_ms *all_redirs)
{
	char	*redir = NULL;
//	redir = readline("Pipeline 2\nfirst_redir = ");
	all_redirs->first_redir = ft_lstnew_redir(readline("Pipeline 2\nfirst_out_redir = "), ft_atoi(readline("| mode = ")));
	redir = readline("second_out_redir = ");
	all_redirs->first_redir->next = ft_lstnew_redir(redir, TOK_APPEND);
	redir = readline("third_out_redir = ");
	all_redirs->first_redir->next->next = ft_lstnew_redir(redir, TOK_APPEND);
	redir = readline("fourth_out_redir = ");
	all_redirs->first_redir->next->next->next = ft_lstnew_redir(redir, TOK_TRUNC);
	all_redirs->infile = NULL;
	all_redirs->infile_mode = TOK_NULL;
	all_redirs->outfile = redir;
	all_redirs->outfile_mode = TOK_APPEND;
}

static void	set_right_values_in_context_all_redirs(t_all_redirs_ms *all_redirs)
{
	all_redirs->first_redir = ft_lstnew_redir(readline("Pipeline 1\nfirst_heredoc_delimiter = "), TOK_HEREDOC);
	all_redirs->first_redir->next = ft_lstnew_redir(readline("second_heredoc_delimiter = "), TOK_HEREDOC);
	all_redirs->first_redir->next->next = ft_lstnew_redir(readline("third_true_infile = "), TOK_INFILE);
	all_redirs->infile = readline("True infile = ");
	all_redirs->infile_mode = TOK_INFILE;
	all_redirs->outfile = NULL;
	all_redirs->outfile_mode = TOK_NULL;
}

static void	set_right_values_in_context_2(t_context_ms *context)
{
	context->next = NULL;
	context->all_redirs = malloc(sizeof(t_all_redirs_ms));//check return NULL
	init_context_all_redirs(context->all_redirs);//met tout à NULL
	set_right_values_in_context_all_redirs_2(context->all_redirs);
	context->pipeline = "cat -e";
	context->what_is_pipeline_after = TOK_NULL;
}

static void	set_right_values_in_context(t_context_ms *context)
{
	context->next = NULL;
	context->all_redirs = malloc(sizeof(t_all_redirs_ms));//check return NULL
	init_context_all_redirs(context->all_redirs);//met tout à NULL
	set_right_values_in_context_all_redirs(context->all_redirs);
	context->pipeline = "echo -n coucou";
	context->what_is_pipeline_after = TOK_NULL;
}

int	test_pipex(t_context_ms *context)
{
	set_right_values_in_context(context);
	context->next = malloc(sizeof(t_context_ms));//check return NULL
	init_context_struct(context->next);//met tout à NULL
	set_right_values_in_context_2(context->next);
//	printf_info_structs(context);
	if (launch_exec(context) == -1)
		return (-1);
	return (0);
}
