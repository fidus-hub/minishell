#include "../minishell.h"

int	env(t_headers *headers)
{
    t_env *env_h;

    env_h = headers->env_h;

    if (!env_h)
        return (-1);
    while (env_h)
    {
        printf("%s=%s\n", env_h->var, env_h->val);
        env_h = env_h->suivant;
    }
    return (0);
}