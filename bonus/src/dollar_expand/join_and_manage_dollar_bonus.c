#include "../../includes/minishell_bonus.h"

static char	*replace_dollar_digit(char *new_parsed, char *parsed, int i)
{
	if (parsed[i + 1] == '0')
	{
		new_parsed = ft_strjoin_free_first(new_parsed, "minishell");
		if (!new_parsed)
			return (NULL);
		new_parsed = \
			ft_strjoin_free_first(new_parsed, parsed + i + 2);
		return (new_parsed);
	}
	new_parsed = \
		ft_strjoin_free_first(new_parsed, parsed + i + 2);
	return (new_parsed);
}

/****************************************************************/
/*                                                     			*/
/*  Replaces dollar by env variable								*/
/*                                                     	 		*/
/*  Parameters:													*/
/*		env_var	-	env variable line							*/
/*		content	-	string with dollar							*/
/*		i		-	dollar index								*/
/*																*/
/*  Return:														*/
/*		content	-	the newly formed line						*/
/*																*/
/****************************************************************/

char	*join_and_manage_dollar(char *new_parsed, char *parsed, \
	char *value, int key_len, int i)
{
	if (value)
	{
		new_parsed = ft_strjoin_free_first(new_parsed, value);
		if (!new_parsed)
			return (NULL);
		new_parsed = \
			ft_strjoin_free_first(new_parsed, parsed + i + key_len + 1);
	}
	else if (!examine_dollar_conditions(parsed, i))
	{
		new_parsed = \
			ft_strjoin_free_first(new_parsed, parsed + i + key_len + 1);
		return (new_parsed);
	}
	else if (examine_dollar_conditions(parsed, i) == 2)
		new_parsed = replace_dollar_digit(new_parsed, parsed, i);
	return (new_parsed);
}
