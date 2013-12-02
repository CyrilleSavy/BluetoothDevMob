
package com.example.bluetoothpicapp.bluetooth;

import java.util.List;

import com.example.bluetoothpicapp.R;

import android.content.Context;
import android.bluetooth.BluetoothDevice;
import android.content.res.ColorStateList;
import android.database.DataSetObserver;
import android.graphics.Color;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebView.FindListener;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ListAdapter;
import android.widget.TextView;

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
