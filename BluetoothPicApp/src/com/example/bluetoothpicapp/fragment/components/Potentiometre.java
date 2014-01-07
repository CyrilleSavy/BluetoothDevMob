
package com.example.bluetoothpicapp.fragment.components;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
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
	
	private int mSizeHeight;
	private int mSizeWidth;
	
	//infos pour la rotation :
	private static final int middleOfHeight = 136;
	private static final int middleOfWidth = 127;
	
	private int mMiddleOfHeight;
	private int mMiddleOfWidth;
	
	private static final int offsetAngle = 136;//mesure sur l'image
	private static final int excursionAngle = 271;//mesure sur l'image
	private Bitmap imageRotation;
	private DisplayMetrics metrics;
	
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
		if (this.metrics != null)
			{
			this.mSizeHeight = (int)(sizeHeight * this.metrics.scaledDensity);
			this.mSizeWidth = (int)(sizeWidth * this.metrics.scaledDensity);
			this.mMiddleOfHeight = (int)(middleOfHeight * this.metrics.scaledDensity);
			this.mMiddleOfWidth = (int)(middleOfWidth * this.metrics.scaledDensity);
			}
		else
			{
			this.mSizeHeight = (int)(sizeHeight);
			this.mSizeWidth = (int)(sizeWidth);
			this.mMiddleOfHeight = this.mSizeHeight / 2;
			this.mMiddleOfWidth = this.mSizeWidth / 2;
			}
		imageRotation = BitmapFactory.decodeResource(getResources(), R.drawable.pot_int);
		imageRotation = Bitmap.createScaledBitmap(imageRotation, mSizeWidth, mSizeHeight, false);
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
		setMeasuredDimension(mSizeWidth, mSizeHeight);
		}
	
	@SuppressWarnings("deprecation")
	@Override
	protected void onDraw(Canvas canvas)
		{
		this.setBackgroundDrawable(getResources().getDrawable(R.drawable.pot_ext));//image de fond
		
		canvas.rotate((this.potLevel * excursionAngle) - offsetAngle, mMiddleOfWidth, mMiddleOfHeight);
		canvas.drawBitmap(imageRotation, 0, 0, null);
		}
	
	public void setMetrics(DisplayMetrics metrics)
		{
		this.metrics = metrics;
		init();
		}
	
	}
