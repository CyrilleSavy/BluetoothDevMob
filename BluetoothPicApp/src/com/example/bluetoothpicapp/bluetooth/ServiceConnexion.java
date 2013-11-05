
package com.example.bluetoothpicapp.bluetooth;


import android.app.IntentService;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.widget.Toast;

public class ServiceConnexion extends IntentService
	{
	
	// Attribut propre au Service
	private int mStartMode; // indicates how to behave if the service is killed
	private IBinder mBinder; // interface for clients that bind
	private boolean mAllowRebind; // indicates whether onRebind should be used
	
	// Nom du service utilisé
	private static final String SERVICE_NAME = "ServiceConnexion";
	
	// Utilisation de notre interface bluetooth
	private SerialComBluetooth mSerialCommInterface;
	
	// Message types sent from the BluetoothChatService Handler
	public static final int MESSAGE_STATE_CHANGE = 1;
	public static final int MESSAGE_READ = 2;
	public static final int MESSAGE_WRITE = 3;
	public static final int MESSAGE_DEVICE_NAME = 4;
	public static final int MESSAGE_TOAST = 5;
	
	// Key names received from the BluetoothChatService Handler
	public static final String DEVICE_NAME = "device_name";
	public static final String TOAST = "toast";
	
	// Intent request codes
	private static final int REQUEST_CONNECT_DEVICE_SECURE = 1;
	private static final int REQUEST_CONNECT_DEVICE_INSECURE = 2;
	private static final int REQUEST_ENABLE_BT = 3;
	
	public ServiceConnexion()
		{
		super(SERVICE_NAME);
		mSerialCommInterface = new SerialComBluetooth(getApplicationContext(), mHandler);
		}
	
	@Override
	public void onCreate()
		{
		// The service is being created
		}
	
	@Override
	public int onStartCommand(Intent intent, int flags, int startId)
		{
		// The service is starting, due to a call to startService()
		return mStartMode;
		}
	
	@Override
	public IBinder onBind(Intent intent)
		{
		// A client is binding to the service with bindService()
		return mBinder;
		}
	
	@Override
	public boolean onUnbind(Intent intent)
		{
		// All clients have unbound with unbindService()
		return mAllowRebind;
		}
	
	@Override
	public void onRebind(Intent intent)
		{
		// A client is binding to the service with bindService(),
		// after onUnbind() has already been called
		}
	
	@Override
	public void onDestroy()
		{
		// The service is no longer used and is being destroyed
		}
	
	@Override
	protected void onHandleIntent(Intent intent)
		{
		
		}
	
	private final Handler mHandler = new Handler()
		{
			
			@Override
			public void handleMessage(Message msg)
				{
				switch(msg.what)
					{
					case MESSAGE_STATE_CHANGE:
						switch(msg.arg1)
							{
							case SerialComBluetooth.STATE_CONNECTED:
								break;
							case SerialComBluetooth.STATE_CONNECTING:
								break;
							case SerialComBluetooth.STATE_LISTEN:
							case SerialComBluetooth.STATE_NONE:
								break;
							}
						break;
					case MESSAGE_WRITE:
						
						break;
					case MESSAGE_READ:
						
						break;
					case MESSAGE_DEVICE_NAME:
						
						break;
					case MESSAGE_TOAST:
						
						break;
					}
				}
		};
	
	}
