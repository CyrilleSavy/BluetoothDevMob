
package com.example.bluetoothpicapp.bluetooth;

import java.io.Serializable;
import java.util.List;

import com.example.bluetoothpicapp.ActivitePrinc;

import android.app.IntentService;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.Parcel;
import android.os.Parcelable;
import android.widget.Toast;

/**
 * Met a disposition des méthodes statiques pour accéder au bluetooth
 * @author Michael
 *
 */
public class BluetoothConnexion
	{
	
	// Message types sent from the BluetoothChatService Handler
	public static final int MESSAGE_STATE_CHANGE = 1;
	public static final int MESSAGE_READ = 2;
	public static final int MESSAGE_WRITE = 3;
	public static final int MESSAGE_DEVICE_NAME = 4;
	public static final int MESSAGE_TOAST = 5;
	public static final int MESSAGE_DISCOVERY_FINISHED = 6;
	
	//Classe bt
	private SerialComBluetooth mSerialComm;
	private List<BluetoothDevice> mDiscoveredDevice;
	
	private static Handler mHandlerMain = null;
	
	public BluetoothConnexion(Context context, Handler handler)
		{
		this.mSerialComm = new SerialComBluetooth(context, this.mHandler);
		this.mHandlerMain = handler;
		startBt();
		}
	
	public void setHandlerMain(Handler mHandlerMainSrc)
		{
		mHandlerMain = mHandlerMainSrc;
		}
	
	/**
	 * Démmarre le serveur bluetooth
	 */
	public void startBt()
		{
		this.mSerialComm.start();
		}
	
	/**
	 * Démmarre le scan bluetooth
	 */
	public void startDiscovery()
		{
		if (this.mSerialComm.isAdapterEnabled())
			{
			this.mSerialComm.discoverDevices();
			}
		else
			{
			this.mSerialComm.setAdapterEnable();
			}
		}
	
	public void connect(BluetoothDevice device)
		{
		this.mSerialComm.connect(device);
		}
	
	public List<BluetoothDevice> getDiscoveredDevices()
		{
		return this.mDiscoveredDevice;
		}
	
	/**
	 * Alumme ou éteint une led
	 * @param aLedNum : Num. de la led [0-7]
	 * @param aState : 0 ou 1
	 */
	public void writeLed(int aLedNum, int aState)
		{
		String msg = "$1_" + String.valueOf(aLedNum) + "_" + String.valueOf(aState) + "_\r\n";
		this.writeSerial(msg.getBytes());
		}
	
	private void writeSerial(byte[] aBuf)
		{
		this.mSerialComm.write(aBuf);
		}
	
	//Recupération des événements envoyé par le Bluetooth
	private final Handler mHandler = new Handler()
		{
			
			Message msgSend;
			
			@Override
			public void handleMessage(Message msg)
				{
				switch(msg.what)
					{
					case MESSAGE_STATE_CHANGE:
						switch(msg.arg1)
							{
							case SerialComBluetooth.STATE_CONNECTED:
								mHandlerMain.obtainMessage(ActivitePrinc.MESSAGE_STATE_CHANGE, SerialComBluetooth.STATE_CONNECTED, -1).sendToTarget();
								break;
							case SerialComBluetooth.STATE_CONNECTING:
								mHandlerMain.obtainMessage(ActivitePrinc.MESSAGE_STATE_CHANGE, SerialComBluetooth.STATE_CONNECTING, -1).sendToTarget();
								break;
							case SerialComBluetooth.STATE_LISTEN:
								mHandlerMain.obtainMessage(ActivitePrinc.MESSAGE_STATE_CHANGE, SerialComBluetooth.STATE_LISTEN, -1).sendToTarget();
								break;
							case SerialComBluetooth.STATE_NO_ADAPTER:
								mHandlerMain.obtainMessage(ActivitePrinc.MESSAGE_STATE_CHANGE, SerialComBluetooth.STATE_NO_ADAPTER, -1).sendToTarget();
								break;
							case SerialComBluetooth.STATE_NONE:
								mHandlerMain.obtainMessage(ActivitePrinc.MESSAGE_STATE_CHANGE, SerialComBluetooth.STATE_NONE, -1).sendToTarget();
								break;
							default:
								;
							}
						break;
					case MESSAGE_READ:
						byte[] readBuf = (byte[])msg.obj;
						String[] strTabVal;
						// construct a string from the valid bytes in the buffer
						String readMessage = new String(readBuf, 3, msg.arg1 - 2); // $0_ | string | \r\n
						
						//Get the command
						switch(readBuf[1])
							{
							// We get Leds
							case '1':
								
								break;
							//We get Switchs
							case '2':
								strTabVal = readMessage.split("_");
								break;
							//We get Pot
							case '3':
								break;
							default:
								;
							}
						
						break;
					case MESSAGE_WRITE:
						break;
					//On a trouvé un device
					case MESSAGE_DEVICE_NAME:
						// On récupère la liste 
						mDiscoveredDevice = mSerialComm.getDiscoveredDevices();
						msgSend = mHandlerMain.obtainMessage(ActivitePrinc.MESSAGE_DEVICE_DISCOVERED);
						mHandlerMain.sendMessage(msgSend);
						break;
					case MESSAGE_TOAST:
						break;
					case MESSAGE_DISCOVERY_FINISHED:
						msgSend = mHandlerMain.obtainMessage(ActivitePrinc.MESSAGE_DISC_FINISHED);
						mHandlerMain.sendMessage(msgSend);
						break;
					default:
						;
					}
				}
		};
	}
