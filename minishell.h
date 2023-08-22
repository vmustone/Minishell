/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:52:58 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/21 17:19:36 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "libft/libft.h"
# include <termios.h>
# include <sys/ioctl.h>

# define T_COMMAND		42
# define T_WORD			43
# define T_PIPE			44
# define T_ARROW_R		45
# define T_ARROW_L		46
# define T_ARROW_R_2	47
# define T_ARROW_L_2	48
# define T_VARIABLE		49

int		g_exit_status;

typedef struct s_allocations
{
	void	*allocations[5000];
	int		count;
}				t_allocations;

typedef struct s_env
{
	char			*data;
	struct s_env	*next;
}					t_env;

typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}					t_pid;

typedef struct s_exec{
	char			*cmd;
	char			**argv;
	int				read_fd;
	int				write_fd;
	struct s_exec	*next;
}				t_exec;

typedef struct s_tokens{
	char			*data;
	int				type;
	struct s_tokens	*next;
}				t_tokens;

typedef struct s_here_docs{
	int				fd;
	char			*doc_name[50];
	int				count;
}				t_here_docs;

typedef struct s_shell
{
	t_env			*env;
	t_pid			*pids;
	t_exec			*exec;
	t_tokens		*tokens;
	t_allocations	*allocs;
	t_here_docs		*here_docs;
	char			**org_env;
}				t_shell;

/*REMOVE BEFORE EVAL (remove the functions too)*/
void			print_tokens(t_tokens	*head);
void			print_exec(t_exec *head);

/*init functions*/
t_allocations	*init_allocs(void);
t_env			*env_init(char **env_array, t_allocations *allocs);
t_here_docs		*init_here_docs(t_shell *shell);
void			unlink_heredocs(t_shell *shell);

/*error handling*/
void			shell_error(char *error, int exit_code, t_allocations *allocs);
void			ft_error(char *error);

/*reimagined lib functions*/
char			*shell_ft_strdup(const char *s1, t_allocations *allocs);
char			*shell_ft_substr(char *s, int start, int len,
					t_allocations *allocs);
char			**shell_ft_split(char const *s, char c, t_shell *shell);
char			*shell_ft_strjoin(char const *s1, char const *s2,
					t_shell *shell);
char			*shell_ft_itoa(int n, t_shell *shell);

/*allocation and free functions*/
void			*oh_my_malloc(size_t size, t_allocations *allocs);
void			oh_my_free(t_allocations *allocs);

/*lexer*/
t_tokens		*lexer(char *input, t_shell *shell);
char			**split_shell_input(char *str, t_shell *shell);
int				pipes_and_redirections(char *str, int i);
int				open_quote(char *str, int i);
t_tokens		*create_tokens(char **splitted_input, t_shell *shell);
int				skip_spaces(char *str, int i);
int				identify_variable(char *str);
char			*set_data(char *str, t_shell *shell);
int				check_for_arrangement_errors(t_tokens *tokens);
int				is_quoted(char *str);
char			*remove_quotes(char *str, t_shell *shell, int i, int j);
int				set_node_values(char **splitted_input,
					t_tokens **node, t_shell *shell);
int				last_time(char **str);
int				define_token_type(char *str, int last_run);
void			find_word_or_end(char *str, int *i, int *k);
char			*pipe_rdr_str(t_shell *shell, int *k, int *i, char *str);
char			*quote_str(t_shell *shell, int *k, int *i, char *str);
void			init_split_variables(int *i, int *j, int *k);
char			*dollar_str(t_shell *shell, int *k, int *i, char *str);
int				counter_dollar(int i, char *str, int *count);
int				counter_normal_word(int i, char *str, int *count);
int				is_valid_variable_char(char c);

/*parser*/
t_exec			*make_exec_node(t_tokens *temp, t_shell *shell,
					int read_fd, int write_fd);
t_exec			*parser(t_shell *shell);
int				here_doc(char *delimeter, t_shell *shell);
int				do_pipe(t_exec *last);
void			redir_errors(int error, t_tokens *temp);
char			*make_expand(char *data, char *var, t_shell *shell);
int				is_single_quoted(char *data);
char			*remove_quotes_and_dollar(char *data,
					int remove_dollar, t_shell *shell);
void			reset_fds(int *read_fd, int *write_fd);
int				set_write_fd(t_tokens *temp, int write_fd);
int				set_read_fd(t_tokens *temp, int read_fd, t_shell *shell);
int				parser_set_read_fd(t_exec *head, int read_fd);
int				parser_set_write_fd(t_exec *head, int write_fd);
void			signal_ctl_c_heredoc(int sig);
t_exec			*parser_close_all_fds(t_exec *head);
void			close_fds(int read_fd, int write_fd);
int				set_fds(int *write_fd, int *read_fd,
					t_tokens *temp, t_shell *shell);
t_exec			*check_and_return(t_exec *ret, int read_fd, int write_fd);
void			fd_do_if(t_exec *head, int read_fd, int write_fd);
int				do_pipe_if(t_tokens *temp, t_exec *head, int *r_fd);
t_exec			*last_node(t_exec *head);

/*executer*/
void			executer(t_shell *shell, int org_write, int org_read);
void			save_pid(pid_t pid, t_shell *shell);
int				execute_command(t_exec *exec, t_shell *shell);
char			*get_env(char *var, t_env *env);
int				is_builtin(char *command);
void			wait_pids(t_shell *shell);
int				builtin(t_exec *exec, t_shell *shell);
int				save_fds(int *org_write, int *org_read);
void			close_all_fds(t_shell *shell, int org_write, int org_read);
void			child(t_exec *head, t_shell *shell,
					int org_write, int org_read);
int				dup_fds(t_exec *head, int org_write, int org_read);
char			**set_expansion(t_exec *exec, t_shell *shell);

/*builtin functions*/
int				ft_echo(char **argv);
int				ft_env(t_env *env);
int				ft_pwd(void);
void			ft_exit(char **argv, t_allocations *all);
int				ft_cd(char **argv, t_env *env);
int				ft_export(char **argv, t_env *env);
int				ft_unset(char **argv, t_env *env);
int				in_env(t_env *env, char *argv);
int				add_env(char *data, t_env *env);
char			*env_name(char *new, char *str);
char			*str_env(t_env *env);
int				env_size(t_env *env);
void			free_env(t_env *env);
int				len_of_env(char **argv);
int				check_arg(char *str);

/*signals*/
void			signal_start(void);
void			close_echo(struct termios *ter);
void			reset_echo(struct termios *ter);
void			handle_ctrl_d(void);
void			sig_handler_child(int signum);
void			sigint_heredoc(int sig);

#endif
