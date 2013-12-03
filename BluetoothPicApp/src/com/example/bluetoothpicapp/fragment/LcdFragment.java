
package com.example.bluetoothpicapp.fragment;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;

import com.example.bluetoothpicapp.R;

/**
 * A fragment representing a section of the app, that displays the text
 * of the Lcd and could edit this text field.
 */
public class LcdFragment extends Fragment
	{
	
	/**
	 * The fragment argument representing the section number for this
	 * fragment.
	 */
	public static final String ARG_SECTION_NUMBER = "section_Lcd";
	
	private static TextView lcdFirstLineView;
	private static TextView lcdSecondLineView;
	private static String lcdFirstLineText = "";
	private static String lcdSecondLineText = "";
	
	public LcdFragment()
		{
		}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
		{
		View rootView = inflater.inflate(R.layout.lcd_layout, container, false);
		
		lcdFirstLineView = (EditText)rootView.findViewById(R.id.lcdLine1);
		lcdFirstLineView.setText(lcdFirstLineText);
		
		lcdSecondLineView = (EditText)rootView.findViewById(R.id.lcdLine2);
		lcdSecondLineView.setText(lcdSecondLineText);
		
		return rootView;
		}
	
	public static String getLcdTextFirstLine()
		{
		return lcdFirstLineText;
		}
	
	public static void setLcdTextFirstLine(String theText)
		{
		lcdFirstLineText = theText;
		
		return;
		}
	
	public static String getLcdTextSecondLine()
		{
		return lcdSecondLineText;
		}
	
	public static void setLcdTextSecondLine(String theText)
		{
		lcdSecondLineText = theText;
		
		return;
		}
	
	public static void setLcdTextAllowFocus(boolean isAllowed)
		{
		lcdFirstLineView.setActivated(isAllowed);
		lcdSecondLineView.setActivated(isAllowed);
		
		return;
		}
	}
