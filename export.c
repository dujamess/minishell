#include "minishell.h"

char	*ft_substr1(char const *s, int start, int len)
{
	int	i;
	int	j;
	char			*str;

	i = 0;
	j = 0;

	if (!s)
		return (NULL);
	if (ft_strlen((char *) s) - start < len)
		len = ft_strlen((char *) s) - start;
	if (start > ft_strlen((char *) s))
		return (ft_strdup1(""));
	str = malloc (sizeof (char) * (len +1));
	if (!str)
		return (NULL);
	while (i < start)
		i++;
	while (s[i] && j < len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

int valid_argument(char *av)
{
    int i;

    i = 0;
    while(av[i])
    {
        if (av[i] == '=')
            return 1;
        i++;
    }
    return 0;
}

int size_array_env(t_variable *env)
{
    int i;

    i = 0;
    while(env[i].nom)
        i++;
    return i +1;
}
int position_egal(char *av)
{
    int i;
    i = 0;
    while(av[i] && av[i]!= '=')
        i++;
    return i;
}

int	ft_strncmp1(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] == s2[i])
			i++;
		else
		{
			if (s1[i] - s2[i] > 0)
				return (1);
			else
				return (-1);
		}
	}
    if (s2[i] == '\0')
	    return (0);
    return (2);
}

int check_dans_env(char *av,t_variable *env,int n)
{
    int i;

    i = 0;
    while(env[i].nom)
    {
        if (ft_strncmp1(av,env[i].nom,n) == 0)
            return 0;
        i++;
    }
    return 1;
}

t_variable *builtin_export(char **av, t_variable *env) 
{
    int count = 0;
    int i = 0;
    int n = 0;

    while (av[i])
    {
        if (valid_argument(av[i])) 
        {
            n = position_egal(av[i]);
            if (check_dans_env(av[i], env, n))
                count++;
        }
        i++;
    }
    t_variable *new_env = malloc(sizeof(t_variable) * (size_array_env(env) + count + 1));
    i = 0;
    while (env[i].nom) 
    {
        new_env[i].nom = ft_strdup1(env[i].nom);
        new_env[i].valeur = ft_strdup1(env[i].valeur);
        i++;
    }
    while(count > 0)
    {
        new_env[i].nom = ft_strdup1("");
        new_env[i].valeur = ft_strdup1("");
        i++;
        count--;
    }
    new_env[i].nom = NULL;
    new_env[i].valeur = NULL;

    i = size_array_env(env);
    int j = 1; 
    while (av[j])
     {
        if (valid_argument(av[j])) 
        {
            n = position_egal(av[j]);
            if (check_dans_env(av[j], new_env, n)) 
            {
                new_env[i].nom = ft_substr1(av[j], 0, n);
                new_env[i].valeur = ft_strdup1(av[j] + n + 1);
                i++;
            } 
            else
            {
                int k = 0;
                while (new_env[k].nom) 
                {
                    if (ft_strncmp1(av[j], new_env[k].nom, n) == 0)
                    {
                        new_env[k].valeur = ft_strdup1(av[j] + n + 1);
                        break;
                    }
                    k++;
                }
            }
        }
        j++;
    }
    new_env[i].nom = NULL;
    new_env[i].valeur = NULL;
    return new_env;
}