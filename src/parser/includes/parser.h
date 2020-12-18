#ifndef FT_PARSER_H
#define FT_PARSER_H

#ifndef FT_LIBFT_H
#include "libft.h"
# endif
#ifndef FT_ARRAY_LIST_H
# include "array_list.h"
#endif
#ifndef FT_GAME_H
# include "game.h" 
#endif

typedef struct s_parser{
        t_array_list lines;
        int             fd;
        struct s_game          *g_p;
        void (*get_lines)(struct s_parser *this);
        int (*get_fd)(char *filename);
        void  (*do_final)( struct s_parser *this);
        void (*free)(void *this);
}           t_parser;

t_bool check_empty_line(char *line);
void get_lines(t_parser *this);
int get_fd(char *filename);
void new_parser(t_parser *this, char *filename , t_game *g_p);
void  parser_do_final(t_parser *this);
void   free_parser(void *this);
void sprite_tex_parser(char *line);
void insert_wall(double s_x,double s_y,double e_x,double e_y);
void insert_player(double x,double y);
void push_n_walls(t_parser *this,char *l ,t_vector r_p);
t_bool check_res(t_array_list words);
void fill_res(t_game *g_p , char *line);
t_bool find_res(t_game *g_p,t_array_list array);
t_bool check_digit(char *line);
void put_error(t_game *g_p, char *message);
void  split_that(t_array_list *words , char *line , char ch)
#endif