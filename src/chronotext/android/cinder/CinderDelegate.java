
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

/*
 * WARNING: BE SURE TO DEFINE android:screenOrientation IN THE MANIFEST
 * BECAUSE THE CURRENT SYSTEM IS NOT HANDLING AUTO-ROTATION
 */

public class CinderDelegate implements SensorEventListener
{
  public static final int ACCELEROMETER_ORIENTATION_DEFAULT = 0;
  public static final int ACCELEROMETER_ORIENTATION_PORTRAIT = 1;
  public static final int ACCELEROMETER_ORIENTATION_LANDSCAPE = 2;

  protected Activity mActivity;
  protected Handler mHandler;

  protected GLView mView;

  protected SensorManager mSensorManager;
  protected Sensor mAccelerometerSensor;
  protected int mAccelerometerOrientation;

  public CinderDelegate(Activity activity, Handler handler)
  {
    mActivity = activity;
    mHandler = handler;

    initAccelerometer();

    mView = new GLView(activity);
    mView.setRenderer(new CinderRenderer(activity, this)); // WILL START THE RENDERER'S THREAD
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
  {}

  @Override
  public void onSensorChanged(SensorEvent event)
  {
    if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER)
    {
      float x = event.values[0];
      float y = event.values[1];
      float z = event.values[2];

      /*
       * APPLYING THE EVENTUAL ORIENTATION FIX
       */
      if (mAccelerometerOrientation == ACCELEROMETER_ORIENTATION_LANDSCAPE)
      {
        float tmp = x;
        x = -y;
        y = +tmp;
      }
      else if (mAccelerometerOrientation == ACCELEROMETER_ORIENTATION_PORTRAIT)
      {
        float tmp = x;
        x = +y;
        y = -tmp;
      }

      /*
       * FOR CONSISTENCY WITH iOS
       */
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
      mSensorManager.registerListener(this, mAccelerometerSensor, SensorManager.SENSOR_DELAY_GAME); // SOME SAY IT CORRESPONDS TO AN updateFrequency OF 50
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

  protected void initAccelerometer()
  {
    mSensorManager = (SensorManager) mActivity.getSystemService(Context.SENSOR_SERVICE);
    mAccelerometerSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);

    /*
     * THE FOLLOWING IS BASED ON CODE FROM Cocos2dxAccelerometer.java
     * Copyright (c) 2010-2011 cocos2d-x.org 
     * http://www.cocos2d-x.org
     */

    int orientation = mActivity.getResources().getConfiguration().orientation;

    Display display = ((WindowManager) mActivity.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay();
    int naturalOrientation = display.getOrientation();

    if ((orientation == Configuration.ORIENTATION_LANDSCAPE) && (naturalOrientation != Surface.ROTATION_0))
    {
      mAccelerometerOrientation = ACCELEROMETER_ORIENTATION_LANDSCAPE;
    }
    else if ((orientation == Configuration.ORIENTATION_PORTRAIT) && (naturalOrientation != Surface.ROTATION_0))
    {
      mAccelerometerOrientation = ACCELEROMETER_ORIENTATION_PORTRAIT;
    }
    else
    {
      mAccelerometerOrientation = ACCELEROMETER_ORIENTATION_DEFAULT;
    }
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
