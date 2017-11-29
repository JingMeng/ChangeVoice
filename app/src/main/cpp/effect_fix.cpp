//
// @author admin on 2017/11/28.
//

#include <stdio.h>
#include <unistd.h>
#include "com_sinieco_changevoice_EffectUtils.h"
#include "inc/fmod.hpp"
using namespace FMOD ;

JNIEXPORT void JNICALL Java_com_sinieco_changevoice_EffectUtils_fix
        (JNIEnv *env, jclass jclazz, jstring path, jint type){
    const char* path_char = env->GetStringUTFChars(path,NULL);

    System *system ;
    Sound *sound ;
    Channel *channel ;
    System_Create(&system);
    DSP *dsp ;
    float frequency ;
    bool playing = true ;
    system->init(32, FMOD_INIT_NORMAL, NULL);
    system->createSound(path_char, FMOD_DEFAULT, 0, &sound);
    switch (type){
        case com_sinieco_changevoice_EffectUtils_MODE_DASHU :
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,0.8);
            system->playSound(sound,0, false,&channel);
            channel->addDSP(0,dsp);
            break ;
        case com_sinieco_changevoice_EffectUtils_MODE_GAOGUAI:
            //本质是提高语速
            system->playSound(sound,0,false,&channel);
            channel->getFrequency(&frequency);
            frequency = frequency *1.6 ;
            channel->setFrequency(frequency);
            break ;
        case com_sinieco_changevoice_EffectUtils_MODE_JINGSONG :
            system->createDSPByType(FMOD_DSP_TYPE_TREMOLO,&dsp);
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW,0.5);
            system->playSound(sound,0,false,&channel);
            channel->addDSP(0,dsp);
            break ;
        case com_sinieco_changevoice_EffectUtils_MODE_KONGLING :
            system->createDSPByType(FMOD_DSP_TYPE_ECHO,&dsp);
            system->playSound(sound,0,false,&channel);
            channel->addDSP(0,dsp);
            break ;
        case com_sinieco_changevoice_EffectUtils_MODE_LUOLI :
            //FMOD_DSP_TYPE_PITCHSHIFT dsp,提升或者降低音调用的一种音效
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,2.5);
            system->playSound(sound,0, false,&channel);
            channel->addDSP(0,dsp);
            break ;
        case com_sinieco_changevoice_EffectUtils_MODE_NORMAL :
            system->playSound(sound, 0, false, &channel);
            break ;
        default:
            break ;
    }
    system->update();

    while (playing){
        channel->isPlaying(&playing);
        usleep(1000*1000);
    }
    env->ReleaseStringUTFChars(path,path_char);
    sound->release();
    system->close();
    system->release();
}


