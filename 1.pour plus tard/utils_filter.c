char	*get_tmp_without_quotes(char *tmp, char *user_input)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (user_input[j])
	{
		if (user_input[j] == '\'' || user_input[j] == '\"')
		{
			k = j;
			j++;
			while (user_input[j] !=  user_input[k])
			{
				tmp[i] = user_input[j];
				i++;
				j++;
			}
			j++;
		}
		else
		{
			tmp[i] = user_input[j];
			i++;
			j++;
		}	
	}
	tmp[i] = '\0';
	return (tmp);
}
