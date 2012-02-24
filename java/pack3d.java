public class  pack3d {

	
	public static class shape {
		
		int w;
		int h;
		int l;
		shape d;
		shape r;
		shape b;
	}

	private static int fitCount = 0;


	public static void main(String[] args) {

		shape bin = new shape();
		shape box = new shape();
		
		bin.w = Integer.parseInt(args[0].split(",")[0]);
		bin.h = Integer.parseInt(args[0].split(",")[1]);
		bin.l = Integer.parseInt(args[0].split(",")[2]);
	
		box.w = Integer.parseInt(args[1].split(",")[0]);
		box.h = Integer.parseInt(args[1].split(",")[1]);
		box.l = Integer.parseInt(args[1].split(",")[2]);		

		long start = System.currentTimeMillis();
		
		packIt(bin, box);

		long end = System.currentTimeMillis();
		long execTime = end - start;	
		System.out.println("found " + fitCount + " fits in " + execTime + " ms");
	}



	private static void packIt(shape bin, shape box) {


		//sort both bin and box
		if ( bin.w < bin.h) {

		        int tmpw = bin.w;
		        bin.w = bin.h;
		        bin.h = tmpw;
		}


		if ( box.w < box.h) {

		        int tmpw = box.w;
		        box.w = box.h;
		        box.h = tmpw;
		}


		if ( bin.h < bin.l ) {

                	int tmph = bin.h;
                	bin.h = bin.l;
                	bin.l = tmph;
        	}



        	if ( box.w < box.h) {

                	int tmpw = box.w;
                	box.w = box.h;
                	box.h = tmpw;
        	}


        	if ( box.w < box.l ) {

                	int tmpw = box.w;
                	box.w = box.l;
                	box.l = tmpw;

        	}

        	if ( box.h < box.l ) {

               		int tmph = box.h;
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

		int dW = bin.w;
		int dH = bin.h - box.h;
		int dL = bin.l;

		if ( dH == 0 )
		        bin.d = null;
		else {

			bin.d = new shape();

			bin.d.w = dW;
			bin.d.h = dH;
			bin.d.l = dL;
		}

		
		int rW = bin.w - box.w;
		int rH = box.h;
		int rL = bin.l;

		if ( rW == 0 )
		        bin.r = null;
		else {

			bin.r = new shape();
			
			bin.r.w = rW;
			bin.r.h = rH;
			bin.r.l = rL;
		}


		int bW = box.w;
                int bH = box.h;
                int bL = bin.l - box.l;

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
