package com.example.android.livecubes.cube1;

import android.content.res.AssetManager;
import android.os.Handler;
import android.service.wallpaper.WallpaperService;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.SurfaceHolder;

/**
 * Живые обои (Wallpaper) Ogre3D + Android
 */
public class CubeWallpaper1 extends WallpaperService  {

    private final Handler mHandler = new Handler();
    private static CubeWallpaper1 mContext;
    private static AssetManager mContext_Assets;

	static {
		System.loadLibrary("LiveWall");
	}
 
	private native void NativeDrawFrame();
	
	private native void NativeOnCreate(AssetManager asset);
	private native void NativeOnDestroy();
	private native void NativeOnShow();
	private native void NativeOnHide();
	
	private native void NativeOnSurfaceChanged(int width, int height);
	private native void NativeSurfaceCreated(Surface holder);
	
	
	private native void NativeOnSurfaceDestroyed();
	private native void NativeOnOffsetsChanged();
	
	private native void NativeOnTouchEvent(float width, float height, int action);
 
    public static CubeWallpaper1 getContext(){
        return mContext;
    }
    
    @Override
    public void onCreate()
    {
        super.onCreate();
		mContext = this;
		mContext_Assets = getAssets();
        NativeOnCreate(mContext_Assets);
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
    }

    @Override
    public Engine onCreateEngine()
    {
        return new CubeEngine();
    }

    class CubeEngine extends Engine {

        @Override
        public void onCreate(SurfaceHolder surfaceHolder)
        {
            super.onCreate(surfaceHolder);
            setTouchEventsEnabled(true);
        }

        @Override
        public void onDestroy()
        {
            super.onDestroy();
            NativeOnDestroy();
        }

        @Override
        public void onVisibilityChanged(boolean visible)
        {
            if (visible)
            {
            	NativeOnShow();
            }
            else
            {
            	NativeOnHide();
            }
        }
 
		@Override
		public void onSurfaceChanged(SurfaceHolder holder, int format, int width, int height)
		{
			// Update surface size.
			NativeOnSurfaceChanged(width, height);
		}

        @Override
        public void onSurfaceCreated(SurfaceHolder holder)
        {
            super.onSurfaceCreated(holder);
            NativeSurfaceCreated(holder.getSurface());
        }

        @Override
        public void onSurfaceDestroyed(SurfaceHolder holder)
        {
            super.onSurfaceDestroyed(holder);
            NativeOnSurfaceDestroyed();
        }

        @Override
		public void onOffsetsChanged(float xOffset, float yOffset, float xOffsetStep, float yOffsetStep, int xPixelOffset, int yPixelOffset)
        {
			super.onOffsetsChanged(xOffset, yOffset, xOffsetStep, yOffsetStep, xPixelOffset, yPixelOffset);
		}

        /*
         * Store the position of the touch event so we can use it for drawing later
         */
        @Override
        public void onTouchEvent(MotionEvent event)
        {
            super.onTouchEvent(event);
            NativeOnTouchEvent(event.getX(), event.getY(), event.getAction());
        }
    }
}
