/*
** my_irc.h for my_irc in /home/kevin/rendu/PSU_2016_myirc/include
** 
** Made by kevin
** Login   <kevin3.nguyen@epitech.eu>
** 
** Started on  Tue May  9 15:13:53 2017 kevin
** Last update Sun Jun 11 22:12:37 2017 kevin
*/

#ifndef MY_IRC_H_
# define MY_IRC_H_

#include				<sys/select.h>
#include				<sys/types.h>
#include				<arpa/inet.h>
#include				<stdio.h>
#include				<stdlib.h>
#include				<unistd.h>
#include				<sys/socket.h>
#include				<string.h>
#include				<sys/types.h>
#include				<signal.h>
#include				<libgen.h>
#include				<dirent.h>
#include				<errno.h>
#include				<sys/stat.h>
#include				<fcntl.h>

typedef struct				s_transfert
{
  int					socket_id;
  int					client_id;
  int					port;
  char					*ip;
  unsigned int			        len;
  int					status;
  struct sockaddr_in			client_config;
  struct sockaddr_in			config;
}					t_transfert;

typedef struct				s_user
{
  int					socket;
  unsigned int			        len;
  int				        port;
  char				        *ip;
  char					*buf;
  char					*filename;
  char					*nickname;
  int					status;
  char					**cmd;
  struct sockaddr_in			config;
  int					fd;
}					t_user;

typedef struct				s_channel
{
  int					socket;
  unsigned int			        len;
  int				        port;
  char					*buf;
  char					*filename;
  char					*name;
  int					status;
  char					**cmd;
  struct sockaddr_in			config;
  int					fd;
}					t_channel;

typedef struct				s_server
{
  int					socket;
  unsigned int			        len;
  int				        port;
  char					*server_ip;
  char					*buf;
  int					status;
  struct sockaddr_in			config;
  fd_set				active_fd_set;
  fd_set				read_fd_set;
  t_user				*users;
  int					len_users;
  t_channel				*channels;
  t_transfert				data;
}					t_server;

typedef struct				t_pointeur
{
  char					*func;
  void					(*ptr)(t_server *server, t_user *user);
}				        t_pointeur;

typedef struct                          s_client
{
  int					id;
  char					buffer[100];
  int					port;
  char					*buf;
  char					*response;
  char					**cmd;
  t_transfert			        data;
  struct sockaddr_in			config;
  int					init;
}					t_client;

void					my_putstr(int fd, char *str);
char					*my_itoa(int nb);
char					**my_str_to_wordtab(char *str);
char					*my_realloc(char *old, int size);
char					*get_next_line(const int fd);
void					add_nick(t_server *server, t_user *user);
void					modify_nick(t_server *server, t_user *user);
void					cmd_nick(t_server *server, t_user *user);
int					handle_server(t_client *client);
void					cmd_quit(t_server *server, t_user *user);
void					cmd_part(t_server *server, t_user *user);
void					cmd_users(t_server *server, t_user *user);
void					cmd_user(t_server *server, t_user *user);
void					cmd_msg(t_server *server, t_user *user);
void					cmd_list(t_server *server, t_user *user);
void					cmd_names(t_server *server, t_user *user);
void					cmd_send_file(t_server *server, t_user *user);
void					cmd_accept_file(t_server *server, t_user *user);
int					check_cmd(t_server *server, t_user *user,
						  t_pointeur *tab);
int					init_user(t_user *user);
int					init_server(t_server *server, int port);
void					init_tab(t_pointeur *tab);
void					cmd_server(t_server *server, t_user *user);
int					init_client(t_client *client, char *addr, int port);
char					*get_ip(t_client *client);
int					get_port(t_client *client);

#endif /* !MY_IRC_H_ */
