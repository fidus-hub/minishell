#include "../minishell.h"

int	export(t_headers *headers)
{
    t_env *env_h;
    char **args;

    env_h = headers->env_h;
    args = headers->cmd_h->args;

    t_env *tmp;

    tmp = env_h;
    if (!tmp)
        return (-1);

    if(!args[1])
    {
        if (!tmp)
        return (-1);
        while (tmp)
        {
        printf("%s=%s\n", tmp->var, tmp->val);
        tmp = tmp->suivant;
        }
        return (0);
    }
}

    t_env*newnode = new_node(args[1], args[2]);
    tmp->suivant = newnode;
    newnode->preced = tmp;
    return (0);


// }

    t_env *new_node(char *var, char *val)
{
    t_env *new;

    new = malloc(sizeof(t_env));
    new->var = var;
    new->val = val;
    new->preced = NULL;
    new->suivant = NULL;
    return new;
}