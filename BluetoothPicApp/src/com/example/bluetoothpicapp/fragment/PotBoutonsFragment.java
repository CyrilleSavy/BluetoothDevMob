
package com.example.bluetoothpicapp.fragment;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.bluetoothpicapp.R;

/**
 * A fragment representing a section of the app, that simply displays the value
 * of the potentiometer and the state of the buttons.
 */
public class PotBoutonsFragment extends Fragment
	{
	
	/**
	 * The fragment argument representing the section number for this
	 * fragment.
	 */
	public static final String ARG_SECTION_NUMBER = "section_LedPot";
	
	public PotBoutonsFragment()
		{
		}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
		{
		View rootView = inflater.inflate(R.layout.pots_boutons_layout, container, false);
		TextView dummyTextView = (TextView)rootView.findViewById(R.id.textView2);
		dummyTextView.setText("ici le pot et les boutons");
		return rootView;
		}
	}
