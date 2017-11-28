//
// @author admin on 2017/11/28.
//

#include <stdio.h>
#include <unistd.h>
#include "com_sinieco_changevoice_EffectUtils.h"
#include "inc/fmod.hpp"
#include <android/log.h>
#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"jason",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"jason",FORMAT,##__VA_ARGS__);
using namespace FMOD ;

JNIEXPORT void JNICALL Java_com_sinieco_changevoice_EffectUtils_fix
        (JNIEnv *env, jclass jclazz, jstring path, jint type){
//    const char* path_char = env->GetStringUTFChars(path,NULL);
//
//    System *system ;
//    Sound *sound ;
//    Channel *channel ;
//    System_Create(&system);
//    system->init(32, FMOD_INIT_NORMAL, NULL);
//    system->createSound(path_char, FMOD_DEFAULT, 0, &sound);
//    system->playSound(sound, 0, false, &channel);
//    system->update();
//
//    usleep(5000);
//    env->ReleaseStringUTFChars(path,path_char);
//    sound->release();
//    system->close();
//    system->release();


    System *system;
    Sound *sound;
    Channel *channel;
    DSP *dsp;

    //初始化
    System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, NULL);

    const char* path_cstr = env->GetStringUTFChars(path,NULL);
    //创建声音
    system->createSound(path_cstr, FMOD_DEFAULT, NULL, &sound);
    switch (type) {
        case com_sinieco_changevoice_EffectUtils_MODE_NORMAL:
            //原生播放
            system->playSound(sound, 0, false, &channel);

            break;
        default:
            break;
    }

    system->update();

    //释放资源
    usleep(5000);
    env->ReleaseStringUTFChars(path,path_cstr);

    sound->release();
    system->close();
    system->release();

}


