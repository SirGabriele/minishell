#include "../../includes/minishell.h"

/*static void	printf_info_structs(t_pipeline_ms *pipeline)
{
	t_cmd_list_ms	*cmd;
	t_redir_ms		*redir;

	int	i;
	ft_printf("\npipeline->first_redir:\n");
	redir = pipeline->first_redir;
	while (redir != NULL)
	{
		ft_printf("\t%s | %d\n", redir->file_name, redir->mode);
		ft_printf("\nredir = redir->next\n");
		redir = redir->next;
	}
	ft_printf("\nPipeline context is:\n"
		"\tInfile = %s\n"
		"\tOutfile = %s\n"
		"\tOutfile_mode = %d\n\n", pipeline->infile, pipeline->outfile, pipeline->outfile_mode);
	cmd = pipeline->first_cmd;
	ft_printf("\npipeline->first_cmd:\n");
	while (cmd != NULL)
	{
		i = 0;
		ft_printf("\tCorrect_path = %s\n", cmd->correct_path);
		while (cmd->cmd_and_args[i] != NULL)
		{
			ft_printf("\tArg[%d] = %s\n", i, cmd->cmd_and_args[i]);
			i++;
		}
		ft_printf("\ncmd = cmd->next\n");
		cmd = cmd->next;
	}
}*/

static void	set_right_values_in_pipeline(t_pipeline_ms *pipeline)
{
	pipeline->infile = "infile1.txt";
	pipeline->outfile = "outfile2.txt";
	pipeline->outfile_mode = TOK_OUTF_APPEND;
	pipeline->first_redir = ft_lstnew_redir("outfile1", TOK_OUTF_TRUNC);
	pipeline->first_redir->next = ft_lstnew_redir("infile1", TOK_INFILE);
	pipeline->first_redir->next->next = ft_lstnew_redir("outfile2", TOK_OUTF_APPEND);
	pipeline->first_cmd = ft_lstnew_cmd("echo -n Ca fonctionne punaise !");//Gerer les return NULL
	pipeline->first_cmd->next = ft_lstnew_cmd("cat");
}

int	test_pipex(void)
{
	t_pipeline_ms	*pipeline;

	pipeline = malloc(sizeof(t_pipeline_ms));
	init_pipeline_struct(pipeline);//met tout à NULL
	set_right_values_in_pipeline(pipeline);
//	printf_info_structs(pipeline);
	if (launch_pipex(pipeline) == -1)
		return (-1);
	return (0);
}
