
#ifndef FT_PLAYER_H
#define FT_PLAYER_H

# include "array_list.h"

typedef struct s_player{
    t_vector    *pos;
    double       rotaion_angle;
    double       fov;
    double      rotation_speed;
    double      mov_speed;
    int         w_dir;
    int         t_dir;
    t_array_list collision;
    t_array_list wall_rays;
    t_array_list sprit_rays;

    void (*update)(struct s_player *this);
    void (*render)(struct s_player *this);
    void (*free)(void *item);
}       t_player;

void  new_player(t_player *this , t_vector *pos, char ch);
void  update_player(t_player *this);
void  render_player(t_player *this);
void  free_player(void *item);
#endif