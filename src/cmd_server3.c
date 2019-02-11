/*
** cmd_server3.c for cmd_server3 in /home/valentin/rendu/PSU/PSU_2016_myirc
** 
** Made by Muratore Valentin
** Login   <valentin1.muratore@epitech.euvalentin1.muratore@epitech.eu>
** 
** Started on  Sun Jun 11 17:48:17 2017 Muratore Valentin
** Last update Sun Jun 11 22:22:42 2017 kevin
*/

#include "my_irc.h"

int				init_user(t_user *user)
{
  user->nickname = NULL;
  return (0);
}

int				init_server(t_server *server, int port)
{
  server->port = port;
  server->socket = socket(AF_INET, SOCK_STREAM, 0);
  server->config.sin_family = AF_INET;
  server->config.sin_addr.s_addr = htonl(INADDR_ANY);
  server->config.sin_port = htons(port);
  server->len = sizeof(struct sockaddr);
  server->len_users = 0;
  server->users = NULL;
  server->channels = NULL;
  FD_ZERO (&server->active_fd_set);
  FD_SET (server->socket, &server->active_fd_set);
  if (bind(server->socket, (struct sockaddr *)&server->config,
	   sizeof(struct sockaddr_in)) < 0)
    {
      my_putstr(1, "[-] ERROR bind");
      exit (EXIT_FAILURE);
    }
  if (listen (server->socket, 1) < 0)
    {
      my_putstr(1, "[-] ERROR listen");
      exit (EXIT_FAILURE);
    }
  my_putstr(1, "[+] Initialisation serveur OK.");
  return (0);
}

void				cmd_join(t_server *server, t_user *user)
{
  server = server;
  user = user;
  printf("in function LIST\n");
}

void				init_tab(t_pointeur *tab)
{
  tab[0].func = "NICK";
  tab[0].ptr = &cmd_nick;
  tab[1].func = "QUIT";
  tab[1].ptr = &cmd_quit;
  tab[2].func = "PART";
  tab[2].ptr = &cmd_part;
  tab[3].func = "USERS";
  tab[3].ptr = &cmd_users;
  tab[4].func = "MSG";
  tab[4].ptr = &cmd_msg;
  tab[5].func = "LIST";
  tab[5].ptr = &cmd_list;
  tab[6].func = "NAMES";
  tab[6].ptr = &cmd_names;
  tab[7].func = "SEND_FILE";
  tab[7].ptr = &cmd_send_file;
  tab[8].func = "ACCEPT_FILE";
  tab[8].ptr = &cmd_accept_file;
  tab[9].func = "SERVER";
  tab[9].ptr = &cmd_server;
  tab[10].func = "USER";
  tab[10].ptr = &cmd_user;
  tab[11].func = "JOIN";
  tab[11].ptr = &cmd_join;
}
