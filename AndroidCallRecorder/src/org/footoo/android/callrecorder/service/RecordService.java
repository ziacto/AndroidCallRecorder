package org.footoo.android.callrecorder.service ;

import java.io.BufferedReader ;
import java.io.BufferedWriter ;
import java.io.File ;
import java.io.IOException ;
import java.io.InputStreamReader ;
import java.io.OutputStreamWriter ;
import java.io.PrintWriter ;
import java.util.regex.Matcher ;
import java.util.regex.Pattern ;

import android.app.Service ;
import android.content.Intent ;
import android.os.IBinder ;
import android.util.Log ;

public class RecordService extends Service
{
	int alsa_daemon_pid = -1 ;
	int alsa_client_pid = -1 ;
	
	@Override
	public IBinder onBind( Intent intent )
	{
		return null ;
	}
	
	@Override
	public void onCreate()
	{
		super.onCreate() ;
	}
	
	@Override
	public void onStart( Intent intent , int startId )
	{
		super.onStart( intent , startId ) ;
		startRecord( "audio.tmp" ) ;
	}
	
	@Override
	public void onDestroy()
	{
		stopRecord( alsa_daemon_pid , alsa_client_pid ) ;
		super.onDestroy() ;
	}
	
	/**
	 * @param file 录音文件名
	 * 录音
	 */
	public void startRecord( String file )
	{
		Process process = null ;
		Pattern alsa_daemon_pid_pattern = Pattern
				.compile( "daemon started, pid=(.*)" ) ;
		Pattern alsa_client_pid_pattern = Pattern
				.compile( "Recording started, address to stop: (.*)" ) ;
		Matcher matcher = null ;
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
			out.println( "cd /" ) ;
			out.println( "./alsa_daemon 2> tmp.tmp" ) ;
			out.println( "cat tmp.tmp" ) ;
			out.println( "./alsa_client cfg t2.cfg" ) ;
			out.println( "./alsa_client start " + file + " 2> tmp.tmp" ) ;
			out.println( "cat tmp.tmp" ) ;
			try
			{
				String line = null ;
				while( ( line = bufferedReader.readLine() ) != null )
				{
					matcher = alsa_daemon_pid_pattern.matcher( line ) ;
					if( matcher.find() )
					{
						Log.i( "shiyanhui" , "shiyanhui " + matcher.group( 1 ) ) ;
						alsa_daemon_pid = Integer.valueOf( matcher.group( 1 ) )
								.intValue() ;
					}
					matcher = alsa_client_pid_pattern.matcher( line ) ;
					if( matcher.find() )
					{
						Log.i( "shiyanhui" , "shiyanhui " + matcher.group( 1 ) ) ;
						alsa_client_pid = Integer.valueOf( matcher.group( 1 ) )
								.intValue() ;
					}
				}
				process.waitFor() ;
				out.close() ;
				process.destroy() ;
			}
			
			catch( Exception e )
			{
				e.printStackTrace() ;
			}
		}
		
	}
	/**
	 * @param daemon_pid 守护进程pid
	 * @param client_id  client端pid
	 * 停止录音
	 */
	public void stopRecord( int daemon_pid , int client_id )
	{
		if( daemon_pid < 0 || client_id < 0 )
			return ;
		Process proc = null ;
		try
		{
			proc = Runtime.getRuntime().exec( "/system/bin/sh" , null ,
					new File( "/system/bin" ) ) ;
		}
		catch( IOException e )
		{
			e.printStackTrace() ;
		}
		if( proc != null )
		{
			PrintWriter out = new PrintWriter( new BufferedWriter(
					new OutputStreamWriter( proc.getOutputStream() ) ) , true ) ;
			out.println( "su" ) ;
			out.println( "cd /" ) ;
			out.println( "./alsa_client stop " + client_id ) ;
			out.println( "kill " + daemon_pid ) ;
			try
			{
				proc.waitFor() ;
				out.close() ;
				proc.destroy() ;
			}
			catch( Exception e )
			{
				e.printStackTrace() ;
			}
		}
	}
}
