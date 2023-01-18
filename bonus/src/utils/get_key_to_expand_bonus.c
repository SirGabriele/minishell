#include "../../includes/minishell_bonus.h"

char	*get_key_to_expand(char *content)
{
	char	*key_to_expand;
	int		j;

	j = 0;
	while (ft_isdigit(content[j]) != 1
		&& content[j] != ' ' && content[j] != '\"'
		&& content[j] != '$' && content[j] != '\0'
		&& content[j] != '\'' && content[j] != '='
		&& content[j] != '-' && content[j] != '?'
		&& content[j] != '_')
		j++;
	if (content[j] == '?' || content[j] == '_' || content[j] == '0')//_ et 0 rajoutés
		j++;
	key_to_expand = ft_strndup(content, j);
	if (key_to_expand == NULL)
	{
		free(content);
		perror(NULL);
		return (NULL);
	}
	return (key_to_expand);
}
