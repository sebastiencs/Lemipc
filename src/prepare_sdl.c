/*
** prepare_sdl.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 18:03:53 2015 chapui_s
** Last update Sun Mar  8 18:07:20 2015 chapui_s
*/

#ifdef SDL_OUTPUT

# include "lemipc.h"

void		prepare_sdl(t_info *info)
{
  if (SDL_Init(SDL_INIT_VIDEO))
  {
    fprintf(stderr, "Warning: Can't initialize SDL: %s\n", SDL_GetError());
  }
  if (!(info->screen = SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE)))
  {
    SDL_Quit();
  }
  if (!(info->player = SDL_CreateRGBSurface(SDL_HWSURFACE,
					    5, 5, 32, 0, 0, 0, 0)))
  {
    SDL_FreeSurface(info->screen);
    SDL_Quit();
  }
  SDL_WM_SetCaption("LemIPC !", (const char*)0);
  info->colors[0] = SDL_MapRGB(info->screen->format, 255, 0, 0);
  info->colors[1] = SDL_MapRGB(info->screen->format, 30, 144, 255);
  info->colors[2] = SDL_MapRGB(info->screen->format, 69, 139, 0);
  info->colors[3] = SDL_MapRGB(info->screen->format, 202, 255, 112);
  info->colors[4] = SDL_MapRGB(info->screen->format, 0, 0, 0);
  info->black = SDL_MapRGB(info->screen->format, 0, 0, 0);
}

#endif /* !SDL_OUTPUT */
