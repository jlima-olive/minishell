#include "../libft.h"

char	*ft_mat_join(char **mat, int indv, int ind, int total)
{
	char *ret;

	if (mat == NULL)
		return (NULL);
	while (mat[indv])
	{
		ind = 0;
		while (mat[indv][ind])
			ind++;
		total += ind + 1;
		indv++;
	}
	ret = ft_calloc(1, total);
	if (ret == NULL)
		return (NULL);
	ind = 0;
	indv = -1;
	while (mat[++indv])
		while (mat[indv])
		{
			ret[ind] = *(mat[indv]);
			ind++;
			(mat[indv])++;
		}
	return (ret);
}
