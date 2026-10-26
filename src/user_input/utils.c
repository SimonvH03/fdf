#include "fdf.h"

void	precalc(t_fdf *fdf)
{
	fdf->cosin = (t_cosin){
		cos(fdf->speed * ROTATION_SPEED),
		sin(fdf->speed * ROTATION_SPEED)};
}
