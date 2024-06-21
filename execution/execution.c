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
int cherch_input(t_info *info ,int flag)
{
    int i;
    i = 0;
    while(info->plist->reds && info->plist->reds[i])
    {
        if (info->plist->types[i] == I_RED)
        {
            if (info->plist->reds[i + 1])
            {
                close(info->fd0);
                info->fd0 = open(info->plist->reds[i + 1], O_RDONLY);
                if (info->fd0 == -1) 
                {
                    printf("input ----%s\n",info->plist->reds[i + 1]);
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(info->fd0, STDIN_FILENO);
            }
        }
        i++;
    }
    // if (info->plist->next && info->fd0 == -1)
    //     flag = 0;
    return flag;
}
int cherch_output(t_info *info ,int flag)
{
    int i;
    i = 0;
    while(info->plist->reds && info->plist->reds[i])
    {
        if (info->plist->types[i] == O_RED)
        {
            if (info->plist->reds[i + 1])
            {
                close(info->fd1);
                info->fd1 = open(info->plist->reds[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (info->fd1 == -1) 
                {
                    printf("output ----%s\n",info->plist->reds[i + 1]);
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(info->fd1, STDOUT_FILENO);
            }
        }
        else if(info->plist->types[i] == A_RED)
        {
            if (info->plist->reds[i + 1])
            {
                close(info->fd1);
                info->fd1 = open(info->plist->reds[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (info->fd1 == -1) 
                {
                    printf("output ----%s\n",info->plist->reds[i + 1]);
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(info->fd1, STDOUT_FILENO);
            }
        }
        i++;
    }
    // if (info->plist->next && info->fd1 == -1)
    //     flag = 1;
    return flag;
}
void execution_cmd(int ac, t_variable *env, t_path *path, t_info *info, char **en)
{
    (void)ac;
    (void)env;
    (void)path;
    int pid;
    // int fd[2];
    int i;
    i = 0;
    while (info->plist) 
    {
        int flag1 = 2;
        int flag0 = 2;
        // pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            char *s = join_commande_path1(path, info->plist->parts[i]);
            if (s == NULL) 
            {
                printf("command not found : %s\n",info->plist->parts[i]);
                if (info->plist->reds)
                {
                    cherch_input(info,flag0);
                    cherch_output(info,flag1);
                }
                exit(EXIT_FAILURE);
            }
            if (info->plist->reds)
            {
                flag0 = cherch_input(info,flag0);
                flag1 = cherch_output(info,flag1);
                // if (flag0 != 2 && info->fd0)
                // {
                //     dup2(fd[0],STDIN_FILENO);
                //     close(fd[1]);
                // }
                // if (flag1 != 2 && info->fd1)
                // {
                //     dup2(fd[1],STDOUT_FILENO);
                //     close(fd[0]);
                // }
            }
            execve(s, info->plist->parts, en);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        info->plist= info->plist->next;
    }
    // while(info->plist)
    // {
        wait(NULL);
    //     info->plist= info->plist->next;
    // }
}
