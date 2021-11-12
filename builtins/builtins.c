#include "../minishell.h"

/*
  Function Declarations for builtin shell commands:
 */
int	cd(char **args);
int	echo(char **args);
int pwd(char **args);
int	eexit(char **args);
int	env(t_env *env_h);
//int	export(char **args);
//int	unset(char **args);


/*
  List of builtin commands, followed by their corresponding functions.
 */
char	*builtin_str[] =
{
	"cd",
	"echo",
	"pwd",
	"exit",
	"env",
	//"export",
	//"unset",
};

int (*builtin_func[]) (char **) =
{
	&cd,
	&echo,
	&pwd,
	&eexit,
	&env,
	//&export,
	//&unset,
};


int	num_builtins()
{
	return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/




//int	export(char **args)
//{

//}

//int	unset(char **args)
//{

//}

//int	env(char **args)
//{

//}

