package crc642dc1cd4f88c133f3;


public class ContentActivity
	extends androidx.appcompat.app.AppCompatActivity
	implements
		mono.android.IGCUserPeer
{
/** @hide */
	public static final String __md_methods;
	static {
		__md_methods = 
			"n_onCreate:(Landroid/os/Bundle;)V:GetOnCreate_Landroid_os_Bundle_Handler\n" +
			"";
		mono.android.Runtime.register ("PeXPress.ContentActivity, PeXPress", ContentActivity.class, __md_methods);
	}


	public ContentActivity ()
	{
		super ();
		if (getClass () == ContentActivity.class)
			mono.android.TypeManager.Activate ("PeXPress.ContentActivity, PeXPress", "", this, new java.lang.Object[] {  });
	}


	public ContentActivity (int p0)
	{
		super (p0);
		if (getClass () == ContentActivity.class)
			mono.android.TypeManager.Activate ("PeXPress.ContentActivity, PeXPress", "System.Int32, mscorlib", this, new java.lang.Object[] { p0 });
	}


	public void onCreate (android.os.Bundle p0)
	{
		n_onCreate (p0);
	}

	private native void n_onCreate (android.os.Bundle p0);

	private java.util.ArrayList refList;
	public void monodroidAddReference (java.lang.Object obj)
	{
		if (refList == null)
			refList = new java.util.ArrayList ();
		refList.add (obj);
	}

	public void monodroidClearReferences ()
	{
		if (refList != null)
			refList.clear ();
	}
}
