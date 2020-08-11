
#include "ft_ls.h"

char	*ft_strjoin_safe(char **str1, const char *str2)
{
	char *result;

	result = ft_strjoin(*str1, str2);
	ft_strdel(str1);
	return (result);
}
