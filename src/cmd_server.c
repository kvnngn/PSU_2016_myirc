/*
** cmd_server.c for cmd_server in /home/valentin/rendu/PSU/PSU_2016_myirc
** 
** Made by Muratore Valentin
** Login   <valentin1.muratore@epitech.euvalentin1.muratore@epitech.eu>
** 
** Started on  Sun Jun 11 17:46:55 2017 Muratore Valentin
** Last update Sun Jun 11 22:14:15 2017 kevin
*/

#include "my_irc.h"

void			cmd_quit(t_server *server, t_user *user)
{
  printf("User %d left the channel\n", user->fd);
  close(user->fd);
  FD_CLR(user->fd, &server->active_fd_set);
}

void			cmd_part(t_server *server, t_user *user)
{
  server = server;
  user = user;
  printf("in function PART\n");
}

void			cmd_users(t_server *server, t_user *user)
{
  int			i;

  i = 0;
  user = user;
  if (server->users != NULL)
    {
      while (i < server->len_users)
	{
	  my_putstr(1, server->users[i].nickname);
	  i++;
	}
    }
}

void			cmd_user(t_server *server, t_user *user)
{
  server = server;
  my_putstr(user->fd, "001 :Welcome to the Internet Relay Network !");
}

void			cmd_msg(t_server *server, t_user *user)
{
  server = server;
  user = user;
  printf("in function MSG\n");
}
