/*
 * Author: Spiros Delviniotis
 * File: Serial_heat2D.c
 * Project: Parallel Programming 
 */

#include <stdio.h>
#include <stdlib.h>

#define NXPROB      4                 /* x dimension of problem grid */
#define NYPROB      4                 /* y dimension of problem grid */
#define STEPS       10                /* number of time steps */

struct Parms { 
  float cx;
  float cy;
} parms = {0.1, 0.1};

int main (int argc, char *argv[])
{
	void inidat(),prbdat(), update();
	float  u[2][NXPROB][NYPROB];        /* array for grid */
	int start,end,ix,iy,iz,it;


	/* Initialize grid */
	printf("Grid size: X= %d  Y= %d  Time steps= %d\n",NXPROB,NYPROB,STEPS);
	inidat(NXPROB, NYPROB, u);
	
        start = 0;
	end = start + NYPROB - 2;
	
	/* Initialize everything - including the borders - to zero */
	for (iz=0; iz<2; iz++)
		for (ix=0; ix<NXPROB; ix++) 
			for (iy=0; iy<NYPROB; iy++) 
				u[iz][ix][iy] = 0.0;
	
	printf("Initialization finished!\n");	
	
        iz = 0;
	for (it = 1; it <= STEPS; it++)
	{
		update(start, end, NYPROB, &u[iz][0][0], &u[1-iz][0][0]);
		iz = 1 - iz;
	}
	
}


/**************************************************************************
 *  subroutine update
 ****************************************************************************/
void update(int start, int end, int ny, float *u1, float *u2)
{
   int ix, iy;
   for (ix = start; ix <= end; ix++) 
      for (iy = 1; iy <= ny-2; iy++) 
         *(u2+ix*ny+iy) = *(u1+ix*ny+iy)  + 
                          parms.cx * (*(u1+(ix+1)*ny+iy) +
                          *(u1+(ix-1)*ny+iy) - 
                          2.0 * *(u1+ix*ny+iy)) +
                          parms.cy * (*(u1+ix*ny+iy+1) +
                         *(u1+ix*ny+iy-1) - 
                          2.0 * *(u1+ix*ny+iy));
}

/*****************************************************************************
 *  subroutine inidat
 *****************************************************************************/
void inidat(int nx, int ny, float *u) {
	int ix, iy;

	for (ix = 0; ix <= nx - 1; ix++) {
		for (iy = 0; iy <= ny - 1; iy++) {
			*(u + ix * ny + iy) = (float) (ix * (nx - ix - 1) * iy * (ny - iy - 1) + 10);
		}
	}
}