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

int	get_pipelines(t_token_ms *tokens, t_context_ms *cmd_line)
{
	t_context_ms	*cmd_line_cpy;
	t_token_ms		*tokens_cpy;

	cmd_line_cpy = cmd_line;
	tokens_cpy = tokens;
	while (tokens_cpy->next)
	{
		if (tokens_cpy->type == TOK_PIPE || tokens_cpy->type == TOK_OR_OPER
			|| tokens_cpy->type == TOK_AND_OPER)
		{
			cmd_line_cpy->next = lstnew_cmd_line();
			cmd_line_cpy = cmd_line_cpy->next;
			cmd_line_cpy->what_is_pipeline_after = tokens_cpy->type;
			tokens_cpy = tokens_cpy->next;
		}
		else
		{
			cmd_line_cpy->pipeline \
				= ft_strjoin(cmd_line_cpy->pipeline, tokens_cpy->content);
			delete_useless_spaces(cmd_line_cpy->pipeline);
			if (!cmd_line_cpy->pipeline)
				return (-1);
			tokens_cpy = tokens_cpy->next;
		}
	}
	return (0);
}
/*
int	get_redirections(t_token_ms *tokens, t_context_ms *cmd_line)
{

}
*/
t_context_ms	*structure_cmd_line(t_token_ms *tokens)
{
	t_context_ms	*cmd_line;

	cmd_line = lstnew_cmd_line();
	if (!cmd_line)
		return (NULL);
	else if (get_pipelines(tokens, cmd_line) == -1)
	{
		free_context(cmd_line);
		return (NULL);
	}
	print_pipelines(cmd_line); //a supprimer
	/*else if (get_redirections(tokens, cmd_line) == -1)
	{
		free_context(cmd_line);
		return (NULL);
	}*/
	return (cmd_line);
}
