
package com.example.bluetoothpicapp.fragment;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.example.bluetoothpicapp.R;
import com.example.bluetoothpicapp.fragment.components.Bouton;
import com.example.bluetoothpicapp.fragment.components.Potentiometre;

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
	public static final String ARG_SECTION_NUMBER = "section_BoutonsPot";
	
	private static boolean boutonsState[] = new boolean[4];
	private static Bouton boutonsView[] = new Bouton[4];
	private static float potLevel;
	private static Potentiometre potView;
	
	public PotBoutonsFragment()
		{
		for(int i = 0; i < 4; i++)
			{
			boutonsState[i] = false;
			}
		
		potLevel = (float)0.0;
		}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
		{
		View rootView = inflater.inflate(R.layout.pots_boutons_layout, container, false);
		
		boutonsView[0] = (Bouton)rootView.findViewById(R.id.bouton1);
		boutonsView[1] = (Bouton)rootView.findViewById(R.id.bouton2);
		boutonsView[2] = (Bouton)rootView.findViewById(R.id.bouton3);
		boutonsView[3] = (Bouton)rootView.findViewById(R.id.bouton4);
		
		potView = (Potentiometre)rootView.findViewById(R.id.potentiometre1);
		potView.setPotLevel(potLevel);
		return rootView;
		}
	
	public static boolean[] getBoutonsValues()
		{
		boolean theValues[] = new boolean[4];
		
		for(int i = 0; i < 4; i++)
			{
			theValues[i] = boutonsState[i];
			}
		
		return theValues;
		}
	
	public static void setBoutonsValues(boolean theValues[])
		{
		for(int i = 0; i < 4; i++)
			{
			boutonsState[i] = theValues[i];
			boutonsView[i].setState(boutonsState[i]);
			}
		
		return;
		}
	
	public static float getPotValue()
		{
		return potLevel;
		}
	
	/**
	 * Called when PIC sends the pot value
	 * @param theValue
	 */
	public static void setPotLevelValue(int theValue)
		{
		float aVal = (float)((float)theValue/100.0);
		potLevel = aVal;
		potView.setPotLevel(potLevel);
		}
	
	public static void setPotValue(float theValue)
		{
		potLevel = theValue;
		return;
		}
	
	}
