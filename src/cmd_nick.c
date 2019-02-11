/*
** add_users.c for add_users in /home/valentin/rendu/PSU/PSU_2016_myirc
** 
** Made by Muratore Valentin
** Login   <valentin1.muratore@epitech.euvalentin1.muratore@epitech.eu>
** 
** Started on  Tue May 23 14:07:05 2017 Muratore Valentin
** Last update Sun Jun 11 22:09:28 2017 kevin
*/

#include	        "my_irc.h"

void			add_nick(t_server *server, t_user *user)
{
  if (server->users == NULL)
    server->users = malloc(sizeof(t_user) * 1);
  else
    server->users = realloc(server->users, sizeof(t_user) *
			    (server->len_users + 1));
  if (server->users == NULL)
    exit(84);
  server->users[server->len_users] = *user;
  server->len_users += 1;
}

void			modify_nick(t_server *server, t_user *user)
{
  int		        i;

  i = 0;

  while (i < server->len_users)
    {
      if (strcmp(server->users[i].nickname, user->nickname) == 0)
	{
	  server->users[i].nickname = user->cmd[1];
	  return;
	}
      i++;
    }
}

int			check_users_nickname(t_server *server, t_user *user)
{
  int			i;

  i = 0;

  if (server->users == NULL)
    return (0);
  while (i < server->len_users)
    {
      if (strcmp(server->users[i].nickname, user->nickname) == 0)
	return (-1);
      i++;
    }
  return (0);
}

void			cmd_nick(t_server *server, t_user *user)
{
  if (user->nickname == NULL)
    {
      if (user->cmd[1] != NULL)
	{
	  if (check_users_nickname(server, user) == -1)
	    my_putstr(user->fd, "433 This Nickname is already used");
	  else
	    {
	      user->nickname = strdup(user->cmd[1]);
	      add_nick(server, user);
	    }
	}
      else my_putstr(user->fd, "413 Give a nickname please");
    }
  else
    {
      modify_nick(server, user);
      my_putstr(1, "Nickname changed");
      user->nickname = strdup(user->cmd[1]);
    }
}
