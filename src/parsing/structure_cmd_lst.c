#include "../../includes/minishell.h"

void	print_pipelines(t_context_ms *cmd_line)
{
	while (cmd_line)
	{
		if (cmd_line->what_is_pipeline_after == TOK_OR_OPER)
			ft_printf(" || ");
		else if (cmd_line->what_is_pipeline_after == TOK_AND_OPER)
			ft_printf(" && ");
		else if (cmd_line->what_is_pipeline_after == TOK_PIPE)
			ft_printf(" | ");
		ft_printf("%s", cmd_line->pipeline);
		cmd_line = cmd_line->next;
	}
	printf("\n");
}

/*
int	get_redirections(t_token_ms *tokens, t_context_ms *cmd_line)
{

}
*/
t_context_ms	*structure_cmd_lst(t_token_ms *tokens)
{
	t_context_ms	*cmd_lst;

	cmd_lst = lstnew_cmd_lst();
	if (!cmd_lst)
		return (NULL);
	else if (get_all_pipelines(tokens, cmd_lst) == -1)
	{
		free_context(cmd_lst);
		return (NULL);
	}
	print_pipelines(cmd_lst); //a supprimer
	/*else if (get_redirections(tokens, cmd_line) == -1)
	{
		free_context(cmd_line);
		return (NULL);
	}*/
	return (cmd_lst);
}
