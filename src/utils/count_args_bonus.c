#include "../../includes/minishell.h"

/****************************************************************/
/*																*/
/*	Counts the number of arguments that the command has			*/
/*																*/
/*	Parameters:													*/
/*		content	-	a double array containing the command and	*/
/*					its arguments								*/
/*																*/
/*	Return:														*/
/*		i		-	the count									*/
/*																*/
/****************************************************************/

int	count_args(char **content)
{
	int	i;

	i = 0;
	while (content[i])
		i++;
	return (i);
}
