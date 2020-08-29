# ifndef FREE_SURFACE_FUNC_H
#define FREE_SURFACE_FUNC_H

#include "ShengShen_head.h"

double free_surface_func(float **V,
                         float **Txx_now, float **Txz_now,float **Tzz_now,
					     struct PARAMETER *param);



#endif
