
package com.example.bluetoothpicapp.bluetooth;

import java.util.List;

import android.app.IntentService;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.widget.Toast;

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
	
	//Classe bt
	private SerialComBluetooth mSerialComm;
	private List<BluetoothDevice> mDiscoveredDevice;
	
	private final Handler mHandlerMain;
	
	public BluetoothConnexion(Context context, Handler handler)
		{
		this.mSerialComm = new SerialComBluetooth(context, this.mHandler);
		this.mHandlerMain = handler;
		startBt();
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
		this.mSerialComm.discoverDevices();
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
	 * Alumme ou �teint une led
	 * @param aLedNum : Num. de la led [0-7]
	 * @param aState : 0 ou 1
	 */
	public void writeLed(char aLedNum, char aState)
		{
		String msg = "$0_" + aLedNum + "_" + aState + "_\r\n";
		this.writeSerial(msg.getBytes());
		}
	
	public void startReadSw()
		{
		String msg = "$1\r\n";
		this.writeSerial(msg.getBytes());
		}
	
	public void startReadPot()
		{
		String msg = "$2\r\n";
		this.writeSerial(msg.getBytes());
		}
	
	private void writeSerial(byte[] aBuf)
		{
		this.mSerialComm.write(aBuf);
		}
	
	//Recup�ration des �v�nements envoy� par le Bluetooth
	private final Handler mHandler = new Handler()
		{
			
			@Override
			public void handleMessage(Message msg)
				{
				switch(msg.what)
					{
					case MESSAGE_STATE_CHANGE:
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
						Message msgSend = mHandlerMain.obtainMessage(MESSAGE_DEVICE_NAME);
						mHandlerMain.sendMessage(msgSend);
						break;
					case MESSAGE_TOAST:
						break;
					default:
						;
					}
				}
		};
	
	}
