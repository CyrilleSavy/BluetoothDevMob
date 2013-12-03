
package com.example.bluetoothpicapp.bluetooth;

import com.example.bluetoothpicapp.R;

import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.FragmentManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

public class BTSearchDiag extends DialogFragment
	{
	
	public BTSearchDiag()
		{
		
		}
	
	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState)
		{
		AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
		LayoutInflater inflater = getActivity().getLayoutInflater();
		View view = inflater.inflate(R.layout.scan_prog_diag, null);
		builder.setView(view);
		return builder.create();
		}
	
	}
