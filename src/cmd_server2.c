/*
** cmd_server2.c for cmd_server2 in /home/valentin/rendu/PSU/PSU_2016_myirc
** 
** Made by Muratore Valentin
** Login   <valentin1.muratore@epitech.euvalentin1.muratore@epitech.eu>
** 
** Started on  Sun Jun 11 17:47:37 2017 Muratore Valentin
** Last update Sun Jun 11 22:22:14 2017 kevin
*/

#include		"my_irc.h"

void			cmd_list(t_server *server, t_user *user)
{
  server = server;
  user = user;
  printf("in function LIST\n");
}

void			cmd_names(t_server *server, t_user *user)
{
  server = server;
  user = user;
  printf("in function NAMES\n");
}

void			cmd_send_file(t_server *server, t_user *user)
{
  server = server;
  user = user;
  printf("in function SEND_FILE\n");
}

void			cmd_accept_file(t_server *server, t_user *user)
{
  server = server;
  user = user;
  printf("in function ACCEPT_FILE\n");
}

int			check_cmd(t_server *server, t_user *user, t_pointeur *tab)
{
  int			j;

  j = 0;
  if (user->cmd != NULL)
    {
      while (j < 12)
	{
	  if (strcmp(user->cmd[0], tab[j].func) == 0)
	    {
	      tab[j].ptr(server, user);
	      return (0);
	    }
	  j = j + 1;
	}
    }
  my_putstr(user->socket, "Error: unknown command!");
  return (0);
}
