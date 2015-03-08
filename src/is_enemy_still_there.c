/*
** is_enemy_still_there.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 08:29:36 2015 chapui_s
** Last update Sun Mar  8 08:30:11 2015 chapui_s
*/

#include "lemipc.h"

int		is_enemy_still_there(t_info *info,
				     t_enemy *stupid_guy,
				     char *s)
{
  char		val;
  int		x;
  int		y;

  x = atoi(strtok(s, ":"));
  y = atoi(strtok(s, ":"));
  val = get_battlefield(info, x, y);
  if (val != 0 && val != info->team_number)
  {
    stupid_guy->x = x;
    stupid_guy->y = y;
    return (1);
  }
  else
  {
    return (0);
  }
}
