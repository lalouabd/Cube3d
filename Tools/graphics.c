#include "Cube3d.h"

t_window windo;
extern t_game *game;

void draw_rec(t_window wi ,t_vector pos , int size , int color)
{
    int x = pos.x ;
    int x2 = pos.x + (size );
    int y1 = pos.y ;
    int y2 = pos.y + (size );

while (y1 < y2)
  {
     int x1 = x;
     while ( x1 < x2)
    { 
         game->window.img->put_pixel(game->window ,  x1, y1 ,color);
       x1++;
   }
  y1++;
  }
}

void	circle(t_vector a, int radius, int color)
{
	int		col;
	float	angle;
	float	step;

	col = 0;
	angle =  0;
	step = (M_PI / 180);
	while (angle <= (2 * M_PI))
	{
    
		ft_line(a.x, a.y, radius , angle, color);
		angle += step;
		col++;
	}
}

void rec(int  x ,int  y, int  sizex ,int sizey, int color)
{
  int x2 = x + sizex;
  int y2 = y+ sizey;
  int vx =  x;
  while (y < y2)
  {
    vx = x;
      while (vx < x2)
        {
          game->window.img->put_pixel(game->window ,  vx, y ,color);
          vx++;
        }
        y += 1;
  }

}

void	line(int x0, int y0, int x1, int y1, int color)
{
	int		dx;
	int		dy;
	float		steps;
	float	xinc;
	float	yinc;
	int		i;

	dx = x1 - x0;
	dy = y1 - y0;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 // steps = fmax(dx, dy);
  xinc = dx / (float)steps;
	yinc = dy / (float)steps;
	i = -1;
	while (++i <= steps)
	{
    image_put_pixel(game->window, x0, y0, color);
		x0 += xinc;
		y0 += yinc;
	}
}

// void  draw_line(t_window wi ,t_vector *pos , t_vector *dir , int color)
// {
//   windo = wi;
  
//   line(pos->x, pos->y , dir->x, dir->y,color);
// // int dx =  abs (dir->x - pos->x), sx = pos->x < dir->x ? 1 : -1;
// //   int dy = -abs (dir->y - pos->y), sy = pos->y < dir->y ? 1 : -1; 
// //   int err = dx + dy, e2; /* error value e_xy */
// //  int x0 = pos->x;
// //  int y0 = pos->y;
// //   for (;;){  /* loop */
// //     mlx_pixel_put(wi.mlx , wi.win, (int) x0 ,(int) y0, color);
// //     if (x0 == dir->x && y0 == dir->y) break;
// //     e2 = 2 * err;
// //     if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
// //     if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
// //   }
//   //    if (pos->x < dir->x)
//   //       ft_swap( (void **)&pos,(void **) &dir);    
//   //    int m_new = 2 * (dir->y - pos->y); 
//   //    int slope_error_new = m_new - (dir->x - pos->x); 
//   //    int x = pos->x;
//   //    int y = pos->y;make 

//   //   while ( x <= dir->x) 
//   //   { 
//   //        mlx_pixel_put(wi.mlx , wi.win, (int) x ,(int) y, color);
//   //     slope_error_new += m_new; 
//   //      if (slope_error_new >= 0) 
//   //      { 
//   //         y++; 
//   //         slope_error_new  -= 2 * (dir->x - pos->x); 
//   //      } 
//   //      x++;
//   //  } 
//   //  ft_swap( (void **)&pos,(void **) &dir);
// }
void    ft_line(float x, float y, int size ,float angle, int color)
{
    int r = 0;
    float or_x = x;
    float or_y = y;
    while (r < size)
    {
        x = or_x + (r * cos(angle));
        y = or_y + (r * sin(angle));
        game->window.img->put_pixel(game->window , (int) x, (int)y ,color);
        r++;
    }
}

void    init_image(t_image *this,t_window win)
{
  if(this != NULL)
  {
    this->img_ptr = mlx_new_image(win.mlx, game->width, game->heigth);
    this->img_data = mlx_get_data_addr(this->img_ptr, &this->bpp, &this->size_line, &this->endian);
    this->put_pixel = &image_put_pixel;
    this->clear = &clear_screen;
    this->show = &show_image;

  }
}
int rgb_to_int(int r, int g, int b)
{
int c = r;
  c = (c << 8) | g;
  c = (c << 8) | b;
  return c;
}

int		shadow(int color, double distance)
{
	int		r;
	int		g;
	int		b;
	float	fact;

	fact = 100 / distance;
	b = (color & 0xff) * fact;
	b = b > (color & 0xff) ? (color & 0xff) : b;
	color = color >> 8;
	g = (color & 0xff) * fact;
	g = g > (color & 0xff) ? (color & 0xff) : g;
	color = color >> 8;
	r = (color & 0xff) * fact;
	r = r > (color & 0xff) ? (color & 0xff) : r;
	return (rgb_to_int(r, g, b));
}

 
void image_put_pixel(t_window v , int x, int y, int color)
{
  int i;

  if (x < 0 || y < 0  || x > game->width || y > game->heigth)
      return;
  i = x * v.img->bpp / 8 + y * v.img->size_line;
  v.img->img_data[i] = color & 0xFF; // Blue
  v.img->img_data[i + 1] = (color & 0xFF00) >> 8; // Green
  v.img->img_data[i + 2] = (color & 0xFF0000) >> 16; 

}

void clear_screen( t_window v)
{
  int x = 0;
  int y = 0;
 //mlx_destroy_image(v.mlx, v.img->img_ptr);
 while (y < game->heigth)
{  
    x =0;
  while (x < game->width)
  {
    v.img->put_pixel(v, x , y , 0);
    x++;
  }
  y++;
}
    v.img->show(v);
}

void show_image(t_window v)
{
  mlx_put_image_to_window(v.mlx, v.win, v.img->img_ptr,0,0);
}