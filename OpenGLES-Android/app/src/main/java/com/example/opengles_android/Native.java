package com.example.opengles_android;

import android.content.res.AssetManager;

public class Native {
    static {
        System.loadLibrary("opengl");
    }
    public static native void initAssertManager(AssetManager assertManager);
    public static native void onSurfaceCreated();
    public static native void onSurfaceChanged(float width, float height);
    public static native void onDrawFrame();
}
