/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:26:31 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/28 18:07:47 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/ioctl.h>

typedef struct	s_env
{
	char			*data;
	struct s_env	*next;
}					t_env;

typedef struct	s_data
{
	t_env	*env;
}				t_data;

int		ft_echo(char **argv);
int		ft_env(t_env *env);
int		ft_pwd(void);
void	ft_exit(char **argv);
int 	ft_cd(char **argv, t_env *env);
int 	ft_export(char **argv, t_env *env);
int 	ft_unset(char **argv, t_env *env);
void    *del_ptr(void *ptr);
int		env_init(t_data *data, char **env_array);
char    *env_name(char *new, char *str);
int 	add_env(char *data, t_env *env);
int 	in_env(t_env *env, char *argv);
int		env_size(t_env *env);
char	*str_env(t_env *env);
void	signal_start(void);
void	signal_exec(void);
void	free_env(t_env *env);

#endif