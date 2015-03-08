/*
** prepare_battle.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 08:25:20 2015 chapui_s
** Last update Sun Mar  8 08:31:33 2015 chapui_s
*/

#include "lemipc.h"

static void	place_this_spartiate(t_info *info)
{
  int		x;
  int		y;

  x = rand() % SIZE_X;
  y = rand() % SIZE_Y;
  while (get_battlefield(info, x, y) != 0)
  {
    x += 1;
    if (!(x % SIZE_X))
      y += 1;
  }
  info->x = x % SIZE_X;
  info->y = y % SIZE_Y;
  set_battlefield(info, x, y, info->team_number);
}

int		prepare_for_battle(t_info *info)
{
  if (get_map(info) == -1)
    return (-1);
  if (get_sem(info) == -1)
    return (-1);
  if (get_msg(info) == -1)
    return (-1);
  if (get_connected(info) > (int)SIZE_MAP / 2)
  {
    printf("Ouch.. They block the door :-O I can't go in !\n");
    printf("Let me go home ! *call his mother*\n");
    down_the_arms(info);
    return (-1);
  }
  set_connected(info, ONE_MORE);
  info->i_am_alive = 1;
  place_this_spartiate(info);
  if (info->is_first)
    printf("\033[H\033[J");
#ifdef DEBUG
  printf("Ready to fight ! x: %d y: %d Bring me wine !\n", info->x, info->y);
#else
  printf("Ready to fight ! Bring me wine and whores !\n");
#endif
  return (0);
}
