package org.footoo.android.callrecorder.activity ;

import java.io.BufferedReader ;
import java.io.BufferedWriter ;
import java.io.File ;
import java.io.FileOutputStream ;
import java.io.IOException ;
import java.io.InputStream ;
import java.io.InputStreamReader ;
import java.io.OutputStreamWriter ;
import java.io.PrintWriter ;

import org.footoo.android.callrecorder.R ;
import org.footoo.android.callrecorder.service.RecordService ;

import android.app.Activity ;
import android.content.Context ;
import android.content.Intent ;
import android.content.SharedPreferences ;
import android.content.res.AssetManager ;
import android.os.Bundle ;
import android.util.Log ;
import android.view.View ;
import android.view.View.OnClickListener ;
import android.widget.Button ;

public class AndroidCallRecorderActivity extends Activity
{
	private static final String PREFERENCE = "RECORD_PREFERENCE" ;
	private static final String INSTALLED = "INSTALLED" ;
	SharedPreferences preferences = null ;
	SharedPreferences.Editor editor = null ;
	boolean installed = false ;
	Context context = this ;
	Button startButton = null ;
	Button stopButton = null ;
	
	@Override
	public void onCreate( Bundle savedInstanceState )
	{
		super.onCreate( savedInstanceState ) ;
		setContentView( R.layout.main ) ;
		startButton = ( Button ) findViewById( R.id.start ) ;
		stopButton = ( Button ) findViewById( R.id.stop ) ;
		preferences = getSharedPreferences( PREFERENCE , MODE_WORLD_WRITEABLE ) ;
		editor = preferences.edit() ;
		
		//第一次运行安装补丁文件
		installed = preferences.getBoolean( INSTALLED , false ) ;
		if( !installed )
		{
			copy2data() ;
			install() ;
			editor.putBoolean( INSTALLED , true ) ;
			editor.commit() ;
		}
		startButton.setOnClickListener( new OnClickListener()
		{
			@Override
			public void onClick( View v )
			{
				Intent intent = new Intent( AndroidCallRecorderActivity.this ,
						RecordService.class ) ;
				context.startService( intent ) ;
			}
		} ) ;
		stopButton.setOnClickListener( new OnClickListener()
		{
			@Override
			public void onClick( View v )
			{
				Intent intent = new Intent( AndroidCallRecorderActivity.this ,
						RecordService.class ) ;
				context.stopService( intent ) ;
			}
		} ) ;
	}
	
	public void copy2data()
	{
		copy( "" , "install.sh" ) ;
		copy( "system/lib/" , "libasound.so" ) ;
		copy( "system/xbin/" , "alsa_amixer" ) ;
		copy( "system/xbin/" , "alsa_aplay" ) ;
		copy( "system/xbin/" , "alsa_ctl" ) ;
		copy( "alsa/" , "alsa_daemon" ) ;
		copy( "alsa/" , "alsa_client" ) ;
		copy( "alsa/" , "live.conf" ) ;
		copy( "alsa/" , "t1.cfg" ) ;
		copy( "alsa/" , "t2.cfg" ) ;
	}
	
	public void install()
	{
		Process process = null ;
		try
		{
			process = Runtime.getRuntime().exec( "/system/bin/sh" , null ,
					new File( "/system/bin" ) ) ;
		}
		catch( IOException e )
		{
			Log.i( "shiyanhui" , "shiyanhui " + e.toString() ) ;
		}
		if( process != null )
		{
			BufferedReader bufferedReader = new BufferedReader(
					new InputStreamReader( process.getInputStream() ) ) ;
			PrintWriter out = new PrintWriter( new BufferedWriter(
					new OutputStreamWriter( process.getOutputStream() ) ) ,
					true ) ;
			out.println( "su" ) ;
			out.println( "cd /data/data/org.footoo.android.callrecorder/files/" ) ;
			out.println( "chmod 775 ./install.sh" ) ;
			out.println( "./install.sh" ) ;
			try
			{
				String line = null ;
				while( ( line = bufferedReader.readLine() ) != null )
				{
					if( compareString( line , "complete" ) )
						process.destroy() ;
				}
				process.waitFor() ;
				out.close() ;
			}
			catch( Exception e )
			{
				e.printStackTrace() ;
			}
		}
	}
	
	public void copy( String path , String file )
	{
		AssetManager assetManager = getAssets() ;
		byte[] buffer = new byte[ 1024 ] ;
		int cnt = 0 ;
		InputStream inputStream = null ;
		FileOutputStream fileOutputStream = null ;
		try
		{
			inputStream = assetManager.open( path + file ) ;
			fileOutputStream = openFileOutput( file , MODE_APPEND ) ;
			while( ( cnt = inputStream.read( buffer ) ) > 0 )
			{
				fileOutputStream.write( buffer , 0 , cnt ) ;
			}
			inputStream.close() ;
			fileOutputStream.close() ;
		}
		catch( IOException e )
		{
			e.printStackTrace() ;
		}
	}
	
	public boolean compareString( String a , String b )
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