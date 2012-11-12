
package chronotext.android.cinder;

import javax.microedition.khronos.opengles.GL10;

import chronotext.android.gl.GLRenderer;

import android.content.Context;
import android.content.res.AssetManager;

public class CinderRenderer extends GLRenderer
{
  public static final int EVENT_ATTACHED = 1;
  public static final int EVENT_DETACHED = 2;
  public static final int EVENT_PAUSE = 3;
  public static final int EVENT_RESUME = 4;
  public static final int EVENT_DESTROYED = 5;

  Context context;

  public CinderRenderer(Context context)
  {
    this.context = context;
  }

  public void start()
  {
    start(context.getAssets());
  }

  public void attached()
  {
    event(EVENT_ATTACHED);
  }

  public void detached()
  {
    event(EVENT_DETACHED);
  }

  public void pause()
  {
    resumed = false;
    event(EVENT_PAUSE);
  }

  public void resume()
  {
    resumed = true;
    event(EVENT_RESUME);
  }

  public void destroyed()
  {
    destroyed = true;
    event(EVENT_DESTROYED);
  }

  public void init(GL10 gl, int width, int height)
  {
    init(width, height);
  }

  public void draw(GL10 gl)
  {
    draw();
  }

  // ---------------------------------------- JNI ----------------------------------------

  public native void start(AssetManager assets);

  public native void event(int id);

  public native void init(int width, int height);

  public native void draw();

  public native void addTouch(float x, float y);

  public native void updateTouch(float x, float y);

  public native void removeTouch(float x, float y);
}
