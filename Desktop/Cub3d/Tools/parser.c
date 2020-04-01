#include  "Cube3d.h"

t_game *game;

void new_parser(t_parser *this, char *filename, t_game *g_p)
{
    new_array_list(&(this->lines), 7, sizeof(char *));
    this->get_lines = &get_lines;
    this->get_fd = &get_fd;
    this->do_final = &parser_do_final;
    this->free = &free_parser;
    this->g_p = g_p;
    this->fd = this->get_fd(filename);
}

void get_lines(t_parser *this)
{
    char *line;
    int result;

    if (this->fd > -1)
    {
        while ((result = get_next_line(this->fd, &line)) > 0)
        {
            if (this->lines.push(&(this->lines),(void *) ft_strdup(line), sizeof(line)) != TRUE) 
                this->lines.free(&(this->lines), &free);
            free(line);
        }
        if (this->lines.push(&(this->lines),(void *) ft_strdup(line), sizeof(line)) != TRUE) 
            this->lines.free(&(this->lines), &free);
        free(line);
    }
    close(this->fd);
}

int get_fd(char *filename)
{
    int fd = -1;
    if (filename != NULL)
         fd = open(filename , O_RDONLY);
    return fd;
}


void   free_parser(void *this)
{

}

void fill_res(t_game *g_p , char **aftersplit)
{
    int h;
    int w;

    
    if(aftersplit != NULL)
    {
        if(aftersplit[1] != NULL)
        {
            w = ft_atoi_p(&aftersplit[1]);
            h = ft_atoi_p(&(aftersplit[1]));
             g_p->width = (w > 0 && w <= 1000) ? w : 1000;
             g_p->heigth = (h > 0 &&  h <= 600) ? h : 600;
        }
        else
        {
            g_p->width = 1000;
            g_p->heigth = 600;
        }
    }
    else
    {
       g_p->width = 1000;
       g_p->heigth = 600;
    }

}
void set_no_tex(t_game *g_p , char **aftersplit)
{

}
void set_so_tex(t_game *g_p , char **aftersplit)
{

}
void set_we_tex(t_game *g_p , char **aftersplit)
{

}
void set_ea_tex(t_game *g_p , char **aftersplit)
{

}

void set_colors(t_game *g_p , char **aftersplit, char kind)
{

}

void parse_line(t_game *g_p, char *line)
{
    char **aftersplit;
    int i;

    i = 0;
    aftersplit = NULL;
    aftersplit = ft_split(line , ' ');
    if (aftersplit!= NULL)
    {
        //if (ft_memcmp((const void *)aftersplit[0], (const void *)"R", 1) ==0)
        if(line[0] == 'R')
            fill_res(g_p , aftersplit);
        // if (ft_memcmp((const void *)aftersplit[0], (const void *)"NO", 2) == 0)
        //     set_no_tex(g_p , aftersplit);
        // if (ft_memcmp((const void *)aftersplit[0], (const void *)"SO", 2) == 0)
        //     set_so_tex(g_p , aftersplit);
        // if (ft_memcmp((const void *)aftersplit[0], (const void *)"WE", 2) == 0)
        //     set_we_tex(g_p , aftersplit);
        // if (ft_memcmp((const void *)aftersplit[0], (const void *)"EA", 2) == 0 )
        //     set_ea_tex(g_p , aftersplit);
        // if (ft_memcmp((const void *)aftersplit[0], (const void *)"S", 1))
        //     set_colors(g_p , aftersplit, 'S');
        // if (ft_memcmp((const void *)aftersplit[0], (const void *)"F", 1))
        //     set_colors(g_p , aftersplit, 'f');
        // if (ft_memcmp((const void *)aftersplit[0], (const void *)"C", 1))
        //     set_colors(g_p , aftersplit, 'c');
    }
   // while (aftersplit[i])
      //  free(aftersplit[i++]);
   // free(aftersplit);
}

t_bool check_mapline(char *line)
{
    int i;

    i = 0;
    if (line[i] == '\0')
        return FALSE;
    while ( line [i]  != '\0')
    {
        if (line[i] != ' ' && line[i] != '1')
            return FALSE;
        i++;
    }
    return (TRUE);
}

void get_w(void *item)
{
    char *l;
    int i;
    double wsize;

    l = (char *) item;
//     if(ft_strlen(l ) <= 0)
//         return;
//     wsize = (double ) game->width / (double) (ft_strlen(l) + 1);
//      if (wsize > game->wvalue)
//       game->wvalue = wsize;
//
    game->wvalue = 22;
 }

