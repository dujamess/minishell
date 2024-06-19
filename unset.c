#include "minishell.h"

void    unistial_vlag(int *flag , int size)
{
    int s = 0;
    while(s < size)
    {
        flag[s] = 0;
        s++;
    }
}

int check_size_new_array(char **av,t_variable *env,int *flag)
{
    int count = 0;
    int i = 0;
    int j = 0;
    while(av[i])
     {
        j = 0;
        while(env[j].nom)
        {
            if ((ft_strcmp1(av[i],env[j].nom) == 0) && flag[j] == 0 )
            {
                flag[j] = 1;
                count++;
            }
            j++;
        }
        i++;
     }
     return ((j - count) +1);
}
void free_env(t_variable *env)
 {
    if (env == NULL)
        return;
    int i;
    i = 0;
    while (env[i].nom != NULL) 
    {
        free(env[i].nom);
        free(env[i].valeur);
        i++;
    }
    free(env);
}

t_variable update_env(t_variable env_line) 
{
    t_variable var;
    var.nom = ft_strdup1(env_line.nom);
    var.valeur = ft_strdup1(env_line.valeur);
    return var;
}
t_variable *builtin_unset(char **av,t_variable *env)
{

    int i = 0;
    while(env[i].nom)
        i++;
    int flag[i];
    unistial_vlag(flag , i);
    int size;
    size = check_size_new_array(av,env,flag);
    t_variable *new_env = malloc(sizeof(t_variable) * size);
    i = 0;
    int j = 0;
    int s = 0;
    while(env[i].nom) 
    {
        j = 0;
        while(av[j])
        {
            if (ft_strcmp1(av[j],env[i].nom) != 0)
                j++;
            else
                break;
        }
        if (av[j] == NULL)
        {
            new_env[s] = update_env(env[i]);
            s++;
        }
        i++;
    }
    new_env[s].valeur = NULL;
    new_env[s].nom = NULL;
    printf("jfjfjf\n");
    return new_env;
}