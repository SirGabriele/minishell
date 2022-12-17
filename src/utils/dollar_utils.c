/********************************************************************/
/*                                                     				*/
/*  Determines if the environment variable found is between			*/
/*	single/double quotes or not in any sort of quotes				*/
/*                                                     	 			*/
/*  Parameters:														*/
/*		parsed	-	line from the terminal							*/
/*		i		-	index of the '$' symbol found					*/
/*																	*/
/*  Return:															*/
/*		0	-	env_variable is between double quotes or alone		*/
/*		1	-	env_variable is between single quotes				*/
/*																	*/
/********************************************************************/

int	what_is_dollar_in(const char *parsed, int i)
{
	int		j;
	char	c;

	j = 0;
	while (parsed[j] != '\0')
	{
		if (parsed[j] == '\"' || parsed[j] == '\'')
		{
			c = parsed[j];
			j++;
			while (parsed[j] != c && parsed[j] != '\0')
				j++;
			if (j > i && c == '\"')
				return (0);
			else if (j > i && c == '\'')
				return (-1);
		}
		else if (parsed[j] == '$')
			return (0);
		j++;
	}
	return (-1);
}
