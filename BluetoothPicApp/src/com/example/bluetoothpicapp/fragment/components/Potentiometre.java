
package com.example.bluetoothpicapp.fragment.components;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.view.View;

import com.example.bluetoothpicapp.R;

@SuppressLint("NewApi")
public class Potentiometre extends View
	{
	
	//niveau du potentiometre
	private float potLevel;
	
	//infos sur l'image
	private static final int sizeHeight = 256;
	private static final int sizeWidth = 256;
	
	//infos pour la rotation :
	private static final int middleOfHeight = 136;
	private static final int middleOfWidth = 127;
	private static final int offsetAngle = 136;//mesure sur l'image
	private static final int excursionAngle = 271;//mesure sur l'image
	private Bitmap imageRotation;
	
	public Potentiometre(Context context, AttributeSet attrs, int defStyle)
		{
		super(context, attrs, defStyle);
		init();
		}
	
	public Potentiometre(Context context, AttributeSet attrs)
		{
		super(context, attrs);
		init();
		}
	
	public Potentiometre(Context context)
		{
		super(context);
		init();
		this.setMinimumHeight(sizeHeight);
		this.setMinimumWidth(sizeWidth);
		}
	
	private void init()
		{
		imageRotation = BitmapFactory.decodeResource(getResources(), R.drawable.pot_int);
		imageRotation = Bitmap.createScaledBitmap(imageRotation, sizeWidth, sizeHeight, false);
		this.potLevel = 0;
		this.setClickable(false);
		}
	
	public void setPotLevel(float level)
		{
		this.potLevel = level;
		
		// Redessine la vue
		invalidate();
		}
	
	@Override
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec)
		{
		setMeasuredDimension(sizeWidth, sizeHeight);
		}
	
	@SuppressWarnings("deprecation")
	@Override
	protected void onDraw(Canvas canvas)
		{
		if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.JELLY_BEAN_MR2)
			{
			this.setBackground(getResources().getDrawable(R.drawable.pot_ext));
			}
		else
			{
			this.setBackgroundDrawable(getResources().getDrawable(R.drawable.pot_ext));//image de fond
			}
		canvas.rotate((this.potLevel * excursionAngle) - offsetAngle, middleOfWidth, middleOfHeight);
		canvas.drawBitmap(imageRotation, 0, 0, null);
		}
	
	}
