public class  pack3d {

	
	public static class shape {
		
		float w;
		float h;
		float l;
		shape d;
		shape r;
		shape b;
	}

	private static int fitCount = 0;
	private static float tolKerf;

	public static void main(String[] args) {


		if ( args.length < 3 ) {
                        System.out.println("3 arguments required: bin size (eg. 5x5x5), box size (eg. 1x1x1) and tol+kerf (eg 1.25)");
                        System.exit(1);
                }


		shape bin = new shape();
		shape box = new shape();
		
		bin.w = Float.parseFloat(args[0].split("x")[0]);
		bin.h = Float.parseFloat(args[0].split("x")[1]);
		bin.l = Float.parseFloat(args[0].split("x")[2]);
	
		box.w = Float.parseFloat(args[1].split("x")[0]);
		box.h = Float.parseFloat(args[1].split("x")[1]);
		box.l = Float.parseFloat(args[1].split("x")[2]);		

		tolKerf = Float.parseFloat(args[2]);

		long start = System.currentTimeMillis();
		
		packIt(bin, box);

		long end = System.currentTimeMillis();
		long execTime = end - start;	
		System.out.println("found " + fitCount + " fits in " + execTime + " ms");
	}



	private static void packIt(shape bin, shape box) {


		//sort both bin and box
		if ( bin.w < bin.h) {

		        float tmpw = bin.w;
		        bin.w = bin.h;
		        bin.h = tmpw;
		}


		if ( box.w < box.h) {

		        float tmpw = box.w;
		        box.w = box.h;
		        box.h = tmpw;
		}


		if ( bin.h < bin.l ) {

                	float tmph = bin.h;
                	bin.h = bin.l;
                	bin.l = tmph;
        	}



        	if ( box.w < box.h) {

                	float tmpw = box.w;
                	box.w = box.h;
                	box.h = tmpw;
        	}


        	if ( box.w < box.l ) {

                	float tmpw = box.w;
                	box.w = box.l;
                	box.l = tmpw;

        	}

        	if ( box.h < box.l ) {

               		float tmph = box.h;
                	box.h = box.l;
        	        box.l = tmph;
	
	        }



		if(box.w <= bin.w && box.h <= bin.h && box.l <= bin.l ) {

		        fitCount++;

		        //if it fits split box and recurse
		        splitBin(bin, box);
		        if ( bin.d != null )
		                packIt(bin.d, box);
		        if( bin.r != null )
		                packIt(bin.r, box);
			if ( bin.b != null )
                        	packIt(bin.b, box);

		}

	
	}
	
	private static void splitBin(shape bin, shape box) {

		float dW = bin.w;
		float dH = bin.h - box.h - tolKerf;
		float dL = bin.l;

		if ( dH == 0 )
		        bin.d = null;
		else {

			bin.d = new shape();

			bin.d.w = dW;
			bin.d.h = dH;
			bin.d.l = dL;
		}

		
		float rW = bin.w - box.w - tolKerf;
		float rH = box.h;
		float rL = bin.l;

		if ( rW == 0 )
		        bin.r = null;
		else {

			bin.r = new shape();
			
			bin.r.w = rW;
			bin.r.h = rH;
			bin.r.l = rL;
		}


		float bW = box.w;
                float bH = box.h;
                float bL = bin.l - box.l - tolKerf;

                if ( bW == 0 )
                        bin.b = null;
                else {

                        bin.b = new shape();

                        bin.b.w = bW;
                        bin.b.h = bH;
                        bin.b.l = bL;
                }




	}


}
