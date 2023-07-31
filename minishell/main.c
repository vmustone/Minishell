#include "includes/builtin.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	char **str = malloc(sizeof(char) * 1000);
	char **str1 = malloc(sizeof(char) * 1000);

	str[0] = ft_strdup("export");
	str[1] = ft_strdup("a=10");
	str[2] = NULL;

	str1[0] = ft_strdup("unset");
	str1[1] = ft_strdup("HEI=MOIMOI");
	str1[2] = NULL;

	t_data	data;
	
	signal_start();

	const char	*input = "MINISHELL ";
	
	signal_exec();
	
	readline(input);
	
	if (env_init(&data, env) == 0)
        printf("Environment variables initialized.\n");
	
	else
		printf("error");
	

	ft_export(argv, data.env);
	printf("\n");
	ft_env(data.env);

	free_env(data.env);
	int i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	i = 0;
	while (str1[i])
	{
		free(str1[i]);
		i++;
	}
	free(str1);
	return (0);
}