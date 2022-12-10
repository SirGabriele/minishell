#include "../../includes/minishell.h"

/************************************************************/
/*                                                     		*/
/*  Determines if the environment variable found is valid	*/
/*	If it is, it will be changed. 							*/
/*	If it is not, it will be deleted from the line			*/
/*                                                     	 	*/
/*  Parameters:												*/
/*		content - line from the terminal					*/
/*		env - env variables									*/
/*	Example:												*/
/*		$USER bonjour -> kbrousse bonjour					*/
/*		$U bonjour -> bonjour								*/
/*  Return:													*/
/*		line with env_variable converted or deleted			*/
/************************************************************/
char	*expand_var_with_dollar(char *content, char **env)
{
	int		i;
	char	*var_to_look_for;
	char	*env_var;

	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '$' && what_is_dollar_in(content, i) == 0)
		{
			var_to_look_for = get_var_to_look_for(content + i + 1);
			if (!var_to_look_for)
			{
				free(content);
				return (NULL);
			}
			env_var = extract_env_variable_line(var_to_look_for, env);
			content = manage_dollar(env_var, content, i);
			if (!content)
				return (NULL);
		}
		if (content[i])
			i++;
	}
	return (content);
}
