#include "../headers/minishell.h"

static int	arrsize(char **arr)
{
	int i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**arrjoin(char **arr, char *str) // might leak
{
	char	**newarr;
	int		size;

	if (!arr)
	{
		newarr = (char **)malloc(sizeof (char*) *2);
		newarr[0] = str;
		newarr[1] = NULL;
		return (newarr);
	}
	size = arrsize(arr);
	newarr = (char **)malloc(sizeof (char*) * (size + 2));
	int i = 0;
	while (arr[i])
		newarr[i] = arr[i], i++;
//	free (arr);
	newarr[i] = str;
	i++;
	newarr[i] = NULL;
	return (newarr);
}