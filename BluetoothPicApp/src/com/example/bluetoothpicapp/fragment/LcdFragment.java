
package com.example.bluetoothpicapp.fragment;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.example.bluetoothpicapp.R;
import com.example.bluetoothpicapp.bluetooth.BluetoothConnexion;

/**
 * A fragment representing a section of the app, that displays the text
 * of the Lcd and could edit this text field.
 */
public class LcdFragment extends Fragment implements View.OnClickListener
	{
	
	/**
	 * The fragment argument representing the section number for this
	 * fragment.
	 */
	public static final String ARG_SECTION_NUMBER = "section_Lcd";
	
	private static TextView lcdFirstLineView;
	private static TextView lcdSecondLineView;
	private Button lcdButtonSend;
	private static String lcdFirstLineText = "";
	private static String lcdSecondLineText = "";
	private static BluetoothConnexion mBluetoothConnexion = null;
	
	public LcdFragment()
		{
		}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
		{
		View rootView = inflater.inflate(R.layout.lcd_layout, container, false);
		
		lcdFirstLineView = (EditText)rootView.findViewById(R.id.lcdLine1);
		lcdFirstLineView.setText(lcdFirstLineText);
		
		lcdButtonSend = (Button)rootView.findViewById(R.id.buttonSendLCD);
		lcdButtonSend.setOnClickListener(this);
		
		lcdSecondLineView = (EditText)rootView.findViewById(R.id.lcdLine2);
		lcdSecondLineView.setText(lcdSecondLineText);
		
		return rootView;
		}
	
	public void setBluetoothConn(BluetoothConnexion mBluetoothConnexionSrc)
		{
		mBluetoothConnexion = mBluetoothConnexionSrc;
		}
	
	public static String getLcdTextFirstLine()
		{
		if (lcdFirstLineView != null)
			{
			CharSequence aLine = lcdFirstLineView.getText();
			lcdFirstLineText = aLine.toString();
			return lcdFirstLineText;
			}
		else
			{
			return "";
			}
		}
	
	public static void setLcdTextFirstLine(String theText)
		{
		lcdFirstLineText = theText;
		lcdFirstLineView.setText(lcdFirstLineText);
		return;
		}
	
	public static String getLcdTextSecondLine()
		{
		if (lcdSecondLineView != null)
			{
			CharSequence aLine = lcdSecondLineView.getText();
			lcdSecondLineText = aLine.toString();
			return lcdSecondLineText;
			}
		else
			{
			return "";
			}
		}
	
	public static void setLcdTextSecondLine(String theText)
		{
		lcdSecondLineText = theText;
		lcdSecondLineView.setText(lcdSecondLineText);
		return;
		}
	
	public static void setLcdTextAllowFocus(boolean isAllowed)
		{
		lcdFirstLineView.setActivated(isAllowed);
		lcdSecondLineView.setActivated(isAllowed);
		
		return;
		}
	
	@Override
	public void onClick(View v)
		{
		if (mBluetoothConnexion != null)
			{
			mBluetoothConnexion.writeLcdLns(getLcdTextFirstLine(), getLcdTextSecondLine());
			}
		
		}
	}
