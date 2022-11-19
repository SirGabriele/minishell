#include "../../includes/minishell.h"

static t_context_ms	*get_pipeline(t_context_ms *cmd_lst, t_token_ms *tokens)
{
	while (tokens->type != TOK_PIPE && tokens->type != TOK_OR_OPER
		&& tokens->type != TOK_AND_OPER && tokens->next)
	{
		cmd_lst->pipeline = ft_strjoin_free_first(cmd_lst->pipeline, tokens->content);
		if (!cmd_lst->pipeline)
			return (NULL);
		cmd_lst->pipeline = parse_spaces(cmd_lst->pipeline, tokens);
		if (!cmd_lst->pipeline)
			return (NULL);
		tokens = tokens->next;
	}
	if (tokens->next)
	{
		cmd_lst->next = lstnew_cmd_lst();
		cmd_lst->next->what_is_pipeline_after = tokens->type;
	}
	else
		cmd_lst->next = NULL;
	return (cmd_lst);
}

t_context_ms	*get_all_pipelines(t_token_ms *tokens, t_context_ms *cmd_lst)
{
	t_context_ms	*cmd_lst_cpy;
	t_token_ms		*tokens_cpy;

	cmd_lst_cpy = cmd_lst;
	tokens_cpy = tokens;
	while (tokens_cpy->next)
	{
		cmd_lst_cpy = get_pipeline(cmd_lst_cpy, tokens_cpy);
		if (!cmd_lst_cpy)
		{
			free_context(cmd_lst);
			return (NULL);
		}
		tokens_cpy = increm_tokens_copy(tokens_cpy);
		cmd_lst_cpy = cmd_lst_cpy->next;
	}
	return (cmd_lst);
}
