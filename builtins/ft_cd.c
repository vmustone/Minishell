/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:22:49 by villemuston       #+#    #+#             */
/*   Updated: 2023/07/28 15:28:06 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static int  update_pwd(t_env *env)
{
    char current_dir[PATH_MAX];
    char *pwd;

    if (getcwd(current_dir, PATH_MAX) == NULL)
        return (1);
    if (!(pwd = ft_strjoin("PWD=", current_dir)))
        return (1);
    if (in_env(env, pwd) == 0)
        add_env(pwd, env);
    free(pwd);
    return (0);
}

static char *get_path(t_env *env, char *str, int len)
{
    int     i;
    int     j;
    int     size;
    char    *pwd;

    i = 0;
    j = 0;
    while (env && env->next)
    {
        if (ft_strncmp(env->data, str, len) == 0)
        {
            size = ft_strlen(env->data) - len;
            pwd = malloc(sizeof(char) * size + 1);
            if (!pwd)
                return (NULL);
            pwd = ft_strdup(env->data + len + 1);
            return (pwd);
        }
        env = env->next;
    }
    return (NULL);
}

int ft_cd(char **argv, t_env *env)
{
    int     ret;
    char    *home_path;

    ret = 0;
    if (!argv[1])
    {
        home_path = get_path(env, "HOME", 4);
        if (!home_path)
        {
            ft_putendl_fd("minishell : cd: HOME not set", 2);
            return 1;
        }
        ret = chdir(home_path);
        free(home_path);
    }
    else
        ret = chdir(argv[1]);
    if (ret != 0)
    {
        perror("error");
        return (1);
    }
    update_pwd(env);
    return (0);
}