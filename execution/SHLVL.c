#include "../minishell.h"
int	ft_calcul(long int n)
{
	int	i;

	i = 1;
	if (n >= 0 && n <= 9)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa1(int n)
{
	char		*str;
	int			j;
	long int	m;

	m = (long int)n;
	j = ft_calcul(m);
	str = malloc(sizeof(char) * (j) +1);
	if (!str)
		return (NULL);
	str[j] = '\0';
	j--;
	if (m == 0)
		str[0] = '0';
	if (m < 0)
	{
		str[0] = '-';
		m = m * -1;
	}
	while (m > 0 && j >= 0)
	{
		str[j--] = m % 10 + '0';
		m = m / 10;
	}
	return (str);
}
void    augment_level_shlvl(t_variable *env)
{
    int i;

    i = 0;
    while(env[i].nom)
    {
        if (ft_strcmp1(env[i].nom,"SHLVL") == 0)
            env[i].valeur = ft_strdup1(ft_itoa1(ft_atoi1(env[i].valeur) + 1));
        i++;
    }
}