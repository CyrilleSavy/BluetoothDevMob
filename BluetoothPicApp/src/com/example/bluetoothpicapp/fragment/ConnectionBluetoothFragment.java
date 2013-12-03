
package com.example.bluetoothpicapp.fragment;

import java.util.ArrayList;
import java.util.List;

import android.bluetooth.BluetoothDevice;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.ListView;

import com.example.bluetoothpicapp.R;
import com.example.bluetoothpicapp.bluetooth.BTDeviceListAdapter;
import com.example.bluetoothpicapp.bluetooth.BTSearchDiag;
import com.example.bluetoothpicapp.bluetooth.BluetoothConnexion;

/**
 * A fragment representing a section of the app, that displays the text
 * of the Lcd and could edit this text field.
 */
public class ConnectionBluetoothFragment extends Fragment implements View.OnClickListener ,OnItemClickListener
	{
	
	/**
	 * The fragment argument representing the section number for this
	 * fragment.
	 */
	public static final String ARG_SECTION_NUMBER = "section_Bluetooth";
	
	private List<BluetoothDevice> mDiscoveredDevice;
	private static BluetoothConnexion mBluetoothConnexion = null;
	
	private Button btScan;
	private ListView btDeviceLstView;
	
	private BTDeviceListAdapter mBTDeviceListAdapter;
	
	//Scanning  progress dialog
	private BTSearchDiag mBtSearchDiag;
	
	public ConnectionBluetoothFragment()
		{
		//this.mBluetoothConnexion = null;
		this.btScan = null;
		this.mDiscoveredDevice = new ArrayList<BluetoothDevice>();
		}
	
	public void setBluetoothConn(BluetoothConnexion mBluetoothConnexionSrc)
		{
		mBluetoothConnexion = mBluetoothConnexionSrc;
		}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
		{
		View rootView = inflater.inflate(R.layout.connection_bluetooth_layout, container, false);
		btScan = (Button)rootView.findViewById(R.id.buttonScan);
		btScan.setOnClickListener(this);
		
		btDeviceLstView = (ListView)rootView.findViewById(R.id.listViewDevices);
		btDeviceLstView.setOnItemClickListener(this);
		mBTDeviceListAdapter = new BTDeviceListAdapter(mDiscoveredDevice, getActivity().getApplicationContext(), inflater);
		btDeviceLstView.setAdapter(mBTDeviceListAdapter);
		
		return rootView;
		}
	
	@Override
	public void onResume()
		{
		super.onResume();
		}
	
	public void setBtDeviceDetected()
		{
		//On récupère la liste
		this.mDiscoveredDevice = mBluetoothConnexion.getDiscoveredDevices();
		//btDeviceLstView.setAdapter(mBTDeviceListAdapter);
		this.mBTDeviceListAdapter.setList(this.mDiscoveredDevice);
		this.mBTDeviceListAdapter.notifyDataSetChanged();
		}
	
	public void endOfDiscover()
		{
		if (this.mBtSearchDiag != null)
			{
			this.mBtSearchDiag.dismiss();
			}
		}
	
	//Si l'on a clické sur le bouton on lance le scan
	@Override
	public void onClick(View v)
		{
		this.mBTDeviceListAdapter.clearList();
		//On démmare le scan
		if (mBluetoothConnexion != null) //Evite une source de bugs
			{
			showScanDialog();
			mBluetoothConnexion.startDiscovery();
			}
		}
	
	//Si on veut se connecter sur un périphérique
	@Override
	public void onItemClick(AdapterView<?> arg0, View arg1, int position, long arg3)
		{
		mBluetoothConnexion.connect(this.mDiscoveredDevice.get(position));
		}
	
	private void showScanDialog()
		{
		FragmentManager fm = getFragmentManager();
		this.mBtSearchDiag = new BTSearchDiag();
		this.mBtSearchDiag.show(fm, "fragment_edit_name");
		}
	}
