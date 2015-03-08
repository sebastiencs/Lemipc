/*
** can_i_fight.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 08:26:44 2015 chapui_s
** Last update Sun Mar  8 08:27:05 2015 chapui_s
*/

#include "lemipc.h"

static int	am_i_surrounded(t_info *info, int nb_attackers)
{
  int		x;
  int		id;

  x = ((info->x - 1) < 0) ? (0) : (info->x - 1);
  while (x < info->x + 1 && x < SIZE_X)
  {
    if (info->y + 1 < SIZE_Y)
      if ((id = get_battlefield(info, x, info->y + 1)) != 0
	  && id != info->team_number)
	nb_attackers += 1;
    if (info->y - 1 >= 0)
      if ((id = get_battlefield(info, x, info->y - 1)) != 0
	  && id != info->team_number)
	nb_attackers += 1;
    x += 1;
  }
  if (info->x > 0 && (id = get_battlefield(info, info->x - 1, info->y)) != 0
      && id != info->team_number)
    nb_attackers += 1;
  if (info->x < SIZE_X - 1
      && (id = get_battlefield(info, info->x + 1, info->y)) != 0
      && id != info->team_number)
    nb_attackers += 1;
  return ((nb_attackers >= 2) ? (1) : (0));
}

int		can_i_fight(t_info *info)
{
  if (info->i_am_alive && am_i_surrounded(info, 0))
  {
    info->i_am_alive = 0;
    printf("FUCK ! They killed me ! It wasn't my war !\n");
    set_battlefield(info, info->x, info->y, 0);
    return (0);
  }
  else if (info->i_am_alive)
  {
    printf("Still alive !\n");
    return (1);
  }
  return (0);
}
