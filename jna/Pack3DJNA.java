
import com.sun.jna.Library;
import com.sun.jna.Native;


interface NativePack3D extends Library {

	NativePack3D INSTANCE = (NativePack3D) Native.loadLibrary("pack3d", NativePack3D.class);
	int getCount(float binsize1, float binsize2, float binsize3, float boxsize1, float boxsize2, float boxsize3, float tk);
}

public class Pack3DJNA {


	public static void main( String[] args ) {
		NativePack3D lib = NativePack3D.INSTANCE;
		int res = lib.getCount(5,5,5,1,1,1.25f,0);

		System.out.println( res);
	}


}
