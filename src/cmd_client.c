/*
** cmd_client.c for cmd_client in /home/valentin/rendu/PSU/PSU_2016_myirc
** 
** Made by Muratore Valentin
** Login   <valentin1.muratore@epitech.euvalentin1.muratore@epitech.eu>
** 
** Started on  Sun Jun 11 17:43:11 2017 Muratore Valentin
** Last update Sun Jun 11 22:13:05 2017 kevin
*/

#include "my_irc.h"

int				handle_server(t_client *client)
{
  if (client->cmd != NULL)
    {
      if (strcmp(client->cmd[0], "SERVER") == 0)
	{
	  if (client->cmd[1] != NULL)
	    {
	      if (init_client(client, get_ip(client), get_port(client)) == -1)
		exit (-1);
	      if (connect(client->id, (struct sockaddr *)&client->config,
			  sizeof(client->config)) != 0)
		{
		  my_putstr(1, "Connection to the server failed");
		  return (-1);
		}
	      else
		{
		  my_putstr(client->id, "USER kevin hello test foo");
		  my_putstr(client->id, "NICK kevin");
		}
	      return (1);
	    }
	}
      else my_putstr(1, "Please first use command SERVER");
    }
  return (0);
}
