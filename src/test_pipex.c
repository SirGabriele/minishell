#include "../includes/minishell.h"

static void	printf_info_structs(t_pipeline_ms *pipeline)
{
	int	i = 0;
	ft_printf("\npipeline->to_create_trunc:\n");
	while (pipeline->to_create_trunc != NULL && pipeline->to_create_trunc[i] != NULL)
	{
		ft_printf("\t%s\n", pipeline->to_create_trunc[i]);
		i++;
	}
	ft_printf("\nPipeline context is:\n"
		"\tInfile = %s\n"
		"\tOutfile = %s\n"
		"\tOutfile_mode = %d\n\n", pipeline->infile, pipeline->outfile, pipeline->outfile_mode);
	ft_printf("\npipeline->first_cmd:\n"
		"\tArg[0] = %s\n"
		"\tArg[1] = %s\n"
		"\tArg[2] = %s\n"
		"\tArg[3] = %s\n"
		"\tArg[4] = %s\n"
		"\tArg[5] = %s\n"
		"\tArg[6] = %s\n", pipeline->first_cmd->command_and_args[0], pipeline->first_cmd->command_and_args[1], pipeline->first_cmd->command_and_args[2], pipeline->first_cmd->command_and_args[3], pipeline->first_cmd->command_and_args[4], pipeline->first_cmd->command_and_args[5], pipeline->first_cmd->command_and_args[6]);
	ft_printf("\npipeline->first_cmd->next:\n"
		"\tArg[0] = %s\n"
		"\tArg[1] = %s\n", pipeline->first_cmd->next->command_and_args[0], pipeline->first_cmd->next->command_and_args[1]);
}

static void	set_right_values_in_pipeline(t_pipeline_ms *pipeline)
{
	pipeline->to_create_trunc = malloc(sizeof(char *) * 4);
	pipeline->to_create_trunc[0] = "fakeinfile0";
	pipeline->to_create_trunc[1] = "fakeinfile1";
	pipeline->to_create_trunc[2] = "fakeinfile2";
	pipeline->to_create_trunc[3] = NULL;
	pipeline->to_create_append = NULL;
	pipeline->infile = "infile1.txt";
	pipeline->outfile = "outfile1.txt";
	pipeline->outfile_mode = TOK_OUTF_APPEND;
	pipeline->first_cmd = NULL;
}

void	test_pipex(void)
{
	t_pipeline_ms	*pipeline;

	pipeline = malloc(sizeof(t_pipeline_ms));
	init_pipeline_struct(pipeline);//met tout à NULL
	set_right_values_in_pipeline(pipeline);
	pipeline->first_cmd = ft_lstnew_cmd("echo -n Ca fonctionne punaise !");
	pipeline->first_cmd->next = ft_lstnew_cmd("cat");
	printf_info_structs(pipeline);
//	ft_printf("first_cmd = %s\n", pipeline->first_cmd->command[0]);
//	ft_printf("second_cmd = %s\n", pipeline->first_cmd->next->command[0]);
}
