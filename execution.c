#include "minishell.h"
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
void execution_cmd(int ac, t_variable *env, t_path *path, t_info *info)
{
    (void)ac;
    int nb_cmds = 1;
    printf("nb_cmds : %d\n",nb_cmds);
    int pid;
    int **pipes = cree_pipe(info->lst_size);
    int i;
    i = 0;
    while (i < nb_cmds) 
    {
        pid = fork();
        if (pid == 0) 
        {
            if (info->plist->reds && info->plist->types[i] == O_RED) 
            {
                int fd = open(info->plist->reds[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (fd == -1) 
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            } 
            else if (info->plist->reds && info->plist->types[i] == I_RED) 
            {
                int fd = open(info->plist->reds[i + 1], O_RDONLY);
                if (fd == -1) 
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
            }
            if (info->plist->reds && info->plist->types[i] == PIPE)
            {
                if (i != 0) 
                { 
                    dup2(pipes[i - 1][0], STDIN_FILENO);
                    close(pipes[i - 1][1]);
                }
                if (i != nb_cmds - 1)
                {
                    dup2(pipes[i][1],STDOUT_FILENO);
                    close(pipes[i][0]);
                }
            } 
            char *s = join_commande_path1(path, info->plist->parts[i]);
            if (s == NULL) 
            {
                fprintf(stderr, "Erreur: commande non trouvée.\n");
                exit(EXIT_FAILURE);
            }
            execve(s, info->plist->parts, (char **)env);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    i = 0;
    
    while (i < nb_cmds - 1) 
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
    i = 0;
    while (i < nb_cmds) 
    {
        wait(NULL);
        i++;
    }
}
