/*
** get_args.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar  6 19:51:54 2015 chapui_s
** Last update Fri Mar  6 20:34:52 2015 chapui_s
*/

#include "lemipc.h"

static int	is_number(char *s)
{
  size_t	i;

  i = 0;
  while (s[i])
  {
    if (s[i] < '0' || s[i] > '9')
      return (0);
    i += 1;
  }
  return (1);
}

int		get_info(int argc, char **argv, t_info *info)
{
  int		i;

  i = 1;
  info->team_number = TEAM_NUMBER_DEFAULT;
  info->path = PATH_DEFAULT;
  while (i < argc)
  {
    if (is_number(argv[i]))
      info->team_number = atoi(argv[i]);
    else
      info->path = argv[i];
    i += 1;
  }
  if ((info->key = ftok(info->path, 0)) == -1)
  {
    fprintf(stderr, "ERROR: can't get the key: %s\n", strerror(errno));
    return (-1);
  }
  return (0);
}
