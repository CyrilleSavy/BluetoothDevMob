
package com.example.bluetoothpicapp.bluetooth;

import java.util.LinkedHashSet;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.os.Handler;
import android.os.Message;

import com.example.bluetoothpicapp.ActivitePrinc;

/**
 * Met a disposition des m�thodes statiques pour acc�der au bluetooth
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
	private LinkedHashSet<BluetoothDevice> mDiscoveredDevice;
	
	private static Handler mHandlerMain = null;
	
	public BluetoothConnexion(Context context, Handler handler)
		{
		this.mSerialComm = new SerialComBluetooth(context, this.mHandler);
		mHandlerMain = handler;
		startBt();
		}
	
	public void setHandlerMain(Handler mHandlerMainSrc)
		{
		mHandlerMain = mHandlerMainSrc;
		}
	
	/**
	 * D�mmarre le serveur bluetooth
	 */
	public void startBt()
		{
		this.mSerialComm.start();
		}
	
	/**
	 * D�mmarre le scan bluetooth
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
	
	public LinkedHashSet<BluetoothDevice> getDiscoveredDevices()
		{
		return this.mDiscoveredDevice;
		}
	
	/**
	 * Alumme ou �teint une led
	 * @param aLedNum : Num. de la led [0-7]
	 * @param aState : 0 ou 1
	 */
	public void writeLed(int aLedNum, int aState)
		{
		String msg = "$1_" + String.valueOf(aLedNum) + "_" + String.valueOf(aState) + "_\r\n";
		this.writeSerial(msg.getBytes());
		}
	
	public void startReadSw()
		{
		String msg = "$2\r\n";
		this.writeSerial(msg.getBytes());
		}
	
	public void startReadPot()
		{
		String msg = "$3\r\n";
		this.writeSerial(msg.getBytes());
		}
	
	private void writeSerial(byte[] aBuf)
		{
		this.mSerialComm.write(aBuf);
		}
	
	//Recup�ration des �v�nements envoy� par le Bluetooth
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
						// construct a string from the valid bytes in the buffer
						String readMessage = new String(readBuf, 0, msg.arg1);
						break;
					case MESSAGE_WRITE:
						break;
					//On a trouv� un device
					case MESSAGE_DEVICE_NAME:
						// On r�cup�re la liste 
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
