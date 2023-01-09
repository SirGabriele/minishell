#include "../../includes/minishell.h"

/*t_env_ms	*extend_env_list(char *content, t_env_ms *env_ll)
{
	t_env_ms	*tmp_env;

	tmp_env = env_ll;
	while (env_ll->next)
		env_ll = env_ll->next;
//	env_ll->next = get_env(content);
	env_ll->next = ft_lstnew_env_entry(content);
	if (!env_ll)
		return (NULL);	
	return (tmp_env);
}*/
