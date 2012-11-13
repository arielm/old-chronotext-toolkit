
package chronotext.android.gl;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

public abstract class GLRenderer implements GLSurfaceView.Renderer
{
  int ticks;
  long t0;
  long now;
  long elapsed;

  protected boolean initialized;
  protected boolean attached;
  protected boolean resumed;
  protected boolean destroyed;

  public void onSurfaceCreated(GL10 gl, EGLConfig config)
  {
    /*
     * WE DON'T CALL init() FROM HERE BECAUSE WE WANT TO KNOW THE SURFACE-SIZE FIRST
     */

    if (initialized)
    {
      resume();
    }
    else
    {
      launch();
    }
  }

  public void onSurfaceChanged(GL10 gl, int w, int h)
  {
    if (!initialized)
    {
      init(gl, w, h);
      initialized = true;
    }

    if (!attached)
    {
      attached();
      attached = true;
    }
  }

  public void onDrawFrame(GL10 gl)
  {
    now = System.currentTimeMillis();

    if (ticks == 0)
    {
      t0 = now;
    }

    ticks++;
    elapsed = now - t0;

    // ---

    draw(gl);
  }

  // ---------------------------------------- QUEUED EVENTS, INITIALLY RECEIVED ON THE UI-THREAD ----------------------------------------

  public void onAttachedToWindow()
  {
    ticks = 0;

    if (initialized && !resumed)
    {
      attached();
      attached = true;
    }
  }

  public void onDetachedFromWindow()
  {
    if (!destroyed)
    {
      detached();
      attached = false;
    }
  }

  public void onResume()
  {
    ticks = 0;

    /*
     * AT THIS STAGE, THE SURFACE HAS NOT BEEN RE-CREATED YET
     * SO, WE DON'T CALL resume() HERE BUT IN onSurfaceCreated()
     */
  }

  public void onPause()
  {
    System.out.printf("AVERAGE FRAME-RATE: %f FRAMES PER SECOND\n", ticks / (elapsed / 1000f));

    /*
     * AT THIS STAGE, THE SURFACE HAS BEEN ALREADY DESTROYED,
     * WHICH IS NOT SUPPOSED TO BE AN ISSUE...
     */
    pause();
  }

  public void onDestroy()
  {
    destroyed();
  }

  // ---------------------------------------- ABSTRACT METHODS ----------------------------------------

  public abstract void launch();

  public abstract void init(GL10 gl, int width, int height);

  public abstract void draw(GL10 gl);

  public abstract void attached();

  public abstract void detached();

  public abstract void pause();

  public abstract void resume();

  public abstract void destroyed();

  public abstract void addTouch(float x, float y);

  public abstract void updateTouch(float x, float y);

  public abstract void removeTouch(float x, float y);

  public abstract void handleMessage(int what, String body);
}
