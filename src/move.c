/*
** move.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 05:31:00 2015 chapui_s
** Last update Sun Mar  8 07:01:51 2015 chapui_s
*/

#include "lemipc.h"

static int	is_busy(t_info *info, int x, int y)
{
  if (x < 0 || x >= SIZE_X || y < 0 || y >= SIZE_Y)
    return (1);
  return ((info->map[(y * SIZE_Y + x) % SIZE_MAP] != 0) ? (1) : (0));
}

void		move_random(t_info *info, int *x, int *y)
{
  int		x_old;
  int		y_old;

  x_old = *x;
  y_old = *y;
  if (is_busy(info, *x - 1, *y) == 0)
  {
    *x -= 1;
  }
  else if (is_busy(info, *x + 1, *y) == 0)
  {
    *x += 1;
  }
  else if (is_busy(info, *x, *y - 1) == 0)
  {
    *y -= 1;
  }
  else if (is_busy(info, *x, *y + 1) == 0)
  {
    *y += 1;
  }
  info->map[(y_old * SIZE_Y + x_old) % SIZE_MAP] = 0;
  info->map[(*y * SIZE_Y + *x) % SIZE_MAP] = info->team_number;
  printf("Moving to %d:%d\n", *x, *y);
}

static void	move_y(t_info *info, int *x, int *y, t_enemy *asshole)
{
  if (*y > asshole->y && is_busy(info, *x, *y - 1) == 0)
  {
    *y -= 1;
  }
  else if (*y < asshole->y && is_busy(info, *x, *y + 1) == 0)
  {
    *y += 1;
  }
  else
  {
    if (*x > asshole->x && is_busy(info, *x - 1, *y) == 0)
    {
      *x -= 1;
    }
    else if (*x < asshole->x && is_busy(info, *x + 1, *y) == 0)
    {
      *x += 1;
    }
  }
}

static void	move_x(t_info *info, int *x, int *y, t_enemy *asshole)
{
  if (*x > asshole->x && is_busy(info, *x - 1, *y) == 0)
  {
    *x -= 1;
  }
  else if (*x < asshole->x && is_busy(info, *x + 1, *y) == 0)
  {
    *x += 1;
  }
  else
  {
    move_y(info, x, y, asshole);
  }
}

void		move(t_info *info, int *x, int *y, t_enemy *asshole)
{
  int		x_old;
  int		y_old;

  x_old = *x;
  y_old = *y;
  if (ABS(*x - asshole->x) > ABS(*y - asshole->y))
  {
    move_x(info, x, y, asshole);
  }
  else
  {
    move_y(info, x, y, asshole);
  }
  if (x_old != *x || y_old != *y)
  {
    info->map[(y_old * SIZE_Y + x_old) % SIZE_MAP] = 0;
    info->map[(*y * SIZE_Y + *x) % SIZE_MAP] = info->team_number;
    printf("Moving to %d:%d\n", *x, *y);
  }
  else
  {
    printf("I can't move ! %d:%d *Warrior is scratching his ass*\n", *x, *y);
  }
}
