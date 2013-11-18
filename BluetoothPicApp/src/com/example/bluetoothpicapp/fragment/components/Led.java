
package com.example.bluetoothpicapp.fragment.components;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Canvas;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.widget.Button;

import com.example.bluetoothpicapp.R;

public class Led extends Button
	{
	
	private boolean ledState = false;
	private static final int size = 36;
	
	public Led(Context context, AttributeSet attrs, int defStyle)
		{
		super(context, attrs, defStyle);
		// TODO Auto-generated constructor stub
		init();
		}
	
	public Led(Context context, AttributeSet attrs)
		{
		super(context, attrs);
		// TODO Auto-generated constructor stub
		init();
		}
	
	public Led(Context context)
		{
		super(context);
		// TODO Auto-generated constructor stub
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
			this.setBackgroundDrawable(getResources().getDrawable(R.drawable.led_blue_hi_48p));
			}
		else
			{
			this.setBackgroundDrawable(getResources().getDrawable(R.drawable.led_blue_lo_48p));
			}
		// Ne pas oublier
		//super.onDraw(canvas);
		}
	}
