#include "minishell.h"

t_variable  *check_variable(t_variable *my_env,char *variable)
{
    int i;

    i = 0;
    while(my_env[i].nom)
    {
        if(ft_strcmp1(my_env[i].nom,variable) == 0)
            return (&my_env[i]);
        i++;
    }
    return NULL;
}
int    builtin_cd(int ac,char **av,t_variable *my_env)
{
    char *oldpwd = getcwd(NULL, 4096);
    char  *pwd;
    t_variable *path;
    t_variable *pwd_env;
    if(ac == 1)
    {
        path = check_variable(my_env,"HOME");
        if(path == NULL)
            printf("variable HOME non trouver dans votre env\n");
        int t = chdir(path->valeur);
        if (t == -1)
        {
            printf("erreur chdir\n");
            return 0;
        }
        pwd_env= check_variable(my_env,"PWD");
        if (pwd_env)
        {
            pwd = getcwd(NULL, 4096);
            if (!pwd)
                return 0;
            free(pwd_env->valeur);
            pwd_env->valeur = pwd;
        }
        pwd_env = check_variable(my_env,"OLDPWD");
        if (pwd_env)
        {
            if (!oldpwd)
                return 0;
            free(pwd_env->valeur);
            pwd_env->valeur = oldpwd;
        }
    }
    else
    {
        if(access(av[1],F_OK) != 0 || access(av[1],X_OK) != 0)
            printf("%s : not directory \n",av[1]);
        else
        {
            chdir(av[1]);
            pwd_env= check_variable(my_env,"PWD");
            pwd = getcwd(NULL, 4096);
            pwd_env->valeur = pwd;
            pwd_env = check_variable(my_env,"OLDPWD");
            pwd_env->valeur = oldpwd;
        }
    }
    return 0;
}