
package com.example.bluetoothpicapp;

import java.util.Locale;

import android.app.ActionBar;
import android.app.ActionBar.Tab;
import android.app.FragmentTransaction;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.Menu;
import android.widget.Toast;

import com.example.bluetoothpicapp.bluetooth.BluetoothConnexion;
import com.example.bluetoothpicapp.bluetooth.SerialComBluetooth;
import com.example.bluetoothpicapp.fragment.ConnectionBluetoothFragment;
import com.example.bluetoothpicapp.fragment.LcdFragment;
import com.example.bluetoothpicapp.fragment.LedsFragment;
import com.example.bluetoothpicapp.fragment.PotBoutonsFragment;

public class ActivitePrinc extends FragmentActivity implements ActionBar.TabListener
	{
	
	/**
	 * The {@link android.support.v4.view.PagerAdapter} that will provide
	 * fragments for each of the sections. We use a
	 * {@link android.support.v4.app.FragmentPagerAdapter} derivative, which
	 * will keep every loaded fragment in memory. If this becomes too memory
	 * intensive, it may be best to switch to a
	 * {@link android.support.v4.app.FragmentStatePagerAdapter}.
	 */
	SectionsPagerAdapter mSectionsPagerAdapter;
	
	/**
	 * The {@link ViewPager} that will host the section contents.
	 */
	ViewPager mViewPager;
	
	private static BluetoothConnexion mBluetoothConnexion;
	
	private static boolean firstInit = true;
	//private static mBluetoothConnexionMem = null;
	
	public static final int MESSAGE_DEVICE_DISCOVERED = 0;
	public static final int MESSAGE_STATE_CHANGE = 1;
	public static final int MESSAGE_DISC_FINISHED = 2;
	public static final int MESSAGE_SW_RECEIVED = 3;
	public static final int MESSAGE_POT_VAL = 4;
	
	//On doit avoir un attribut pour passer les donnees au fragment
	private static ConnectionBluetoothFragment mConnFrag;
	private static LedsFragment mLedsFrag;
	private static PotBoutonsFragment mBoutonsFragment;
	
	@Override
	protected void onCreate(Bundle savedInstanceState)
		{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_activite_princ);
		
		// Set up the action bar.
		final ActionBar actionBar = getActionBar();
		actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);
		
		//Enclenchement du bluetooth
		if (firstInit)
			{
			mBluetoothConnexion = new BluetoothConnexion(getApplicationContext(), this.mHandler);
			firstInit = false;
			}
		else
			{
			mBluetoothConnexion.setHandlerMain(mHandler);
			}
		// Create the adapter that will return a fragment for each of the three
		// primary sections of the app.
		mSectionsPagerAdapter = new SectionsPagerAdapter(getSupportFragmentManager());
		
		// Set up the ViewPager with the sections adapter.
		mViewPager = (ViewPager)findViewById(R.id.pager);
		mViewPager.setAdapter(mSectionsPagerAdapter);
		
		// When swiping between different sections, select the corresponding
		// tab. We can also use ActionBar.Tab#select() to do this if we have
		// a reference to the Tab.
		mViewPager.setOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener()
			{
				
				@Override
				public void onPageSelected(int position)
					{
					actionBar.setSelectedNavigationItem(position);
					}
			});
		
		// For each of the sections in the app, add a tab to the action bar.
		for(int i = 0; i < mSectionsPagerAdapter.getCount(); i++)
			{
			// Create a tab with text corresponding to the page title defined by
			// the adapter. Also specify this Activity object, which implements
			// the TabListener interface, as the callback (listener) for when
			// this tab is selected.
			actionBar.addTab(actionBar.newTab().setText(mSectionsPagerAdapter.getPageTitle(i)).setTabListener(this));
			}
		}
	
	@Override
	public void onConfigurationChanged(Configuration newConfig)
		{
		super.onConfigurationChanged(newConfig);
		}
	
	@Override
	protected void onSaveInstanceState(Bundle SavedInstanceState)
		{
		super.onSaveInstanceState(SavedInstanceState);
		
		SavedInstanceState.putBooleanArray("LedStates", LedsFragment.getLedValues());
		SavedInstanceState.putFloat("potValue", PotBoutonsFragment.getPotValue());
		SavedInstanceState.putString("lcdTextFirstLine", LcdFragment.getLcdTextFirstLine());
		SavedInstanceState.putString("lcdTextSecondLine", LcdFragment.getLcdTextSecondLine());
		}
	
	@Override
	protected void onRestoreInstanceState(Bundle SavedInstanceState)
		{
		super.onRestoreInstanceState(SavedInstanceState);
		LedsFragment.setLedValues(SavedInstanceState.getBooleanArray("LedStates"));
		PotBoutonsFragment.setPotValue(SavedInstanceState.getFloat("potValue"));
		LcdFragment.setLcdTextFirstLine(SavedInstanceState.getString("lcdTextFirstLine"));
		LcdFragment.setLcdTextSecondLine(SavedInstanceState.getString("lcdTextSecondLine"));
		
		//On repasse l'objet bluetoothcom
		mLedsFrag.setBluetoothConn(mBluetoothConnexion);
		mConnFrag.setBluetoothConn(mBluetoothConnexion);
		
		}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu)
		{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activite_princ, menu);
		return true;
		}
	
	@Override
	public void onTabSelected(ActionBar.Tab tab, FragmentTransaction fragmentTransaction)
		{
		// When the given tab is selected, switch to the corresponding page in
		// the ViewPager.
		mViewPager.setCurrentItem(tab.getPosition());
		switch(tab.getPosition())
			{
			case 3:
				LcdFragment.setLcdTextAllowFocus(true);
				break;
			default:
				break;
			}
		}
	
	@Override
	public void onTabReselected(Tab tab, FragmentTransaction ft)
		{
		switch(tab.getPosition())
			{
			case 3:
				LcdFragment.setLcdTextAllowFocus(true);
				break;
			default:
				break;
			}
		}
	
	@Override
	public void onTabUnselected(Tab tab, FragmentTransaction ft)
		{
		switch(tab.getPosition())
			{
			case 3:
				LcdFragment.setLcdTextAllowFocus(false);
				break;
			default:
				break;
			}
		}
	
	/**
	 * A {@link FragmentPagerAdapter} that returns a fragment corresponding to
	 * one of the sections/tabs/pages.
	 */
	public class SectionsPagerAdapter extends FragmentPagerAdapter
		{
		
		public final String TAG_SECTION_PAGER_ADAPTER = SectionsPagerAdapter.class.getSimpleName();
		
		public SectionsPagerAdapter(FragmentManager fm)
			{
			super(fm);
			}
		
		@Override
		public Fragment getItem(int position)
			{
			Log.i(TAG_SECTION_PAGER_ADAPTER, "SectionsPagerAdapter.getItem()");
			// getItem is called to instantiate the fragment for the given page.
			// Return a DummySectionFragment (defined as a static inner class
			// below) with the page number as its lone argument.
			Fragment fragment;
			Bundle args = new Bundle();
			
			switch(position)
				{
				default:
					fragment = new ConnectionBluetoothFragment();
					//On passe la classe de connexion BT
					mConnFrag = (ConnectionBluetoothFragment)fragment;
					mConnFrag.setBluetoothConn(mBluetoothConnexion);
					args.putInt(ConnectionBluetoothFragment.ARG_SECTION_NUMBER, position + 1);
					
					break;
				case 1:
					fragment = new LedsFragment();
					//On passe la classe de connexion BT
					mLedsFrag = (LedsFragment)fragment;
					mLedsFrag.setBluetoothConn(mBluetoothConnexion);
					args.putInt(LedsFragment.ARG_SECTION_NUMBER, position + 1);
					break;
				case 2:
					fragment = new PotBoutonsFragment();
					mBoutonsFragment = (PotBoutonsFragment)fragment;
					args.putInt(PotBoutonsFragment.ARG_SECTION_NUMBER, position + 1);
					break;
				case 3:
					fragment = new LcdFragment();
					args.putInt(LcdFragment.ARG_SECTION_NUMBER, position + 1);
					break;
				}
			
			fragment.setArguments(args);
			return fragment;
			}
		
		@Override
		public int getCount()
			{
			// Show 4 total pages.
			return 4;
			}
		
		@Override
		public CharSequence getPageTitle(int position)
			{
			Locale l = Locale.getDefault();
			switch(position)
				{
				case 0:
					return getString(R.string.title_section0).toUpperCase(l);
				case 1:
					return getString(R.string.title_section1).toUpperCase(l);
				case 2:
					return getString(R.string.title_section2).toUpperCase(l);
				case 3:
					return getString(R.string.title_section3).toUpperCase(l);
				}
			return null;
			}
		}
	
	//Recuperation des evenements envoye par le Bluetooth
	private final Handler mHandler = new Handler()
		{
			
			@Override
			public void handleMessage(Message msg)
				{
				switch(msg.what)
					{
					case MESSAGE_STATE_CHANGE:
						switch(msg.arg1)
							{
							case SerialComBluetooth.STATE_CONNECTED:
								Toast.makeText(getApplicationContext(), "Connected", Toast.LENGTH_SHORT).show();
								break;
							case SerialComBluetooth.STATE_CONNECTING:
								Toast.makeText(getApplicationContext(), "Connecting", Toast.LENGTH_SHORT).show();
								break;
							case SerialComBluetooth.STATE_LISTEN:
								Toast.makeText(getApplicationContext(), "Listen", Toast.LENGTH_SHORT).show();
								break;
							case SerialComBluetooth.STATE_NONE:
								Toast.makeText(getApplicationContext(), "None", Toast.LENGTH_SHORT).show();
								break;
							}
						break;
					//On a decouvert un device
					case MESSAGE_DEVICE_DISCOVERED:
						//Il faut avertir le fragment
						if (mConnFrag != null)
							{
							mConnFrag.setBtDeviceDetected();
							}
						break;
					case MESSAGE_DISC_FINISHED:
						if (mConnFrag != null)
							{
							mConnFrag.endOfDiscover();
							}
						break;
					
					case MESSAGE_SW_RECEIVED:
						if (mBoutonsFragment != null)
							{
							mBoutonsFragment.setBoutonsValues(mBluetoothConnexion.getSwTab());
							}
						break;
					
					case MESSAGE_POT_VAL:
						if (mBoutonsFragment != null)
							{
							mBoutonsFragment.setPotLevelValue(mBluetoothConnexion.getPotVal());
							}
						break;
					
					default:
						;
					}
				}
		};
	
	}
