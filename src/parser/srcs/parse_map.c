#include "cub3d.h"

extern t_game *game;

void    get_walls(t_parser *this)
{
    t_vector real_pos;
    char *l;

    new_vector(&real_pos, 0 , 0);
    while (real_pos.y < this->lines.index)
    {
        real_pos.x = 0;
        l = (char *) this->lines.get(&this->lines , (int) real_pos.y);
           push_n_walls(this, l, real_pos);
           push_s_walls(this, l ,real_pos);
            real_pos.y += 1.0;
    }
   real_pos.x = 0;
   real_pos.y = 0;
   while (real_pos.x < game->bi)
   {
       push_e_walls(real_pos);
       if(real_pos.x > 0)
        push_w_walls(real_pos);
       real_pos.x += 1;
   }
}


void  create_map_p(t_parser *this)
{
    int nb_lines = 0;
    char *line;
    int len;

    game = this->g;  
    game->hvalue =64;
    game->wvalue = 64;
    game->bi = 0;
    while (nb_lines < this->lines.index)
    {
      line = this->lines.get(&(this->lines),nb_lines);
        len = ft_strlen(line);
        if(len > game->bi)
          game->bi = len;
      nb_lines++;
    }
    get_walls(this);
    get_sprites(this);
    
}



void parse_map(t_parser *this)
{
  t_token *token;
  t_array_list map;
  token = get_token_by_key(this ,"MAP");
  if(token == NULL)
    put_error(this->g, ft_strdup("no map"));
  else
  {
    this->lines.arr = token->values.arr;
    this->lines.index = token->values.index;
    create_map_p(this);
    
  }
}