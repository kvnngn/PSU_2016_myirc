/*
** client.c for client in /home/kevin/rendu/PSU_2016_myirc
** 
** Made by kevin
** Login   <kevin3.nguyen@epitech.eu>
** 
** Started on  Fri Jun  9 16:13:08 2017 kevin
** Last update Sun Jun 11 22:14:32 2017 kevin
*/

#include			"my_irc.h"

int				init_client(t_client *_client, char *addr, int port)
{
  if ((_client->id = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      printf("Socket error\n");
      return (-1);
    }
  else
    printf("Socket %d created\n", _client->id);
  _client->port = 0;
  _client->buffer[0] = 0;
  _client->config.sin_family = AF_INET;
  _client->config.sin_addr.s_addr = inet_addr(addr);
  _client->config.sin_port = htons(port);
  _client->cmd = NULL;
  _client->init = 1;
  return (0);
}

char				*get_ip(t_client *client)
{
  int				i;
  char				*ip;

  i = 0;
  if ((ip = malloc(sizeof(char) * (strlen(client->cmd[1]) + 1))) == NULL)
    exit(-1);
  while (client->cmd[1][i] != ':' && client->cmd[1][i] != '\0')
    {
      ip[i] = client->cmd[1][i];
      i++;
    }
  ip[i] = 0;
  return (ip);
}

int				get_port(t_client *client)
{
  int				i;
  int				j;
  char				*port;

  i = 0;
  j = 0;
  if ((port = malloc(sizeof(char) * (strlen(client->cmd[1]) + 1))) == NULL)
    exit(-1);
  while (client->cmd[1][i] != ':' && client->cmd[1][i] != '\0')
    i++;
  if (client->cmd[1][i] == 0)
    return (0);
  i++;
  while (client->cmd[1][i] != ':' && client->cmd[1][i] != '\0')
    {
      port[j] = client->cmd[1][i];
      j++;
      i++;
    }
  port[j] = 0;
  return (atoi(port));
}

void				loop(t_client *_client)
{
  char				*input;

  input = NULL;
  while (1)
    {
      input = get_next_line(1);
      my_putstr(_client->id, input);
      _client->cmd = my_str_to_wordtab(input);
      input = get_next_line(_client->id);
      if (input != NULL)
      	{
      	  my_putstr(1, input);
      	  free(input);
      	}
      handle_server(_client);
    }
  close(_client->id);
}

int				main()
{
  t_client			_client;

  init_client(&_client, "127.0.0.1", 4242);
  if (connect(_client.id, (struct sockaddr *)&_client.config,
	      sizeof(_client.config)) != 0)
    {
      my_putstr(1, "Connection to the server failed");
      return (-1);
    }
  loop(&_client);
}
