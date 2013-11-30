
package com.example.bluetoothpicapp.fragment;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;

import com.example.bluetoothpicapp.ActivitePrinc;
import com.example.bluetoothpicapp.R;
import com.example.bluetoothpicapp.bluetooth.BluetoothConnexion;
import com.example.bluetoothpicapp.fragment.components.Led;

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
	public static final String ARG_SECTION_NUMBER = "section_Leds";
	
	private static boolean ledsState[] = new boolean[8];
	private static Led ledsView[] = new Led[8];
	
	private static BluetoothConnexion mBluetoothConnexion = null;
	
	public LedsFragment()
		{
		//mBluetoothConnexion = null ;
		for(int i = 0; i < 8; i++)
			{
			ledsState[i] = false;
			}
		}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
		{
		View rootView = inflater.inflate(R.layout.leds_layout, container, false);
		
		ledsView[0] = (Led)rootView.findViewById(R.id.led1);
		ledsView[1] = (Led)rootView.findViewById(R.id.led2);
		ledsView[2] = (Led)rootView.findViewById(R.id.led3);
		ledsView[3] = (Led)rootView.findViewById(R.id.led4);
		ledsView[4] = (Led)rootView.findViewById(R.id.led5);
		ledsView[5] = (Led)rootView.findViewById(R.id.led6);
		ledsView[6] = (Led)rootView.findViewById(R.id.led7);
		ledsView[7] = (Led)rootView.findViewById(R.id.led8);
		
		for(int i = 0; i < 8; i++)
			{
			ledsView[i].setOnClickListener(new OnLedClickListener(i));
			ledsView[i].setState(ledsState[i]);
			}
		
		return rootView;
		}
	
	public void setBluetoothConn(BluetoothConnexion mBluetoothConnexionSrc)
		{
		mBluetoothConnexion = mBluetoothConnexionSrc;
		}
	
	public static boolean[] getLedValues()
		{
		boolean theValues[] = new boolean[8];
		
		for(int i = 0; i < 8; i++)
			{
			theValues[i] = ledsState[i];
			}
		
		return theValues;
		}
	
	public static void setLedValues(boolean theValues[])
		{
		for(int i = 0; i < 8; i++)
			{
			ledsState[i] = theValues[i];
			ledsView[i].setState(ledsState[i]);
			}
		
		return;
		}
	
	public class OnLedClickListener implements OnClickListener
		{
		
		private int LedNumber;
		
		OnLedClickListener(int LedNumber)
			{
			this.LedNumber = LedNumber;
			}
		
		@Override
		public void onClick(View v)
			{
			if (LedsFragment.ledsState[LedNumber] == true)
				{
				LedsFragment.ledsState[LedNumber] = false;
				//Source de bug
				if(mBluetoothConnexion != null)
					{
					mBluetoothConnexion.writeLed((char)LedNumber, (char)0);
					}
				}
			else
				{
				LedsFragment.ledsState[LedNumber] = true;
				//Source de bug
				if(mBluetoothConnexion != null)
					{
					mBluetoothConnexion.writeLed((char)LedNumber, (char)1);
					}
				}
			
			LedsFragment.ledsView[LedNumber].setState(ledsState[LedNumber]);
			}
		}
	
	}
