/*
** server.c for  in /home/kevin/rendu/PSU_2016_myirc
** 
** Made by kevin
** Login   <kevin3.nguyen@epitech.eu>
** 
** Started on  Mon May 22 14:16:21 2017 kevin
** Last update Sun Jun 11 22:21:49 2017 kevin
*/

#include			"my_irc.h"

void			cmd_server(t_server *server, t_user *user)
{
  server->buf = get_next_line(server->socket);
  my_putstr(1, server->buf);
  if (server->buf == NULL)
    {
      my_putstr(1, "[-] ERROR get_next_line");
      exit(EXIT_FAILURE);
    }
  user->cmd = my_str_to_wordtab(server->buf);
  /* check_cmd(server, user, tab); */
}

int				handle_user(t_server *server, t_user *user, t_pointeur *tab)
{
  int				i;

  server->buf = get_next_line(user->fd);
  if (server->buf == NULL)
    {
      my_putstr(1, "[-] ERROR get_next_line");
      exit(EXIT_FAILURE);
    }
  user->cmd = my_str_to_wordtab(server->buf);
  if (user->cmd != NULL)
    {
      printf("User %d sent : ", user->fd);
      i = 0;
      while (user->cmd[i] != NULL)
	{
	  if (user->cmd[i + 1] == NULL)
	    printf("%s\n", user->cmd[i]);
	  else
	    printf("%s ", user->cmd[i]);
	  i++;
	}
    }
  check_cmd(server, user, tab);
  return (0);
}

void				execute_loop(t_server *server, t_pointeur *tab,
					     t_user user)
{
  while (user.fd < FD_SETSIZE)
    {
      if (FD_ISSET(user.fd, &server->read_fd_set))
	{
	  if (user.fd == server->socket)
	    {
	      user.socket = accept(server->socket,
				   (struct sockaddr *) &user.config,
				   &server->len);
	      if (user.socket < 0)
		{
		  my_putstr(1, "[-] ERROR accept");
		  exit(EXIT_FAILURE);
		}
	      printf("Server: connect from host %s, port %hd.\n",
		     inet_ntoa(user.config.sin_addr),
		     ntohs(user.config.sin_port));
	      FD_SET(user.socket, &server->active_fd_set);
	    }
	  else handle_user(server, &user, tab);
	}
      user.fd++;
    }
}

int				execute(t_server *server, t_pointeur *tab)
{
  t_user			user;

  while (1)
    {
      server->read_fd_set = server->active_fd_set;
      if (select (FD_SETSIZE, &server->read_fd_set, NULL, NULL, NULL) < 0)
	{
	  my_putstr(1, "[-] ERROR select");
	  exit(EXIT_FAILURE);
	}
      user.fd = 0;
      execute_loop(server, tab, user);
    }
}

int				main(int ac, char **av)
{
  t_server			server;
  t_pointeur			*tab;

  if (ac == 2 && atoi(av[1]) > 0)
    {
      init_server(&server, atoi(av[1]));
      if ((tab = malloc(sizeof(t_pointeur) * 13)) == NULL)
	return (-1);
      init_tab(tab);
      execute(&server, tab);
    }
  else my_putstr(1, "Usage : ./server port");
  return (0);
}
