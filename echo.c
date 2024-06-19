#include "minishell.h"

void    builtin_echo(int ac,char **av)
{
    int i;
    (void)ac;
    i = 0;
    if (ft_strcmp1(av[1],"-n") == 0)
    {
        i+=2;
        while(av[i])
        {
            printf("%s ",av[i]);
            i++;
        }
    }
    else
    {
        i = 0;
        i+=1;
        while(av[i])
        {
            printf("%s ",av[i]);
            i++;
        }
        printf("\n");
    }
}