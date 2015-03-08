/*
** print_battlefield_sdl.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 17:23:44 2015 chapui_s
** Last update Sun Mar  8 23:21:15 2015 chapui_s
*/

#ifdef SDL_OUTPUT

# include "lemipc.h"

int		clear_screen(t_info *info, SDL_Rect *pos)
{
  if (!info->screen)
    return (-1);
  pos->x = 0;
  pos->y = 0;
  SDL_FillRect(info->screen, NULL, info->black);
  SDL_BlitSurface(info->screen, NULL, info->screen, pos);
  return (0);
}

void		print_battlefield(t_info *info)
{
  SDL_Rect	pos;
  int		x;
  int		y;
  char		val;

  y = 0;
  if (clear_screen(info, &pos) == -1)
    return ;
  while (y < SIZE_Y)
  {
    x = 0;
    while (x < SIZE_X)
    {
      if ((val = info->map[y * SIZE_Y + x]))
      {
	pos.x = x * 5;
	pos.y = y * 5;
	SDL_FillRect(info->player, NULL, info->colors[val - 1]);
	SDL_BlitSurface(info->player, NULL, info->screen, &pos);
      }
      x += 1;
    }
    y += 1;
  }
  SDL_Flip(info->screen);
}

#endif /* !SDL_OUTPUT */
