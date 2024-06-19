#include "minishell.h"

void    herdoc_appel(t_info *info)
{
    if (info->plist && info->plist->reds)
	{
		int j = 0;
		int l = 0;
		while(info->plist->reds[l])
			l++;
		while(info->plist->reds[j])
		{
			if (ft_strcmp(info->plist->reds[j],"<<") == 0)
			{
				heredoc(info->plist->reds[l - 1]);
				break;
			}
			j++;
		}
	}
}
void heredoc(char *av) 
{
    pid_t t;
    char line[1024];
    ssize_t bytes_read;
    t = fork();
    if (t == 0) 
    {
        write(1,"> ",2);
        while ((bytes_read = read(STDIN_FILENO, line, sizeof(line))) > 0) 
        {
            if (strncmp(line, av,ft_strlen(av)) == 0 && line[ft_strlen(av)] == '\n') 
                exit(1);
            write(1,"> ",2);
        }
    } 
    else
        wait(NULL);
}