package com.hiscene.dy.echoviewer;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.Rect;
import android.media.Image;
import android.util.Log;
import android.view.SurfaceHolder;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

public class algProcessEx implements Runnable {
    static {
        System.loadLibrary("native-lib");
    }
    /**
     * The JPEG image
     */
    private final Image mImage;
    /**
     * The file we save the image into.
     */
    private final File mFile;

    private SurfaceHolder surfaceHolder;
    public static boolean canDo = true;

    algProcessEx(Image image, File file, SurfaceHolder surfaceDraw) {
        surfaceHolder = surfaceDraw;
        mImage = image;
        mFile = file;
    }

    @Override
    public void run() {
        ByteBuffer buffer = mImage.getPlanes()[0].getBuffer();
        byte[] bytes = new byte[buffer.remaining()];
        buffer.get(bytes);

        if (true){
            //TBD
            runAlg(bytes, bytes.length);
            mImage.close();
        }else{
            FileOutputStream output = null;
            try {
                output = new FileOutputStream(mFile);
                output.write(bytes);
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                mImage.close();
                if (null != output) {
                    try {
                        output.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
        canDo = true;
    }

    private void rectDraw(jniReturn location){
        //定义画笔
        Paint mpaint = new Paint();
        mpaint.setColor(Color.BLUE);
        // mpaint.setAntiAlias(true);//去锯齿
        mpaint.setStyle(Paint.Style.STROKE);//空心
        // 设置paint的外框宽度
        mpaint.setStrokeWidth(4f);

        Canvas canvas = new Canvas();

        canvas =  surfaceHolder.lockCanvas();
        canvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR); //清楚掉上一次的画框。

        if (false){
            Rect r = new Rect(location.rectLS, location.rectTS, location.rectLS + location.rectWS,
                    location.rectTS + location.rectHS);
            canvas.drawRect(r, mpaint);
        }else {
            for (int i = 0; i < location.rectT.length; i++) {
                Rect r = new Rect(location.rectL[i], location.rectT[i], location.rectL[i] + location.rectW[i],
                        location.rectT[i] + location.rectH[i]);
                canvas.drawRect(r, mpaint);
            }
        }
        surfaceHolder.unlockCanvasAndPost(canvas);

        Log.d(TAG, "Alg:S " + location.msg + " " + location.rectHS + " " + location.rectWS
                + " " + location.rectLS + " " + location.rectTS);
        Log.d(TAG, "Alg: " + location.msg + " " + location.rectH[0] + " " + location.rectW[0]
                + " " + location.rectL[0] + " " + location.rectT[0]);
    }

    public static void initAlg(){
        Log.d(TAG, "Alg: " + initJNI());
    }

    public static void deinitAlg(){
        Log.d(TAG, "Alg: " + deinitJNI());
    }

    private void runAlg(byte[] img, int dataLen){
        rectDraw(runJNI(img, dataLen));
    }

    private static final String TAG = "ALG";
    private native static String initJNI();
    private native static jniReturn runJNI(byte[] img, int dataLength);
    private native static String deinitJNI();
}