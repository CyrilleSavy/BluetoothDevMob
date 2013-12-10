
package com.example.bluetoothpicapp.bluetooth;

import java.util.Iterator;
import java.util.LinkedHashSet;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ListAdapter;
import android.widget.TextView;

import com.example.bluetoothpicapp.R;

public class BTDeviceListAdapter extends BaseAdapter implements ListAdapter
	{
	
	// Input
	private LinkedHashSet<BluetoothDevice> mBtDeviceList;
	private Context context;
	
	private LayoutInflater mInflater;
	
	public BTDeviceListAdapter(LinkedHashSet<BluetoothDevice> mBtDeviceList, Context context, LayoutInflater inflater)
		{
		this.mBtDeviceList = mBtDeviceList;
		this.mInflater = inflater;
		}
	
	@Override
	public int getCount()
		{
		return this.mBtDeviceList.size();
		}
	
	@Override
	public Object getItem(int position)
		{
		Iterator<BluetoothDevice> i = this.mBtDeviceList.iterator(); // on crée un Iterator pour parcourir notre HashSet
		for(int j = 0; (j < position) && (i.hasNext()); j++)
			{
			i.next();
			}
		return i.next();
		//return this.mBtDeviceList.get(position);
		}
	
	@Override
	public long getItemId(int position)
		{
		// TODO Auto-generated method stub
		return 0;
		}
	
	public void setList(LinkedHashSet<BluetoothDevice> mBtDeviceList)
		{
		this.mBtDeviceList = mBtDeviceList;
		}
	
	public void clearList()
		{
		this.mBtDeviceList.clear();
		}
	
	@Override
	public View getView(int position, View convertView, ViewGroup parent)
		{
		//LayoutInflater mInflater = (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View rootView = mInflater.inflate(R.layout.bt_dev_disc, parent, false);
		
		Iterator<BluetoothDevice> i = this.mBtDeviceList.iterator(); // on crée un Iterator pour parcourir notre HashSet
		for(int j = 0; (j < position) && (i.hasNext()); j++)
			{
			i.next();
			}
		BluetoothDevice temp = i.next();
		String aDeviceName = temp.getName();
		String aDeviceMac = temp.getAddress();
		
		TextView aBtDeviceName = (TextView)rootView.findViewById(R.id.elemListBtDisco_Name);
		aBtDeviceName.setText(aDeviceName);
		TextView aBtDeviceMac = (TextView)rootView.findViewById(R.id.elemListBtDisco_MAC);
		aBtDeviceMac.setText(aDeviceMac);
		
		return rootView;
		
		}
	
	}
