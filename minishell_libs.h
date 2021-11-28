/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_libs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:51:13 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/28 16:35:33 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LIBS_H
# define MINISHELL_LIBS_H
# define PATH_MAX 4097
# define BUFFER_SIZE 100

// flo= LIMITER text save
// flo= many echo pipe
// Pietro= finish unset
// Pietro= exit
// both= basically more test (for example: signal)
// both= test the pipes
// leak test
// $?
// LIMITER: make the code to handel the LIMITER
// we skip = VAR=x
// pipe : only for the shell function - not for our BUILTIN?

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define READ 0
# define WRITE 1
# define RED "\033[0;31m"
# define GR "\033[0;32m"
# define YE "\033[0;33m"
# define BL "\033[0;34m"
# define PU "\033[0;35m"
# define CY "\033[0;36m"
# define WH "\033[0;37m"
# define D "\033[0m"
//# define PATH = "~/minishell/sbin/"

typedef enum command_typ
{
	SHELL,
	BUILTIN,
	IGNORE
} e_cmd;

typedef enum redirection_typ
{
	INFILE,
	OUTFILE,
	LIMITER
} e_red;

typedef struct command
{
	char	**cmd;
	int		nb_arg;
	e_cmd	cmd_type;
	int		(*f_ptr)(void *st, void *arr);
	int		fd_in;
	char	*name_in;
	char	*limiter;
	int		fd_out;
	char	*name_out;
} t_cmd;

typedef struct structure
{
	char	*input;
	char	*buf;
	char	*buf_tmp;
	int		nb_cmd;
	int		tr;
	int		arg;
	int		digit;
	int		all;
	int		exp;
	int		force_expand;
	int		len;
	char	**env;
	t_cmd	*arr;
	int		skip_space;
	int		argc;
	char	**argv;
	int		cancel;
	int		res;
} t_struct;

// main.c
void	free_memory(t_struct *cmd);
int		ms_sig_hook(void);
int		run_exit(void *stt, void *cmd);

// parsing: 0_expand_input.c
void	bufferize_input(t_struct *st, char *str, int i);
int		manage_simple_quote(t_struct *st, char *str, int i);
int		manage_doppel_quote(t_struct *st, char *str, int i);
int		launch_expand_variable(t_struct *st, char *str, int i);
//parsing: expand_variable.c
int		expand_variable(t_struct *st, char *str, int i);
int		expand_special_variable(t_struct *st, char *str, int i);
// parsing : expand_variable_utils.c
int		manage_expand_variable(t_struct *st);
int		find_match(t_struct *st, int e, char *var, int pos);
int		is_variable_end(t_struct *st, unsigned char c);
int		is_special_variable(unsigned char c);
void	write_variable(t_struct *st, int e, int j);
// parsing: 1_extract_cmd.c
int		extract_cmd(t_struct *st);
// parsing: 2_parse_input.c
int		parse_input(t_struct *st);
// parsing: 3_extract_redirection.c
int		count_lengh_name(t_struct *st, int i);
int		extract_redirection(t_struct *st, int i);
int		test_synthaxe(t_struct *st, int i, e_red redirection_typ);
// parsing: extract_file.c
int		extract_infile(t_struct *st, int i);
int		extract_limiter(t_struct *st, int i);
int		extract_outfile(t_struct *st, int i);
char	*expand_name(char **env, char **name);
//parsing: add_path.c
int		add_path(t_struct *st);
//parsing: ms_buffer.c
char	*add_char_to_buf(t_struct *st, char c);
char	*add_number_to_buf(t_struct *st, int nb);
int		transfert_buf_input(t_struct *st);

// parsing: clean_arr
void clean_arr(t_struct *st);

// parsing: extract_utils.c
char	*malloc_file_name(char **file, int len);
int		test_file_descriptor(int fd, char *name);
int		open_outfile(char *name, int append);
void	remove_redirection(char *input, int nb, char c);


//error.c
int		ms_error(char *txt, int	exit_level, t_struct *st);
void	ms_error_synthaxe(char c);

// ms_launch_cmd.c
int		launch_cmd(t_struct *st);

// echo: ms_echo.c
int		run_echo(void *st, void *cmd);
int		initialise_buf(t_struct *st);
void	bufferize_cmd(t_struct *st, t_cmd *arr, int arg, int i);
int		is_writable(t_struct *st, char c, char c_next);

// echo: ms_expand_variable_str
int		launch_bufferize_variable_str(t_struct *st, char *str, int pos_s);
void	bufferize_str(t_struct *st, char *str);

// env
int		ms_run_env(void *stt, void *cmd);
int		ms_run_export(void *stt, void *cmd);
int		ms_run_unset(void *stt, void *cmd);
void	ms_env(char **env);
int		ms_export(char *new_var, t_struct *st);
int		ms_unset(char *var_name, t_struct *st);
char	*ms_get_env(char **env, char *varname);
int		cd(void *stt, void *cmd);
int		pwd(void *stt, void *cmd);
void	free_env(t_struct *st);

// gnl
int		read_till_limiter(t_struct *st, int tr);
char	*get_strjoin(char *s1, char *s2);
int		get_extract_line(char **line, char *str, int stat_read);
int		get_next_line(int fd, char **line, char *limiter);
char	*gnl_strchr(const char *s, int c);
void	*gnl_memmove(void *dest, const void *src, size_t n);
size_t	get_lglen(const char *s);
char	*gnl_substr(char const *s, size_t len);
size_t	gnl_strlen(const char *s);
void	gnl_bzero(void *s, size_t n);
void	*gnl_calloc(size_t nmemb, size_t n);

#endif
