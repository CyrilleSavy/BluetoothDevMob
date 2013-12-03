
package com.example.bluetoothpicapp.bluetooth;

import java.util.List;

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
	private List<BluetoothDevice> mBtDeviceList;
	private Context context;
	
	private LayoutInflater mInflater;
	
	public BTDeviceListAdapter(List<BluetoothDevice> mBtDeviceList, Context context, LayoutInflater inflater)
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
		return this.mBtDeviceList.get(position);
		}
	
	@Override
	public long getItemId(int position)
		{
		// TODO Auto-generated method stub
		return 0;
		}
	
	public void setList(List<BluetoothDevice> mBtDeviceList)
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
		
		String aDeviceName = this.mBtDeviceList.get(position).getName();
		String aDeviceMac = this.mBtDeviceList.get(position).getAddress();
		
		TextView aBtDeviceName = (TextView)rootView.findViewById(R.id.elemListBtDisco_Name);
		aBtDeviceName.setText(aDeviceName);
		TextView aBtDeviceMac = (TextView)rootView.findViewById(R.id.elemListBtDisco_MAC);
		aBtDeviceMac.setText(aDeviceMac);
		
		return rootView;
		
		}
	
	}
