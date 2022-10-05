#include "../../includes/minishell.h"

static char	*delete_quote(char *user_input, int i)
{
	int		j;
	int		k;
	char	*dup;

	j = 0;
	k = 0;
	dup = ft_calloc(sizeof(char), ft_strlen(user_input));
	while (user_input[k] != '\0')
	{
		if (k == i)
			k++;
		else
		{
			dup[j] = user_input[k];
			j++;
			k++;
		}
	}
	dup[j] = '\0';
//	free(user_input);
//	user_input = NULL;
	return (dup);
}

static int	is_quote_closed(char *user_input, int i)
{
	int	j;
	
	j = i + 1;
	while (user_input[j] != user_input[i] && user_input[j] != '\0')
		j++;
	if (user_input[j] == '\0')
		return (-1);
	return (0);
}

    /******************************************************************/
   /*															 	 */
  /*	Detects any isolated quote and deletes it from the line		*/
 /*															  	   */
/******************************************************************/
static char	*delete_isolated_quotes(char *user_input)
{
	int		i;
	char	save;

	i = 0;
	while (user_input[i] != '\0')
	{
		if (user_input[i] == '\"' || user_input[i] == '\'')
		{
			save = user_input[i];
			if (is_quote_closed(user_input, i) == -1)
			{
				user_input = delete_quote(user_input, i);
				continue ;
			}
			i++;
			while (user_input[i] != save)
				i++;
		}
		i++;
	}
	return (user_input);
}

char	*filter_cmd_line(char *user_input, char **env)
{
	int	i;
	(void)env;
	user_input = delete_isolated_quotes(user_input);
	i = 0;
	while (user_input[i] != '\0')
	{
		if (user_input[i] == '\"')
			user_input = manage_dollar_sign(user_input, env);
		i++;
	}
	/*si single quotes, ne pas changer $*/
	/*si double quotes, changer variable env*/	
	return (user_input);
}
