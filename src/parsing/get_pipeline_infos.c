#include "../../includes/minishell.h"

static char	**get_pipeline(t_token_ms *tokens)
{
	char		**pipelines;
	int			nb_tokens_left;
	int			i;

	nb_tokens_left = count_nb_of_tokens_left(tokens);
	pipelines = malloc((nb_tokens_left + 1) * sizeof(char *));
	if (!pipelines)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (check_if_token_is_redir(tokens->type))
			tokens = tokens->next->next;
		else
		{
			pipelines[i] = NULL;
			pipelines[i] = ft_strjoin(pipelines[i], tokens->content);
			if (!pipelines[i])
				return (NULL);
			tokens = tokens->next;
			i++;
		}
	}
	pipelines[i] = NULL;
	return (pipelines);
}

void	execution(char **content)//a supprimer
{
	int	len;

	len = ft_strlen(content[0]);
	if (!ft_strncmp(content[0], "echo", len))
		ft_echo(content + 1);
	else if (!ft_strncmp(content[0], "cd", len))
		ft_cd(content + 1);
	else if (!ft_strncmp(content[0], "pwd", len))
		ft_pwd();
	else if (!ft_strncmp(content[0], "env", len))
		ft_env(content + 1, NULL);
	/*else if (!ft_strncmp(content[0], "export", len))
		ft_export(content + 1, NULL);*/
}

/************************************************************/
/*															*/
/*	Gets infos about redirections and get the command		*/
/*															*/
/*	Parameters:												*/
/*		tokens		-	link								*/
/*		shell		-	what is command in					*/
/*		operators	-	the last two operators of 			*/
/*						the command line					*/
/*															*/
/*	Return:													*/
/*		binary_tree	-	edited binary_tree					*/
/*															*/
/************************************************************/

t_node_ms	*get_pipeline_infos(t_token_ms *tokens, t_enum_token shell, \
	t_enum_token *operators)
{
	t_node_ms	*binary_tree;

	binary_tree = get_redirections_infos(tokens, operators);
	if (!binary_tree)
		return (NULL);
	binary_tree->content = get_pipeline(tokens);
	if (!binary_tree->content)
	{
		free_redirs_list(binary_tree->first_redir);
		free_redirs_infos(binary_tree);
		free(binary_tree);
		return (NULL);
	}
	binary_tree->shell = shell;
	execution(binary_tree->content);//a supprimer
	return (binary_tree);
}
