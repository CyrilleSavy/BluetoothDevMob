
package com.example.bluetoothpicapp.fragment.components;

import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.widget.Button;

import com.example.bluetoothpicapp.R;

public class Led extends Button
	{
	
	private boolean ledState = false;
	private static final int size = 48;
	
	public Led(Context context, AttributeSet attrs, int defStyle)
		{
		super(context, attrs, defStyle);
		init();
		}
	
	public Led(Context context, AttributeSet attrs)
		{
		super(context, attrs);
		init();
		}
	
	public Led(Context context)
		{
		super(context);
		init();
		}
	
	private void init()
		{
		this.setHeight(Led.size);
		this.setWidth(Led.size);
		}
	
	public void setState(boolean state)
		{
		ledState = state;
		
		// Redessine la vue
		invalidate();
		}
	
	@SuppressWarnings("deprecation")
	@Override
	protected void onDraw(Canvas canvas)
		{
		// Dessine l'image
		if (ledState == true)
			{
			this.setBackgroundDrawable(getResources().getDrawable(R.drawable.led_green_hi_48p));
			}
		else
			{
			this.setBackgroundDrawable(getResources().getDrawable(R.drawable.led_green_lo_48p));
			}
		}
	}
