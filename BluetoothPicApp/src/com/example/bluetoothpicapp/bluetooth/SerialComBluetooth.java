
package com.example.bluetoothpicapp.bluetooth;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.UUID;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Handler;
import android.os.Message;
import android.os.ParcelUuid;
import android.util.Log;
import android.widget.Toast;

public class SerialComBluetooth extends BroadcastReceiver
	{
	
	/*------------------------------------------------------------------*\
	|*			Attributs					*|
	\*------------------------------------------------------------------*/
	private BluetoothAdapter mBluetoothAdapter;
	private List<BluetoothDevice> mDiscoveredDevice;
	private ConnectThread connectThread;
	private ConnectedThread connectedThread;
	private AcceptThread mSecureAcceptThread;
	
	private Context mContext;
	
	// Unique UUID
	// Name for the SDP record when creating server socket
	private static final String NAME_SECURE = "SerialComm";
	
	// TODO DEFINIR UN UUID POUR LE PIC
	private static final UUID UUID_SPP = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
	
	// Hanlder de l'activite qui contrele le BT
	private final Handler mHandler;
	// Etat de la connexion comme tout est asynchrone
	private int mState;
	
	// Etats possible de la connexion
	
	public static final int STATE_NONE = 0;
	public static final int STATE_LISTEN = 1;
	public static final int STATE_CONNECTING = 2;
	public static final int STATE_CONNECTED = 3;
	public static final int STATE_NO_ADAPTER = 4;
	
	// Debug
	private static final String TAG = "SerialComBluetooth";
	private static final boolean D = true;
	
	/*------------------------------------------------------------------*\
	|*			Constructeur					*|
	\*------------------------------------------------------------------*/
	
	/**
	 * Constructeur du bluetooth
	 * 
	 * @param context
	 *            : Contexte de l'application
	 * @param handler
	 *            : Handler de la communication BT
	 */
	public SerialComBluetooth(Context context, Handler handler)
		{
		super();
		this.mHandler = handler;
		this.mContext = context;
		this.mDiscoveredDevice = new ArrayList<BluetoothDevice>();
		
		// Verification si le bluetooth du smartphone est disponible
		this.mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		
		// L'adapteur n'est pas pr�sent
		if (mBluetoothAdapter == null)
			{
			setState(STATE_NO_ADAPTER);
			Toast toast = Toast.makeText(context, "Bluetooth not supported", Toast.LENGTH_SHORT);
			toast.show();
			return;
			}
		
		// Il faut que le bluetooth soit enclench�
		if (!mBluetoothAdapter.isEnabled())
			{
			Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
			enableBtIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			this.mContext.startActivity(enableBtIntent);
			}
		
		// On s'enregistre aupr�s des diff�rent message de broadcast
		IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
		this.mContext.registerReceiver(this, filter);
		
		filter = new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
		this.mContext.registerReceiver(this, filter);
		
		}
	
	/*------------------------------------------------------------------*\
	|*			Methodes publiques				*|
	\*------------------------------------------------------------------*/
	
	public boolean isAdapterEnabled()
		{
		return this.mBluetoothAdapter.isEnabled();
		}
	
	public void setAdapterEnable()
		{
		Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
		enableBtIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		this.mContext.startActivity(enableBtIntent);
		}
	
	/**
	 * Fonction qui retourne les p�riph�riques attach�s au mobile
	 * 
	 * @return Un Set de "BluetoothDevice" si il y en a au moins 1 sinon "null"
	 */
	public Set<BluetoothDevice> getPairedDevices()
		{
		
		Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
		if (pairedDevices.size() > 0)
			{
			return null;
			}
		else
			{
			return pairedDevices;
			}
		}
	
	/**
	 * Permet de d�couvrir des p�riph�riques Fonction asyncrone
	 */
	public void discoverDevices()
		{
		// On vide la liste
		this.mDiscoveredDevice.clear();
		
		// Si on scanne d�ja on arr�te
		if (this.mBluetoothAdapter.isDiscovering())
			{
			this.mBluetoothAdapter.cancelDiscovery();
			}
		
		// On lance le scan
		this.mBluetoothAdapter.startDiscovery();
		}
	
	/**
	 * Fonction qui retourne les p�riph�riques d�couvert au mobile
	 * 
	 * @return Une liste de "BluetoothDevice"
	 * 
	 *         On ne peut pas utiliser un Set car "BluetoothDevice" n'impl�mente
	 *         pas comparable
	 */
	public List<BluetoothDevice> getDiscoveredDevices()
		{
		return this.mDiscoveredDevice;
		}
	
	/**
	 * D�mmare le thread "ConnectedThread" pour se connecter � un p�riph�rique
	 * 
	 * @param device
	 *            P�riph�rique
	 */
	public synchronized void connect(BluetoothDevice device)
		{
		if (D) Log.d(TAG, "connect to: " + device);
		
		// Si on est d�ja entrain de tester une connexion on l'annule
		if (mState == STATE_CONNECTING)
			{
			if (this.connectThread != null)
				{
				this.connectThread.cancel();
				this.connectThread = null;
				}
			}
		
		// Si on est connect�, on annule le thread de connexion
		if (this.connectedThread != null)
			{
			this.connectedThread.cancel();
			this.connectedThread = null;
			}
		
		// Tuer le serveur
		if (mSecureAcceptThread != null)
			{
			mSecureAcceptThread.cancel();
			mSecureAcceptThread = null;
			}
		
		// Start du thread qui va tenter de se connecter au p�riph.
		this.connectThread = new ConnectThread(device);
		this.connectThread.start();
		
		setState(STATE_CONNECTING);
		}
	
	/**
	 * Start the chat service. Specifically start AcceptThread to begin a
	 * session in listening (server) mode. Called by the Activity onResume()
	 */
	public synchronized void start()
		{
		if (D) Log.d(TAG, "start");
		
		// Cancel any thread attempting to make a connection
		if (connectThread != null)
			{
			connectThread.cancel();
			connectThread = null;
			}
		
		// Cancel any thread currently running a connection
		if (connectThread != null)
			{
			connectThread.cancel();
			connectThread = null;
			}
		
		// Start the thread to listen on a BluetoothServerSocket
		if (mSecureAcceptThread != null)
			{
			mSecureAcceptThread.cancel();
			mSecureAcceptThread = null;
			}
		
		if (!mBluetoothAdapter.isEnabled())
			{
			setState(STATE_NONE);
			}
		else
			{
			// Ici pour eviter la concurrence
			setState(STATE_LISTEN);
			
			// Start the thread to listen on a BluetoothServerSocket
			if (mSecureAcceptThread == null)
				{
				mSecureAcceptThread = new AcceptThread();
				mSecureAcceptThread.start();
				}
			}
		}
	
	/**
	 * Retourne l'�tat de la communication courant
	 */
	public synchronized int getState()
		{
		return mState;
		}
	
	/**
	 * Stop tous les threads
	 */
	public synchronized void stop()
		{
		if (D) Log.d(TAG, "stop");
		
		if (this.connectThread != null)
			{
			this.connectThread.cancel();
			this.connectThread = null;
			}
		
		if (this.connectedThread != null)
			{
			this.connectedThread.cancel();
			this.connectedThread = null;
			}
		
		if (mSecureAcceptThread != null)
			{
			mSecureAcceptThread.cancel();
			mSecureAcceptThread = null;
			}
		
		setState(STATE_NONE);
		}
	
	/**
	 * Ecrit dans le thread de connexion de facon asynchcrone
	 * 
	 * @param out
	 *            Le tableau de bytes � �crire
	 * @see ConnectedThread#write(byte[])
	 */
	public void write(byte[] out)
		{
		// Creation d'un objet temporaire
		ConnectedThread r;
		// On veut �viter que deux thread �crive dans le m�me flux en m�me temps
		// Programmation concurrente �quivalent �
		// synchronized void write(byte[] out) {
		// //section critique : ici on veut acc�der au thread de connexion
		// }
		synchronized (this)
			{
			if (mState != STATE_CONNECTED) return;
			r = this.connectedThread;
			}
		// Ecriture dans le flux
		r.write(out);
		}
	
	/**
	 * D�mmare le thread qui permet de transmettre les donn�es entre
	 * p�riph�riques
	 * 
	 * @param socket
	 *            Le "BluetoothSocket" sur lequel est bas� la connexion
	 * @param device
	 *            Le "BluetoothDevice" sur lequel nous sommes connect�s
	 */
	public synchronized void connected(BluetoothSocket socket, BluetoothDevice device, final String socketType)
		{
		if (D) Log.d(TAG, "connected, Socket Type:" + socketType);
		
		// On annule tout les autres threads
		if (this.connectThread != null)
			{
			this.connectThread.cancel();
			this.connectThread = null;
			}
		
		if (this.connectedThread != null)
			{
			this.connectedThread.cancel();
			this.connectedThread = null;
			}
		
		// Cancel the accept thread because we only want to connect to one
		// device
		if (mSecureAcceptThread != null)
			{
			mSecureAcceptThread.cancel();
			mSecureAcceptThread = null;
			}
		
		// On d�marre le thread qui va g�rer la communication
		this.connectedThread = new ConnectedThread(socket, socketType);
		this.connectedThread.start();
		
		setState(STATE_CONNECTED);
		}
	
	/*------------------------------------------------------------------*\
	|*			Methodes is					*|
	\*------------------------------------------------------------------*/
	
	/*------------------------------------------------------------------*\
	|*			Methodes priv�e					*|
	\*------------------------------------------------------------------*/
	
	private void addBTDevice(BluetoothDevice mBTDevice)
		{
		this.mDiscoveredDevice.add(mBTDevice);
		}
	
	/**
	 * Permet de changer l'�tat de la connexion
	 * 
	 * @param state
	 *            Entier qui repr�sente les �tats
	 */
	private synchronized void setState(int state)
		{
		if (D) Log.d(TAG, "setState() " + mState + " -> " + state);
		mState = state;
		
		// Permet d'envoyer un message asynchrone � l'activit� qui poss�de le
		// Handler
		mHandler.obtainMessage(BluetoothConnexion.MESSAGE_STATE_CHANGE, state, -1).sendToTarget();
		
		}
	
	/**
	 * Fonction qui permet de g�rer si une connexion � �chou�e
	 */
	private void connectionFailed()
		{
		// Action a faire si la connexion � �chou�e
		
		// Start the service over to restart listening mode
		SerialComBluetooth.this.start();
		}
	
	/**
	 * Fonction qui permet de g�rer si la connexion c'est perdue
	 */
	private void connectionLost()
		{
		
		// Start the service over to restart listening mode
		SerialComBluetooth.this.start();
		}
	
	/*------------------------------------------------------------------*\
	|*			Broadcast receiver				*|
	\*------------------------------------------------------------------*/
	@Override
	public void onReceive(Context context, Intent intent)
		{
		
		String action = intent.getAction();
		
		// Un nouveau p�riph est d�couvert
		if (BluetoothDevice.ACTION_FOUND.equals(action))
			{
			// On r�cup�re les donn�es du p�riph.
			BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
			// On les ajoute � la liste
			SerialComBluetooth.this.addBTDevice(device);
			
			//On averti que l'on a trouve un periph.
			Message msg = mHandler.obtainMessage(BluetoothConnexion.MESSAGE_DEVICE_NAME);
			mHandler.sendMessage(msg);
			}
		// Quand le scan est termine
		else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action))
			{
			Message msg = mHandler.obtainMessage(BluetoothConnexion.MESSAGE_DISCOVERY_FINISHED);
			mHandler.sendMessage(msg);
			}
		
		}
	
	/*------------------------------------------------------------------*\
	|*			classe interne priv�e				*|
	\*------------------------------------------------------------------*/
	
	/**
	 * Ce thread permet d'�tablir la connexion avec un p�riph�rique BT
	 */
	private class ConnectThread extends Thread
		{
		
		private final BluetoothSocket mmSocket;
		private final BluetoothDevice mmDevice;
		private String mSocketType;
		
		public ConnectThread(BluetoothDevice device)
			{
			mmDevice = device;
			BluetoothSocket tmp = null;
			mSocketType = "secure";
			
			// On r�cup�re un socket de connexion
			// ATTENTION !! UUID doit �tre le m�me sur la partie serveur
			try
				{
				if (device.getBondState() == BluetoothDevice.BOND_BONDED)
					{
					ParcelUuid[] uuidTab = device.getUuids();
					tmp = device.createRfcommSocketToServiceRecord(UUID_SPP);// uuidTab[0]
					// .getUuid());
					}
				else
					{
					tmp = device.createRfcommSocketToServiceRecord(UUID_SPP);
					}
				}
			catch (IOException e)
				{
				Log.e(TAG, "Socket Type: " + mSocketType + "create() failed", e);
				}
			mmSocket = tmp;
			}
		
		public void run()
			{
			Log.i(TAG, "BEGIN mConnectThread SocketType:" + mSocketType);
			setName("ConnectThread" + mSocketType);
			
			// On annule le scan pour se connecter
			mBluetoothAdapter.cancelDiscovery();
			
			// On tente la connexion
			try
				{
				// Cet appel est bloquant
				mmSocket.connect();
				}
			catch (IOException e)
				{
				// Fermeture du socket si on � pas pu
				try
					{
					mmSocket.close();
					}
				catch (IOException e2)
					{
					Log.e(TAG, "unable to close() " + mSocketType + " socket during connection failure", e2);
					}
				connectionFailed();
				return;
				}
			
			while(mmSocket.getRemoteDevice().getBondState() == BluetoothDevice.BOND_BONDING);
			
			// On termine le thread �tant donn� que nous sommes connect�s
			synchronized (SerialComBluetooth.this)
				{
				connectThread = null;
				}
			
			// On d�mmare le thread qui va g�rer notre connexion
			connected(mmSocket, mmDevice, mSocketType);
			}
		
		// En cas d'annulation
		public void cancel()
			{
			try
				{
				mmSocket.close();
				}
			catch (IOException e)
				{
				Log.e(TAG, "close() of connect " + mSocketType + " socket failed", e);
				}
			}
		}
	
	/**
	 * Ce thread g�re toute la connexion avec le bluetooth
	 */
	private class ConnectedThread extends Thread
		{
		
		private final BluetoothSocket mmSocket;
		private final InputStream mmInStream;
		private final OutputStream mmOutStream;
		
		public ConnectedThread(BluetoothSocket socket, String socketType)
			{
			Log.d(TAG, "create ConnectedThread: " + socketType);
			mmSocket = socket;
			InputStream tmpIn = null;
			OutputStream tmpOut = null;
			
			// On r�cup�re les flux d'entr�es et de sortie
			try
				{
				tmpIn = socket.getInputStream();
				tmpOut = socket.getOutputStream();
				}
			catch (IOException e)
				{
				Log.e(TAG, "temp sockets not created", e);
				}
			
			mmInStream = tmpIn;
			mmOutStream = tmpOut;
			}
		
		public void run()
			{
			Log.i(TAG, "BEGIN mConnectedThread");
			byte[] buffer = new byte[1024];
			int bytes;
			
			// On �coute se qui se passe sur le flux d'entr�e tant que nous
			// sommes connect�s
			while(true)
				{
				try
					{
					// Lecture du flux d'entr�e
					bytes = mmInStream.read(buffer);
					
					// Envois des bytes r�cup�r�s
					mHandler.obtainMessage(BluetoothConnexion.MESSAGE_READ, bytes, -1, buffer).sendToTarget();
					}
				catch (IOException e)
					{
					Log.e(TAG, "disconnected", e);
					connectionLost();
					break;
					}
				}
			}
		
		/**
		 * Ecriture dans le flux de sortie
		 * 
		 * @param buffer
		 *            The bytes to write
		 */
		public void write(byte[] buffer)
			{
			try
				{
				mmOutStream.write(buffer);
				
				}
			catch (IOException e)
				{
				Log.e(TAG, "Exception during write", e);
				}
			}
		
		public void cancel()
			{
			try
				{
				mmSocket.close();
				}
			catch (IOException e)
				{
				Log.e(TAG, "close() of connect socket failed", e);
				}
			}
		}
	
	/**
	 * This thread runs while listening for incoming connections. It behaves
	 * like a server-side client. It runs until a connection is accepted (or
	 * until cancelled).
	 */
	private class AcceptThread extends Thread
		{
		
		// The local server socket
		private final BluetoothServerSocket mmServerSocket;
		private String mSocketType;
		
		public AcceptThread()
			{
			BluetoothServerSocket tmp = null;
			mSocketType = "secure";
			// Create a new listening server socket
			try
				{
				tmp = mBluetoothAdapter.listenUsingRfcommWithServiceRecord(NAME_SECURE, UUID_SPP);
				}
			catch (IOException e)
				{
				Log.e(TAG, "Socket Type: " + mSocketType + "listen() failed", e);
				}
			mmServerSocket = tmp;
			}
		
		public void run()
			{
			if (D) Log.d(TAG, "Socket Type: " + mSocketType + "BEGIN mAcceptThread" + this);
			setName("AcceptThread" + mSocketType);
			
			BluetoothSocket socket = null;
			
			// Listen to the server socket if we're not connected
			while(mState != STATE_CONNECTED)
				{
				try
					{
					// This is a blocking call and will only return on a
					// successful connection or an exception
					socket = mmServerSocket.accept();
					}
				catch (IOException e)
					{
					Log.e(TAG, "Socket Type: " + mSocketType + "accept() failed", e);
					break;
					}
				
				// If a connection was accepted
				if (socket != null)
					{
					synchronized (SerialComBluetooth.this)
						{
						switch(mState)
							{
							case STATE_LISTEN:
							case STATE_CONNECTING:
								// Situation normal. Start the connected thread.
								connected(socket, socket.getRemoteDevice(), mSocketType);
								break;
							case STATE_NONE:
							case STATE_CONNECTED:
								// Either not ready or already connected. Terminate
								// new socket.
								try
									{
									socket.close();
									}
								catch (IOException e)
									{
									Log.e(TAG, "Could not close unwanted socket", e);
									}
								break;
							}
						}
					}
				}
			if (D) Log.i(TAG, "END mAcceptThread, socket Type: " + mSocketType);
			
			}
		
		public void cancel()
			{
			Log.d(TAG, "Socket Type" + mSocketType + "cancel " + this);
			try
				{
				mmServerSocket.close();
				}
			catch (IOException e)
				{
				Log.e(TAG, "Socket Type" + mSocketType + "close() of server failed", e);
				}
			}
		}
	
	}
