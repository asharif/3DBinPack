class Pack3DJNI {

	private native int getCount(float binsize1, float binsize2, float binsize3, float boxsize1, float boxsize2, float boxsize3);
	

	public static void main( String[] args ) {
		
		System.loadLibrary("pack3d");
		System.out.println(new Pack3DJNI().getCount(5,5,5,1,1,1));

	} 



}
