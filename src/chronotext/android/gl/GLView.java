
package chronotext.android.gl;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

public class GLView extends GLSurfaceView
{
  GLRenderer renderer;

  public GLView(Context context)
  {
    super(context);

    // setEGLConfigChooser(8, 8, 8, 8, 0, 0);
    // getHolder().setFormat(PixelFormat.RGBA_8888);
  }

  @Override
  public void setRenderer(Renderer renderer)
  {
    super.setRenderer(renderer);
    this.renderer = (GLRenderer) renderer;
  }

  @Override
  protected void onAttachedToWindow()
  {
    super.onAttachedToWindow();

    queueEvent(new Runnable()
    {
      public void run()
      {
        renderer.onAttachedToWindow();
      }
    });
  }

  @Override
  protected void onDetachedFromWindow()
  {
    super.onDetachedFromWindow();

    queueEvent(new Runnable()
    {
      public void run()
      {
        renderer.onDetachedFromWindow();
      }
    });
  }

  @Override
  public void onResume()
  {
    super.onResume();

    queueEvent(new Runnable()
    {
      public void run()
      {
        renderer.onResume();
      }
    });
  }

  @Override
  public void onPause()
  {
    super.onPause();

    queueEvent(new Runnable()
    {
      public void run()
      {
        renderer.onPause();
      }
    });
  }

  public void onDestroy()
  {
    queueEvent(new Runnable()
    {
      public void run()
      {
        renderer.onDestroy();
      }
    });
  }

  @Override
  public boolean onTouchEvent(MotionEvent e)
  {
    final float x = e.getX();
    final float y = e.getY();

    switch (e.getAction())
    {
      case MotionEvent.ACTION_DOWN :
        queueEvent(new Runnable()
        {
          public void run()
          {
            renderer.addTouch(x, y);
          }
        });
        break;

      case MotionEvent.ACTION_MOVE :
        queueEvent(new Runnable()
        {
          public void run()
          {
            renderer.updateTouch(x, y);
          }
        });
        break;

      case MotionEvent.ACTION_UP :
      case MotionEvent.ACTION_CANCEL :
        queueEvent(new Runnable()
        {
          public void run()
          {
            renderer.removeTouch(x, y);
          }
        });
        break;
    }

    return true;
  }
}
