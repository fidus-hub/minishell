#include "../minishell.h"

/*
  Function Declarations for builtin shell commands:
 */
int	cd(t_headers *headers);
int	echo(t_headers *headers);
int pwd(t_headers *headers);
int	eexit(t_headers *headers);
int	env(t_headers *headers);
int	export(t_headers *headers);
//int	unset(t_headers *headers);


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
	"export",
	//"unset",
};

int (*builtin_func[]) (char **) =
{
	&cd,
	&echo,
	&pwd,
	&eexit,
	&env,
	&export,
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

