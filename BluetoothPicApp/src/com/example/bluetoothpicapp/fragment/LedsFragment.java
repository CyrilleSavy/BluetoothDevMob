
package com.example.bluetoothpicapp.fragment;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.bluetoothpicapp.R;

/**
 * A fragment representing a section of the app, that displays the value
 * of the Leds and could set or clear these values.
 */
public class LedsFragment extends Fragment
	{
	
	/**
	 * The fragment argument representing the section number for this
	 * fragment.
	 */
	public static final String ARG_SECTION_NUMBER = "section_LedPot";
	
	public LedsFragment()
		{
		}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
		{
		View rootView = inflater.inflate(R.layout.leds_layout, container, false);
		TextView dummyTextView = (TextView)rootView.findViewById(R.id.textView1);
		dummyTextView.setText("ici les leds");
		return rootView;
		}
	}
