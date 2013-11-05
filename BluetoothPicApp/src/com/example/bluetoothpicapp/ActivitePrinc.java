
package com.example.bluetoothpicapp;

import java.util.Locale;

import com.example.bluetoothpicapp.fragment.ConnectionBluetoothFragment;
import com.example.bluetoothpicapp.fragment.LcdFragment;
import com.example.bluetoothpicapp.fragment.LedsFragment;
import com.example.bluetoothpicapp.fragment.PotBoutonsFragment;

import android.app.ActionBar;
import android.app.FragmentTransaction;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

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
	
	@Override
	protected void onCreate(Bundle savedInstanceState)
		{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_activite_princ);
		
		// Set up the action bar.
		final ActionBar actionBar = getActionBar();
		actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);
		
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
		}
	
	@Override
	public void onTabUnselected(ActionBar.Tab tab, FragmentTransaction fragmentTransaction)
		{
		}
	
	@Override
	public void onTabReselected(ActionBar.Tab tab, FragmentTransaction fragmentTransaction)
		{
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
					args.putInt(ConnectionBluetoothFragment.ARG_SECTION_NUMBER, position + 1);
					break;
				case 1:
					fragment = new LedsFragment();
					args.putInt(LedsFragment.ARG_SECTION_NUMBER, position + 1);
					break;
				case 2:
					fragment = new PotBoutonsFragment();
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
			// Show 3 total pages.
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
	
	}
