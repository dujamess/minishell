#include "../minishell.h"
void    split_path(t_variable  *env,t_path *path)
{
    int i;
    int h;
    char *v;
    h = 0;
    i = 0;
    while(env[i].nom)
    {
        if (ft_strcmp1(env[i].nom,"PATH") == 0)
        {
            path->var_path = ft_split1(env[i].valeur,':');
            while(path->var_path[h])
            {
                v = path->var_path[h];
                path->var_path[h] = ft_strjoin1(path->var_path[h],"/");
                free(v);
                h++;
            }
            break;
        }
        i++;
    }
}

char	*join_commande_path1(t_path *path, char *av)
{
	char	*path_commande;
	int		h;

	h = 0;
	while (path->var_path[h])
	{
		path_commande = ft_strjoin1(path->var_path[h], av);
		if (access(path_commande, F_OK) == 0)
			return (path_commande);
		free(path_commande);
		h++;
	}
	return (NULL);
}
int **cree_pipe(int number_pipe)
{
    int i = 0;
    int **pipes = (int **)malloc(number_pipe * sizeof(int *));
    while(i < number_pipe)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        i++;
    }
    i = 0;
    while (i < number_pipe)
    {
        if (pipe(pipes[i]) == -1) 
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    return pipes;
}
int cherch_input(t_info *info)
{
    int fd = 0;
    int i;
    i = 0;
    while(info->plist->reds && info->plist->reds[i])
    {
        if (info->plist->types[i] == I_RED)
        {
            if (info->plist->reds[i + 1])
            {
                 if ( fd != 0)
                    close(fd);
                fd = open(info->plist->reds[i + 1], O_RDONLY);
                if (fd == -1) 
                {
                    printf("input ----%s\n",info->plist->reds[i + 1]);
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDIN_FILENO);
            }
             else
                break;
        }
        i++;
    }
    return fd;
}
int cherch_output(t_info *info)
{
    int fd = 1;
    int i;
    i = 0;

    dup2(1, STDOUT_FILENO);
    while(info->plist->reds && info->plist->reds[i])
    {
        if (info->plist->types[i] == O_RED)
        {
            if (info->plist->reds[i + 1])
            {
                if ( fd != 0)
                    close(fd);
                fd = open(info->plist->reds[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (fd == -1) 
                {
                    printf("output ----%s\n",info->plist->reds[i + 1]);
                    perror("open");
                    exit(EXIT_FAILURE); 
                }
                dup2(fd, STDOUT_FILENO);
            }
            else
                break;
        }
        else if(info->plist->types[i] == A_RED)
        {
            if (info->plist->reds[i + 1])
            {
                if ( fd != 0)
                    close(fd);
                close(fd);
                fd = open(info->plist->reds[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                dup2(fd, STDOUT_FILENO);
            }
             else
                break;
        }
        i++;
    }
    return fd;
}
void execution_cmd(int ac, t_variable *env, t_path *path, t_info *info)
{
    (void)ac;
    (void)env;
    (void)path;
    // int nb_cmds = info->lst_size;
    int pid;
    // int **pipes = cree_pipe(info->lst_size);
    int i;
    i = 0;
    while (info->plist) 
    {
        pid = fork();
        if (pid == 0)
        {
            if (info->plist->reds)
            {
                cherch_input(info);
                cherch_output(info);
            }
            char *s = join_commande_path1(path, info->plist->parts[i]);
            if (s == NULL) 
            {
                printf("command not found : %s\n",info->plist->parts[i]);
                exit(EXIT_FAILURE);
            }
            execve(s, info->plist->parts, (char **)env);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        info->plist= info->plist->next;
    }
    wait(NULL);
}
