
package com.example.bluetoothpicapp.fragment;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.bluetoothpicapp.R;

/**
 * A fragment representing a section of the app, that displays the text
 * of the Lcd and could edit this text field.
 */
public class ConnectionBluetoothFragment extends Fragment
	{
	
	/**
	 * The fragment argument representing the section number for this
	 * fragment.
	 */
	public static final String ARG_SECTION_NUMBER = "section_Bluetooth";
	
	public ConnectionBluetoothFragment()
		{
		}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
		{
		View rootView = inflater.inflate(R.layout.connection_bluetooth_layout, container, false);
		TextView dummyTextView = (TextView)rootView.findViewById(R.id.textView0);
		dummyTextView.setText("ici la connection bluetooth");
		return rootView;
		}
	}
