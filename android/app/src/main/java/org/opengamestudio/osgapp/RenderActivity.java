package org.opengamestudio.osgapp;

import android.app.Activity;
import android.os.Bundle;
// Resources.
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
// Input.
import android.view.MotionEvent;
import android.view.View;

import <your package name>.R;

public class RenderActivity extends Activity implements View.OnTouchListener
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_render);

        setupResources();
        setupInput();
    }

    private void setupResources()
    {
        // Get absolute path to internal storage.
        File dir = getFilesDir();
        String path = dir.getAbsolutePath();
        // Check if 'box.osgt' already exists.
        String modelPath = path + "/box.osgt";
        File model = new File(modelPath);
        // Copy 'box.ogst' from 'res/raw', if it does not exist.
        try {
            if (!model.exists()) {
                // Note: this only works for small files,
                // because we read the whole file into memory.
                InputStream is = getResources().openRawResource(R.raw.box);
                byte[] buffer = new byte[is.available()];
                is.read(buffer);
                FileOutputStream os = new FileOutputStream(model);
                os.write(buffer);
            }
            osgNativeLib.loadModel(modelPath);
        }
        catch (Exception e) {
            // Do nothing.
        }
    }

    private void setupInput()
    {
        EGLview view = (EGLview)findViewById(R.id.render_surface);
        view.setOnTouchListener(this);
    }
    @Override
    public boolean onTouch(View view, MotionEvent event)
    {
        int action = event.getAction() & event.ACTION_MASK;
        float x = event.getX(0);
        float y = event.getY(0);
        switch (action)
        {
            case (MotionEvent.ACTION_MOVE):
            {
                osgNativeLib.moveMouse(x, y);
                return true;
            }
            case (MotionEvent.ACTION_DOWN):
            {
                osgNativeLib.pressMouse(true, x, y);
                return true;
            }
            case (MotionEvent.ACTION_CANCEL):
            {
                osgNativeLib.pressMouse(false, x, y);
                return true;
            }
            default:
                break;
        }
        return false;
    }
}