void push_wall(t_parser *this, t_vector r_p)
{
    t_array_list *lines;
    char *up_l;
    char *do_l;
    char *l;
    int l_size;
    int up_size;
    int do_size;

    lines = &(this->lines);
    l = lines->get(lines , r_p.y);
    up_l = lines->get(lines, r_p.y -1);
    do_l = lines->get(lines, r_p.y + 1);
    if (l != NULL)
    {
        l_size = ft_strlen(l);
        if (r_p.x > 0)
        {
            if(l[(int )r_p.x -1] != '1' && l[(int )r_p.x -1] != ' ')
                game->walls.push(&(game->walls),new_wall(new_vector_pointer(game->wvalue * (r_p.x ), game->hvalue * (r_p.y )),new_vector_pointer(game->wvalue * (r_p.x ) , game->hvalue * (r_p.y  + 1))), sizeof(t_wall *));
        }
        if (r_p.x < l_size)
        {
            if(l[(int )r_p.x +1] != '1' && l[(int )r_p.x +1] != ' ')
                game->walls.push(&(game->walls),new_wall(new_vector_pointer(game->wvalue * (r_p.x  + 1), game->hvalue * (r_p.y )),new_vector_pointer(game->wvalue * (r_p.x + 1), game->hvalue * (r_p.y  + 1))), sizeof(t_wall *));
        }
        if (up_l != NULL)
        {
            up_size = ft_strlen ( up_l);
            if (r_p.x < up_size)
        {
            if(up_l[(int )r_p.x ]!= '1' && up_l[(int )r_p.x ] != ' ')
                game->walls.push(&(game->walls),new_wall(new_vector_pointer(game->wvalue * (r_p.x), game->hvalue * (r_p.y )),new_vector_pointer(game->wvalue * (r_p.x + 1), game->hvalue * (r_p.y  ))), sizeof(t_wall *));
        }
        }
        if (do_l != NULL)
        {
            do_size = ft_strlen ( do_l);
            if (r_p.x < do_size)
            {
                if(do_l[(int )r_p.x ] != '1' && do_l[(int )r_p.x ] != ' ')
                    game->walls.push(&(game->walls),new_wall(new_vector_pointer(game->wvalue * (r_p.x), game->hvalue * (r_p.y + 1)),new_vector_pointer(game->wvalue * (r_p.x + 1), game->hvalue * (r_p.y + 1 ))), sizeof(t_wall *));
            }
        }
    }
}

void    get_walls(t_parser *this)
{
    t_vector real_pos;
    char *l;
    new_vector(&real_pos, 0 , 0);
    while (real_pos.y < this->lines.index)
    {
        real_pos.x = 0;
        l = (char *) this->lines.get(&this->lines , (int) real_pos.y);
            while (l[(int)real_pos.x] != '\0')
            {
                if (l[(int)real_pos.x] == '1')
                     push_wall(this, real_pos);
                if(l[(int)real_pos.x] == 'N' || l[(int)real_pos.x] == 'S' || l[(int)real_pos.x] == 'E' || l[(int)real_pos.x] == 'W')
                {
                 game =   this->g_p;
                  new_player(&(game->player), new_vector_pointer(real_pos.x *game->wvalue + (0.5 * game->wvalue ), real_pos.y * game->hvalue + (0.5 *game->hvalue)) ,l[(int)real_pos.x]);
                }
                   // if (l[(int)real_pos.x] == 's')
                 //    push_door(this, real_pos);
                real_pos.x += 1;
            }
            real_pos.y += 1.0;
    }
}

t_bool create_map(t_parser *this)
{
    int nb_lines = 0;

    while ( this->lines.get(&(this->lines), nb_lines))
    {
        if (((char *)this->lines.get(&(this->lines), nb_lines))[0] == '\0')
                break;
            nb_lines++;
    }
    game = this->g_p;
    //game->hvalue = game->heigth /(nb_lines + 1);
    game->hvalue = 22;
    this->lines.foreach(&(this->lines),&get_w);
    get_walls(this);
    //get_sprites(this);
    //get_doors(this);
}

void   parser_do_final(t_parser *this)
{
    char *line;
    this->get_lines(this);
    if (this->lines.index > 0)
    {
        while (!check_mapline(this->lines.get(&(this->lines),0)))
        {
            line = this->lines.pull(&(this->lines));
            if ( line == NULL)
            {
                this->g_p->errors.push(&(this->g_p->errors),ft_strdup("invalid file : "), sizeof(char *));
                return;
            }
            if (line[0] != '\0')
                parse_line(this->g_p, line);
          //  free(line);
        }
        if (!create_map(this))
        {
            //this->g_p->errors.push(&(this->g_p->errors),ft_strdup("valid file"),sizeof(char *));
            return;
        }
    }
     this->g_p->errors.push(&(this->g_p->errors),ft_strdup("invalid file : "), sizeof(char *));
}