package com.sinieco.changevoice;

import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Build;
import androidx.core.content.ContextCompat;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by BaiMeng on 2017/3/3.
 */
public class XPermissionUtils {

    private static int mRequestCode = -1;

    private static OnPermissionListener mOnPermissionListener;

    public interface OnPermissionListener {

        void onPermissionGranted();

        void onPermissionDenied();
    }

    @TargetApi(Build.VERSION_CODES.M)
    public static void requestPermissions(Context context, int requestCode
            , String[] permissions, OnPermissionListener listener) {

        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M){
            if (context instanceof Activity) {
                mOnPermissionListener = listener;
                List<String> deniedPermissions = getDeniedPermissions(context, permissions);
                if (deniedPermissions.size() > 0) {
                    mRequestCode = requestCode;
                    ((Activity) context).requestPermissions(deniedPermissions
                            .toArray(new String[deniedPermissions.size()]), requestCode);

                } else {
                    if (mOnPermissionListener != null)
                        mOnPermissionListener.onPermissionGranted();
                }
            } else {
                throw new RuntimeException("Context must be an Activity");
            }
        }else {
            mOnPermissionListener = listener;
            if (mOnPermissionListener != null)
                mOnPermissionListener.onPermissionGranted();
        }
        }

    /**
     * 鑾峰彇璇锋眰鏉冮檺涓渶瑕佹巿鏉冪殑鏉冮檺
     */
    private static List<String> getDeniedPermissions(Context context, String... permissions) {
        List<String> deniedPermissions = new ArrayList<>();
        for (String permission : permissions) {
            if (ContextCompat.checkSelfPermission(context, permission) == PackageManager.PERMISSION_DENIED) {
                deniedPermissions.add(permission);
            }
        }
        return deniedPermissions;
    }

    /**
     * 璇锋眰鏉冮檺缁撴灉锛屽搴擜ctivity涓璷nRequestPermissionsResult()鏂规硶銆?     */
    public static void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        if (mRequestCode != -1 && requestCode == mRequestCode) {
            if (mOnPermissionListener != null) {
                if (verifyPermissions(grantResults)) {
                    mOnPermissionListener.onPermissionGranted();
                } else {
                    mOnPermissionListener.onPermissionDenied();
                }
            }
        }
    }

    /**
     * 楠岃瘉鎵€鏈夋潈闄愭槸鍚﹂兘宸茬粡鎺堟潈
     */
    private static boolean verifyPermissions(int[] grantResults) {
        for (int grantResult : grantResults) {
            if (grantResult != PackageManager.PERMISSION_GRANTED) {
                return false;
            }
        }
        return true;
    }
}

