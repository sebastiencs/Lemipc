/*
** move_random.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 07:41:56 2015 chapui_s
** Last update Sun Mar  8 23:12:07 2015 chapui_s
*/

#include "lemipc.h"

static int	move_left(t_info *info, int *x, int *y)
{
  if (is_busy(info, *x - 1, *y) == 0)
  {
    *x -= 1;
    return (1);
  }
  return (0);
}

static int	move_right(t_info *info, int *x, int *y)
{
  if (is_busy(info, *x + 1, *y) == 0)
  {
    *x += 1;
    return (1);
  }
  return (0);
}

static int	move_down(t_info *info, int *x, int *y)
{
  if (is_busy(info, *x, *y - 1) == 0)
  {
    *y -= 1;
    return (1);
  }
  return (0);
}

static int	move_up(t_info *info, int *x, int *y)
{
  if (is_busy(info, *x, *y + 1) == 0)
  {
    *y += 1;
    return (1);
  }
  return (0);
}

t_func_rand tab_func [] =
{
  { 0, move_left },
  { 1, move_right },
  { 2, move_down },
  { 3, move_up },
};

void		move_random(t_info *info, int *x, int *y)
{
  int		x_old;
  int		y_old;
  int		i;

  x_old = *x;
  y_old = *y;
  i = rand() % 4;
  while (!(tab_func[i].func(info, x, y)))
    i = rand() % 4;
  set_battlefield(info, x_old, y_old, 0);
  set_battlefield(info, *x, *y, info->team_number);
  printf("Moving to %d:%d\n", *x, *y);
}
