package com.sinieco.changevoice;

import android.Manifest;
import android.os.Bundle;
import android.os.Environment;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import org.fmod.FMOD;

import java.io.File;

/**
 * @author BaiMeng on 2017/11/28.
 */

public class QQVoiceActivity extends AppCompatActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        FMOD.init(this);
        setContentView(R.layout.qq_activity);
        XPermissionUtils.requestPermissions(this, 0, new String[]{
                Manifest.permission.READ_EXTERNAL_STORAGE,
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.RECORD_AUDIO
        }, new XPermissionUtils.OnPermissionListener() {
            @Override
            public void onPermissionGranted() {

            }

            @Override
            public void onPermissionDenied() {

            }
        });
    }

    public void mFix(View view){
        String path = Environment.getExternalStorageDirectory() + File.separator + "test.wav";
        if(new File(path).exists()){
            EffectUtils.fix(path,EffectUtils.MODE_NORMAL);
            Log.e("-------------->>>>>","播放音频文件");
        }else {
            Log.e("-------------->>>>>","音频文件不存在");
        }
    }

    @Override
    public void onDetachedFromWindow() {
        FMOD.close();
        super.onDetachedFromWindow();
    }
}
