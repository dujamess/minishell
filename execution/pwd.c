#include "../minishell.h"

char   *builtin_pwd()
{
    char *pwd = getcwd(NULL,4096);
    if (!pwd)
        return NULL;
    printf("%s\n",pwd);
    return pwd;
}