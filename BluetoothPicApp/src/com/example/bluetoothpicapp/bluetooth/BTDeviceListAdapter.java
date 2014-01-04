
package com.example.bluetoothpicapp.bluetooth;

import java.util.Iterator;
import java.util.LinkedHashSet;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.location.GpsStatus.Listener;
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
	private boolean mConnected = false;
	private int mPosition = -1;
	
	public BTDeviceListAdapter(LinkedHashSet<BluetoothDevice> mBtDeviceList, Context context, LayoutInflater inflater)
		{
		this.mBtDeviceList = mBtDeviceList;
		this.mInflater = inflater;
		this.context = context;
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
	
	public void setConnected(boolean isConn, int pos)
		{
		mConnected = isConn;
		mPosition = pos;
		}
	
	@Override
	public View getView(int position, View convertView, ViewGroup parent)
		{
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
		
		if (mPosition == position && mConnected == true)
			{
			rootView.setBackgroundDrawable(context.getResources().getDrawable(R.drawable.listview_item_layout_connected));
			}
		
		return rootView;
		
		}
	
	}
