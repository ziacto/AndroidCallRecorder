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
import org.footoo.android.callrecorder.util.StringUtil ;
import android.app.Activity ;
import android.content.Context ;
import android.content.Intent ;
import android.content.SharedPreferences ;
import android.content.res.AssetManager ;
import android.os.Bundle ;
import android.util.Log ;
import android.view.View ;
import android.view.View.OnClickListener ;
import android.widget.ImageButton ;
import android.widget.Toast ;

public class AndroidCallRecorderActivity extends Activity
{
	private static final String LOG_TAG = "AndroidCallRecorder" ;
	private static final String PREFERENCE = "RECORD_PREFERENCE" ;
	private static final String INSTALLED = "INSTALLED" ;
	SharedPreferences preferences = null ;
	SharedPreferences.Editor editor = null ;
	boolean installed = false ;
	Context context = this ;
	ImageButton controlButton = null ;
	static boolean flag = false ;
	
	@Override
	public void onCreate( Bundle savedInstanceState )
	{
		super.onCreate( savedInstanceState ) ;
		setContentView( R.layout.recorde ) ;
		controlButton = ( ImageButton ) findViewById( R.id.control ) ;
		preferences = getSharedPreferences( PREFERENCE , MODE_WORLD_WRITEABLE ) ;
		editor = preferences.edit() ;
		
		// 第一次运行安装补丁文件
		installed = preferences.getBoolean( INSTALLED , false ) ;
		removeOld() ;
		copy2data() ;
		install() ;
		editor.putBoolean( INSTALLED , true ) ;
		editor.commit() ;
		controlButton.setOnClickListener( new OnClickListener()
		{
			@Override
			public void onClick( View v )
			{
				Intent intent = new Intent( AndroidCallRecorderActivity.this ,
						RecordService.class ) ;
				String content = null ;
				if( !flag )
				{
					context.startService( intent ) ;
					content = "Started!" ;
					flag = true ;
					controlButton
							.setBackgroundResource( R.drawable.start_record ) ;
				}
				else
				{
					context.stopService( intent ) ;
					content = "Stoped!" ;
					flag = false ;
					controlButton
							.setBackgroundResource( R.drawable.stop_record ) ;
				}
				Toast.makeText( context , content , Toast.LENGTH_LONG ).show() ;
			}
		} ) ;
	}
	
	public void copy2data()
	{
		int[] fileNum = { 1 , 1 , 3 , 6 , 1 , 1 , 15 } ;
		String[] dir = { "" , "system/lib/" , "system/xbin/" , "alsa/" ,
				"system/usr/share/alsa/cards/" , "system/usr/share/alsa/" ,
				"system/usr/share/alsa/pcm/" } ;
		String[] file = { "install.sh" , "libasound.so" , "alsa_amixer" ,
				"alsa_aplay" , "alsa_ctl" , "pcm2wav" , "alsa_daemon" ,
				"alsa_client" , "live.conf" , "t1.cfg" , "t2.cfg" ,
				"aliases.conf" , "alsa.conf" , "center_lfe.conf" ,
				"default.conf" , "dmix.conf" , "dpl.conf" , "dsnoop.conf" ,
				"front.conf" , "iec958.conf" , "modem.conf" , "rear.conf" ,
				"side.conf" , "surround40.conf" , "surround41.conf" ,
				"surround50.conf" , "surround51.conf" , "surround71.conf" } ;
		
		int cnt = 0 ;
		for( int i = 0 ; i < dir.length ; ++ i )
		{
			for( int j = 0 ; j < fileNum[ i ] ; ++ j )
			{
				copy( dir[ i ] , file[ cnt ++ ] ) ;
			}
		}
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
			Log.i( LOG_TAG , e.toString() ) ;
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
			out.println( "echo complete" ) ;
			try
			{
				String line = null ;
				while( ( line = bufferedReader.readLine() ) != null )
				{
					if( StringUtil.compareString( line , "complete" ) )
					{
						process.destroy() ;
						break ;
					}
				}
				process.waitFor() ;
				out.close() ;
			}
			catch( Exception e )
			{
				Log.i( LOG_TAG , e.toString() ) ;
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
			Log.i( LOG_TAG , e.toString() ) ;
		}
	}
	
	public void removeOld()
	{
		Process process = null ;
		try
		{
			process = Runtime.getRuntime().exec( "/system/bin/sh" , null ,
					new File( "/system/bin" ) ) ;
		}
		catch( IOException e )
		{
			Log.i( LOG_TAG , e.toString() ) ;
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
			out.println( "rm *" ) ;
			out.println( "echo complete" ) ;
			try
			{
				String line = null ;
				while( ( line = bufferedReader.readLine() ) != null )
				{
					if( StringUtil.compareString( line , "complete" ) )
					{
						process.destroy() ;
						break ;
					}
				}
				process.waitFor() ;
				out.close() ;
			}
			catch( Exception e )
			{
				Log.i( LOG_TAG , e.toString() ) ;
			}
		}
	}
}