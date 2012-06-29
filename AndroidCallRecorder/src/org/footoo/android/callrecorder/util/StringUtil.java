package org.footoo.android.callrecorder.util ;

public class StringUtil
{
	public static boolean compareString( String a , String b )
	{
		if( a == null || b == null )
			return false ;
		if( a.length() != b.length() )
			return false ;
		for( int i = 0 ; i < a.length() ; ++ i )
		{
			if( a.indexOf( i ) != b.indexOf( i ) )
			{
				return false ;
			}
		}
		return true ;
	}
	
}
