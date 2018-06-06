package com.hiscene.dy.echoviewer;

import android.graphics.Bitmap;
import android.graphics.Matrix;
import android.media.Image;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

public class algProcess implements Runnable {
    /**
     * The JPEG image
     */
    private Bitmap mImage;
    /**
     * The file we save the image into.
     */
    private final File mFile;

    public static boolean canDo = true;

    algProcess(Bitmap image, File file) {
        mImage = image;
        mFile = file;
    }

    @Override
    public void run() {
        FileOutputStream output = null;
        try {
            output = new FileOutputStream(mFile);
            mImage = rotateBitmap(mImage, 270);
            mImage = scaleBitmap(mImage, 1280, 720);
            //TBD
            mImage.compress(Bitmap.CompressFormat.JPEG, 90, output);
         } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (null != output) {
                try {
                    canDo = true;
                    output.flush();
                    output.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private Bitmap scaleBitmap(Bitmap origin, int newWidth, int newHeight) {
        if (origin == null) {
            return null;
        }
        int height = origin.getHeight();
        int width = origin.getWidth();
        float scaleWidth = ((float) newWidth) / width;
        float scaleHeight = ((float) newHeight) / height;
        Matrix matrix = new Matrix();
        matrix.postScale(scaleWidth, scaleHeight);// 使用后乘
        Bitmap newBM = Bitmap.createBitmap(origin, 0, 0, width, height, matrix, false);
        if (!origin.isRecycled()) {
            origin.recycle();
        }
        return newBM;
    }

    private Bitmap rotateBitmap(Bitmap origin, float alpha) {
        if (origin == null) {
            return null;
        }
        int width = origin.getWidth();
        int height = origin.getHeight();
        Matrix matrix = new Matrix();
        matrix.setRotate(alpha);
        // 围绕原地进行旋转
        Bitmap newBM = Bitmap.createBitmap(origin, 0, 0, width, height, matrix, false);
        if (newBM.equals(origin)) {
            return newBM;
        }
        origin.recycle();
        return newBM;
    }
}
