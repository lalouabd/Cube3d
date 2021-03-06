#include "Cube3d.h"
extern t_game *game;

/*** 
  @autor b0n3:1337

  this file contains texture function 

  TODO :
    function that create new sprite || wall texture 
    free functions

**/

t_texture  *new_texture(char *link)
{
    t_texture *tex;

    if (link != NULL)
    {
      tex =(t_texture *) malloc(sizeof(t_texture));
      if(tex != NULL)
      {
        tex->offset = 0;
        void *ptr = mlx_xpm_file_to_image(game->window.mlx,
        link, 
        &tex->width, &tex->height);
        tex->img.img_ptr = ptr; 
        if (tex->img.img_ptr == NULL)
          game->errors.push(&game->errors, ft_strdup("invalid texture bitch"), 
          sizeof(char *));
        tex->data = (int *) mlx_get_data_addr(tex->img.img_ptr , &(tex->img.bpp) 
          ,&tex->img.size_line , &(tex->img.endian));
          game->allocated_tex.push(&game->allocated_tex, tex, sizeof(t_texture));
         // printf("%s : heigth %d  : width : %d" , link, tex->height , tex->width);
      }
    
    }
    return tex;
}

t_sp_texture *get_sp_tex(int kind)
{
  t_sp_texture *tex;
   t_sp_texture *ntex;
  int i;
  
  tex = NULL;
  ntex = NULL;
  i = 0;
  while (i < game->allocated_sp_tex.index)
  {
    ntex = game->allocated_sp_tex.get(&game->allocated_sp_tex, i);
    if (ntex != NULL)
      if (ntex->kind == kind)
      {
        tex = ntex;
        break;
      }
    i++;
  }
  return tex;
}
t_sp_texture *new_sp_texture(char *link, int kind)
{
    t_sp_texture *tex;

    if (link != NULL)
    {
      tex =(t_sp_texture *) malloc(sizeof(t_sp_texture));
      if(tex != NULL)
      {
        tex->offset = 0;
        tex->img.img_ptr =  mlx_xpm_file_to_image(game->window.mlx,link, 
        &tex->width, &tex->height);
        tex->data =(int *) mlx_get_data_addr(tex->img.img_ptr , &tex->img.bpp 
          ,&tex->img.size_line , &tex->img.endian);
        tex->kind = kind;
      }
    }
    return tex;
}