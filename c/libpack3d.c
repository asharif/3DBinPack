#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"libpack3d.h"

int PACK3D_fitCount;


void PACK3D_splitBin(struct PACK3D_shape *bin, struct PACK3D_shape *box) {

        float dW = bin->w->size;
        float dH = bin->h->size - box->h->size - bin->h->tk;
	float dL = bin->l->size;

	if ( dH <= 0 )
                bin->d = NULL;
        else
	{
		struct PACK3D_shape *binD;
		binD = ( struct PACK3D_shape *) malloc(sizeof( struct PACK3D_shape ) );
		binD->w = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );
		binD->h = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );
		binD->l = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );

		binD->w->size = dW;
		binD->w->origSide = bin->w->origSide;	
		binD->w->tk = bin->w->tk;

		binD->h->size = dH;
		binD->h->origSide = bin->h->origSide;
		binD->h->tk = bin->h->tk;

		binD->l->size = dL;
		binD->l->origSide = bin->l->origSide;
		binD->l->tk = bin->l->tk;

		bin->d = binD;

	}


        float rW = bin->w->size - box->w->size - bin->w->tk;
        float rH = box->h->size;
	float rL = bin->l->size;

        if ( rW <= 0 )
                bin->r = NULL;
        else
	{

		struct PACK3D_shape *binR;
		binR = ( struct PACK3D_shape *) malloc( sizeof ( struct PACK3D_shape ) );

		binR->w = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );
		binR->h = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );
		binR->l = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );

		binR->w->size = rW;
		binR->w->origSide = bin->w->origSide;	
		binR->w->tk = bin->w->tk;

		binR->h->size = rH;
		binR->h->origSide = bin->h->origSide;
		binR->h->tk = bin->h->tk;

		binR->l->size = rL;
		binR->l->origSide = bin->l->origSide;
		binR->l->tk = bin->l->tk;

		bin->r = binR;

	
	}


	float bW = box->w->size;
        float bH = box->h->size;
        float bL = bin->l->size - box->l->size - bin->l->tk;

        if ( bL <= 0 )
                bin->b = NULL;
        else
        {

                struct PACK3D_shape *binB;
                binB = ( struct PACK3D_shape *) malloc( sizeof ( struct PACK3D_shape ) );


		binB->w = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );
		binB->h = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );
		binB->l = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );

		binB->w->size = bW;
		binB->w->origSide = bin->w->origSide;	
		binB->w->tk = bin->w->tk;

		binB->h->size = bH;
		binB->h->origSide = bin->h->origSide;
		binB->h->tk = bin->h->tk;

		binB->l->size = bL;
		binB->l->origSide = bin->l->origSide;
		binB->l->tk = bin->l->tk;

                bin->b = binB;
        }



}


void PACK3D_packIt( struct PACK3D_shape *bin, struct PACK3D_shape *box)
{
	//sort both bin and box
        if ( bin->w->size < bin->h->size ) 
	{
                struct PACK3D_side *tmpw = bin->w;
                bin->w = bin->h;
                bin->h = tmpw;
        }


        if ( bin->w->size < bin->l->size ) 
	{

                struct PACK3D_side *tmpw = bin->w;
                bin->w = bin->l;
                bin->l = tmpw;
        }

	if ( bin->h->size < bin->l->size )
	 {

                struct PACK3D_side *tmph = bin->h;
                bin->h = bin->l;
                bin->l = tmph;
        }



        if ( box->w->size < box->h->size ) 
	{

                struct PACK3D_side *tmpw = box->w;
                box->w = box->h;
                box->h = tmpw;
        }


        if ( box->w->size < box->l->size )
	 {

                struct PACK3D_side *tmpw = box->w;
                box->w = box->l;
                box->l = tmpw;

        }

        if ( box->h->size < box->l->size ) 
	{

                struct PACK3D_side *tmph = box->h;
                box->h = box->l;
                box->l = tmph;

        }


        if( box->w->size <= bin->w->size && box->h->size <= bin->h->size &&
	    box->l->size <= bin->l->size ) 
	{

                PACK3D_fitCount++;

                //if it fits split box and recurse
                PACK3D_splitBin( bin, box );
		
		if ( bin->d != NULL )
		{
                        PACK3D_packIt( bin->d, box );
			free ( bin->d->w );
			free ( bin->d->h );
			free ( bin->d->l );
                	free( bin->d );
		}

		if( bin->r != NULL )
                { 

		       PACK3D_packIt( bin->r, box );
		       free ( bin->r->w );
		       free ( bin->r->h );
		       free ( bin->r->l );
		       free ( bin->r );
	
		}
		if( bin->b != NULL )
		{

			PACK3D_packIt( bin->b, box );
			free ( bin->b->w );
		        free ( bin->b->h );
		        free ( bin->b->l );
        		free ( bin->b );
		}
	}


}


//this is what should be called at end of day!
int PACK3D_getCount(float binsize1, float binsize2, float binsize3, float boxsize1, float boxsize2, float boxsize3, 
		    float tkw, float tkh, float tkl)
{

	
	PACK3D_fitCount = 0;

	struct PACK3D_shape *bin;
        struct PACK3D_shape *box;
        bin = ( struct PACK3D_shape * ) malloc(sizeof( struct PACK3D_shape ));
        box = ( struct PACK3D_shape *) malloc(sizeof( struct PACK3D_shape ) );

	bin->w = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );
	bin->h = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );
	bin->l = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );
	
	bin->w->size = binsize1;
	bin->w->origSide = 'w';
	bin->w->tk = tkw;

	bin->h->size = binsize2;
	bin->h->origSide = 'h';
	bin->h->tk = tkh;

	bin->l->size = binsize3;
	bin->l->origSide = 'l';
	bin->l->tk = tkl;


        bin->d = NULL;
        bin->r = NULL;
        bin->b = NULL;

	box->w = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );
	box->h = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );
	box->l = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side) );
        box->w->size = boxsize1;
        box->h->size = boxsize2;
        box->l->size = boxsize3;

	PACK3D_packIt(bin, box);

	free ( bin->w );
	free ( bin->h );
	free ( bin->l );
	free ( bin );
	free ( box->w );
	free ( box->h );
	free ( box->l );
	free ( box );


	return PACK3D_fitCount;

}

