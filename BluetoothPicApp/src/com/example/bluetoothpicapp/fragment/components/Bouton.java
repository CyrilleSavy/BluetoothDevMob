
package com.example.bluetoothpicapp.fragment.components;

import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.widget.Button;

import com.example.bluetoothpicapp.R;

public class Bouton extends Button
	{
	
	private boolean buttonState = false;
	private static final int sizeHeight = 64;
	private static final int sizeWidth = 45;
	
	public Bouton(Context context, AttributeSet attrs, int defStyle)
		{
		super(context, attrs, defStyle);
		init();
		}
	
	public Bouton(Context context, AttributeSet attrs)
		{
		super(context, attrs);
		init();
		}
	
	public Bouton(Context context)
		{
		super(context);
		init();
		}
	
	private void init()
		{
		this.setHeight(Bouton.sizeHeight);
		this.setWidth(Bouton.sizeWidth);
		this.setClickable(false);
		}
	
	public void setState(boolean state)
		{
		buttonState = state;
		
		// Redessine la vue
		invalidate();
		}
	
	@SuppressWarnings("deprecation")
	@Override
	protected void onDraw(Canvas canvas)
		{
		// Dessine l'image
		if (buttonState == true)
			{
			this.setBackgroundDrawable(getResources().getDrawable(R.drawable.switch_lo_64p));
			}
		else
			{
			this.setBackgroundDrawable(getResources().getDrawable(R.drawable.switch_hi_64p));
			}
		}
	}
