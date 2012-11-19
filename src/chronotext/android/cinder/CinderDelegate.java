
package chronotext.android.cinder;

import android.app.Activity;
import android.content.Context;
import android.content.res.Configuration;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Handler;
import android.os.Message;
import android.view.Display;
import android.view.Surface;
import android.view.View;
import android.view.WindowManager;
import chronotext.android.gl.GLView;

public class CinderDelegate implements SensorEventListener
{
  protected Activity mActivity;
  protected Handler mHandler;

  protected GLView mView;

  protected SensorManager mSensorManager;
  protected Sensor mAccelerometerSensor;
  protected int mNaturalOrientation;

  public CinderDelegate(Activity activity, Handler handler)
  {
    mActivity = activity;
    mHandler = handler;

    mView = new GLView(activity);
    mView.setRenderer(new CinderRenderer(activity, this)); // WILL START THE RENDERER'S THREAD

    // ---

    mSensorManager = (SensorManager) activity.getSystemService(Context.SENSOR_SERVICE);
    mAccelerometerSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);

    Display display = ((WindowManager) activity.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay();
    mNaturalOrientation = display.getOrientation();
  }

  public GLView getView()
  {
    return mView;
  }

  public void showView()
  {
    if (mView.getVisibility() == View.GONE)
    {
      mView.setVisibility(View.VISIBLE);
    }
  }

  public void hideView()
  {
    if (mView.getVisibility() == View.VISIBLE)
    {
      mView.setVisibility(View.GONE);
    }
  }

  // ---------------------------------------- TO BE CALLED FROM THE HOST ACTIVITY ----------------------------------------

  public void onPause()
  {
    mView.onPause();
  }

  public void onResume()
  {
    mView.onResume();
  }

  public void onDestroy()
  {
    mView.onDestroy();
  }

  // ---------------------------------------- ACCELEROMETER ----------------------------------------

  @Override
  public void onAccuracyChanged(Sensor sensor, int accuracy)
  {
    System.out.println("********** onAccuracyChanged: " + sensor + " - " + accuracy + " **********");
  }

  @Override
  public void onSensorChanged(SensorEvent event)
  {
    if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER)
    {
      float x = event.values[0];
      float y = event.values[1];
      float z = event.values[2];

      /*
       * THE FOLLOWING IS FROM Cocos2dxAccelerometer.java
       * Copyright (c) 2010-2011 cocos2d-x.org 
       * http://www.cocos2d-x.org
       */
      
      int orientation = mActivity.getResources().getConfiguration().orientation;

      if ((orientation == Configuration.ORIENTATION_LANDSCAPE) && (mNaturalOrientation != Surface.ROTATION_0))
      {
        float tmp = x;
        x = -y;
        y = tmp;
      }
      else if ((orientation == Configuration.ORIENTATION_PORTRAIT) && (mNaturalOrientation != Surface.ROTATION_0))
      {
        float tmp = x;
        x = y;
        y = -tmp;
      }
      
      // ---
      
      x /= -SensorManager.GRAVITY_EARTH;
      y /= +SensorManager.GRAVITY_EARTH;
      z /= +SensorManager.GRAVITY_EARTH;
      
      mView.accelerated(x, y, z);
    }
  }

  public void enableAccelerometer(float updateFrequency)
  {
    if (android.os.Build.VERSION.SDK_INT < 11)
    {
      mSensorManager.registerListener(this, mAccelerometerSensor, SensorManager.SENSOR_DELAY_GAME); // CORRESPONDS TO AN updateFrequency OF 50
    }
    else
    {
      mSensorManager.registerListener(this, mAccelerometerSensor, (int) (1000000 / updateFrequency));
    }
  }

  public void disableAccelerometer()
  {
    mSensorManager.unregisterListener(this);
  }

  // ---------------------------------------- MESSAGING SYSTEM ----------------------------------------

  /*
   * THIS WILL BE SENT ON THE RENDERER'S THREAD
   */
  public void sendMessage(int what, String body)
  {
    mView.sendMessage(what, body);
  }

  /*
   * THIS IS RECEIVED ON THE RENDERER'S THREAD
   */
  public void handleMessage(int what, String body)
  {
    mHandler.sendMessage(Message.obtain(mHandler, what, body));
  }
}
