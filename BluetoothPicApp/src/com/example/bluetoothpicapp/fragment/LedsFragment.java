
package com.example.bluetoothpicapp.fragment;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.widget.SearchViewCompat.OnCloseListenerCompat;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnFocusChangeListener;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.bluetoothpicapp.R;
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
	public static final String ARG_SECTION_NUMBER = "section_LedPot";
	
	private boolean ledsState[];
	private Led ledsView[];
	
	public LedsFragment()
		{
		}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
		{
		ledsState = new boolean[8];
		ledsView = new Led[8];
		
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
			ledsState[i] = false;
			ledsView[i].setState(ledsState[i]);
			}
		
		ledsView[0].setOnFocusChangeListener(new OnFocusChangeListener()
			{
				
				@Override
				public void onFocusChange(View v, boolean hasFocus)
					{
					// TODO Auto-generated method stub
					if (hasFocus == true)
						{
						LedsFragment.this.ledsView[0].setState(LedsFragment.this.ledsState[0]);
						LedsFragment.this.ledsView[0].invalidate();
						}
					}
			});
		
		TextView dummyTextView = (TextView)rootView.findViewById(R.id.textView1);
		dummyTextView.setText("ici les leds");
		return rootView;
		}
	
	//	//TODO : trouver quelle méthode est appelée lors de la restauration du fragment
	//	@Override
	//	public void onResume()
	//		{
	//		for(int i = 0; i < 8; i++)
	//			{
	//			ledsView[i].setState(ledsState[i]);
	//			}
	//		}
	
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
			// TODO Auto-generated method stub
			if (LedsFragment.this.ledsState[LedNumber] == true)
				{
				LedsFragment.this.ledsState[LedNumber] = false;
				}
			else
				{
				LedsFragment.this.ledsState[LedNumber] = true;
				}
			
			LedsFragment.this.ledsView[LedNumber].setState(ledsState[LedNumber]);
			}
		}
	
	}
