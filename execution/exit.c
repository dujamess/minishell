#include "../minishell.h"

int	ft_isdigit1(char *c)
{
	int	i;

	i = 0;
	if (c[i] == '+' || c[i] == '-')
		i++;
	while (c[i] && (c[i] >= '0' && c[i] <= '9'))
		i++;
	if (c[i] == '\0')
		return (1);
	else
		return (0);
}
int	ft_atoi1(const char *str)
{
	int				signe;
	int				i;
	long			result;

	i = 0;
	result = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		signe = signe * -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	result = result * signe;
	return ((int)result);
}

void    builtin_exit(int ac ,char **av)
{
    if (ac == 1)
        exit(0);
    if (ac > 2)
    {
        printf("plusieur argument\n");
        exit(2);
    }
    if (ft_isdigit1(av[1]) == 0)
    {
        printf("argument non numeric\n");
        exit(2);
    }
    exit(ft_atoi1(av[1]));
}