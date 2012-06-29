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

import org.footoo.android.callrecorder.util.StringUtil ;

import android.app.Service ;
import android.content.Intent ;
import android.os.IBinder ;
import android.util.Log ;

public class RecordService extends Service
{
	static String alsa_daemon_pid = null ;
	static String alsa_client_pid = null ;
	
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
		startRecord( "audio" ) ;
	}
	
	@Override
	public void onDestroy()
	{
		stopRecord() ;
		super.onDestroy() ;
	}
	
	/**
	 * @param file
	 *            录音文件名 录音
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
			Log.i( "ERROR" , e.toString() ) ;
		}
		if( process != null )
		{
			BufferedReader bufferedReader = new BufferedReader(
					new InputStreamReader( process.getInputStream() ) ) ;
			PrintWriter out = new PrintWriter( new BufferedWriter(
					new OutputStreamWriter( process.getOutputStream() ) ) ,
					true ) ;
			out.println( "su" ) ;
			out.println( "cd /data/tmp" ) ;
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
						alsa_daemon_pid = matcher.group( 1 ) ;
					}
					matcher = alsa_client_pid_pattern.matcher( line ) ;
					if( matcher.find() )
					{
						alsa_client_pid = matcher.group( 1 ) ;
						process.destroy() ;
						break ;
					}
				}
				process.waitFor() ;
				out.close() ;
				
			}
			
			catch( Exception e )
			{
				Log.i( "ERROR" , e.toString() ) ;
			}
		}
		
	}
	
	/**
	 * @param daemon_pid
	 *            守护进程pid
	 * @param client_id
	 *            client端pid 停止录音
	 */
	public void stopRecord()
	{
		if( alsa_client_pid == null || alsa_daemon_pid == null )
			return ;
		Process proc = null ;
		try
		{
			proc = Runtime.getRuntime().exec( "/system/bin/sh" , null ,
					new File( "/system/bin" ) ) ;
		}
		catch( IOException e )
		{
		}
		if( proc != null )
		{
			BufferedReader bufferedReader = new BufferedReader(
					new InputStreamReader( proc.getInputStream() ) ) ;
			PrintWriter out = new PrintWriter( new BufferedWriter(
					new OutputStreamWriter( proc.getOutputStream() ) ) , true ) ;
			out.println( "su" ) ;
			out.println( "cd /data/tmp" ) ;
			out.println( "./alsa_client stop " + alsa_client_pid
					+ " 2> tmp.tmp" ) ;
			out.println( "cat tmp.tmp" ) ;
			out.println( "echo complete" ) ;
			alsa_client_pid = null ;
			try
			{
				String line = null ;
				while( ( line = bufferedReader.readLine() ) != null )
				{
					if( StringUtil.compareString( line , "complete" ) )
					{
						out.println( "./pcm2wav audio audio.wav 1 8000 16" ) ;
						out.println( "cat audio.wav > /sdcard/audio.wav" ) ;
						proc.destroy() ;
						break ;
					}
				}
				proc.waitFor() ;
				out.close() ;
			}
			catch( Exception e )
			{
				e.printStackTrace() ;
			}
		}
	}
}
