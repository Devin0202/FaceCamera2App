#include <jni.h>
#include <string>
#include "HifdTypes.h"
#include "Hifd.h"

jclass cls;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_hiscene_dy_echoviewer_algProcessEx_initJNI(JNIEnv *env, jclass type) {

    // TODO
    std::string returnValue = "Init from C++: ";
    int rtv = fdCreate();
    return env->NewStringUTF((returnValue + std::to_string(rtv)).c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_hiscene_dy_echoviewer_algProcessEx_deinitJNI(JNIEnv *env, jclass type) {

    // TODO
    std::string returnValue = "Deinit from C++";
    fdDestroy();
    return env->NewStringUTF(returnValue.c_str());
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_hiscene_dy_echoviewer_algProcessEx_runJNI(JNIEnv *env, jclass type, jbyteArray img_, jint dataLength) {
    jbyte *img = env->GetByteArrayElements(img_, NULL);
    cReturn rt;
    //rtv: faces num
    int rtv = fdRun((char *)img, dataLength, 1280, 720, &rt);
    env->ReleaseByteArrayElements(img_, img, 0);

    std::string returnValue = "Run once from C++: ";

    cls = env->FindClass("com/hiscene/dy/echoviewer/jniReturn");
    jobject javaResult = env->AllocObject(cls);
    jfieldID id;
    int arrLen = rtv;
    jint *arr = NULL;
    jintArray jarr;

    if (0 < arrLen){
        jarr = env->NewIntArray(arrLen);
        arr = env->GetIntArrayElements(jarr, NULL);
        for(int i = 0; i < arrLen; i++){
            arr[i] = rt.w[i];
        }
        id = env->GetFieldID(cls, "rectW","[I");
        env->SetObjectField(javaResult, id, jarr);
        env->ReleaseIntArrayElements(jarr, arr, 0);

        jarr = env->NewIntArray(arrLen);
        arr = env->GetIntArrayElements(jarr, NULL);
        for(int i = 0; i < arrLen; i++){
            arr[i] = rt.h[i];
        }
        id = env->GetFieldID(cls, "rectH","[I");
        env->SetObjectField(javaResult, id, jarr);
        env->ReleaseIntArrayElements(jarr, arr, 0);

        jarr = env->NewIntArray(arrLen);
        arr = env->GetIntArrayElements(jarr, NULL);
        for(int i = 0; i < arrLen; i++){
            arr[i] = rt.l[i];
        }
        id = env->GetFieldID(cls, "rectL","[I");
        env->SetObjectField(javaResult, id, jarr);
        env->ReleaseIntArrayElements(jarr, arr, 0);

        jarr = env->NewIntArray(arrLen);
        arr = env->GetIntArrayElements(jarr, NULL);
        for(int i = 0; i < arrLen; i++){
            arr[i] = rt.t[i];
        }
        id = env->GetFieldID(cls, "rectT","[I");
        env->SetObjectField(javaResult, id, jarr);
        env->ReleaseIntArrayElements(jarr, arr, 0);
    }else{
        jintArray jarr = env->NewIntArray(1);
        //2.获取数组指针
        arr = env->GetIntArrayElements(jarr, NULL);
        //3.赋值
        arr[0] = 2;
        //4.释放资源
        id = env->GetFieldID(cls, "rectW","[I");
        env->SetObjectField(javaResult, id, jarr);

        id = env->GetFieldID(cls, "rectH","[I");
        env->SetObjectField(javaResult, id, jarr);

        id = env->GetFieldID(cls, "rectL","[I");
        env->SetObjectField(javaResult, id, jarr);

        id = env->GetFieldID(cls, "rectT","[I");
        env->SetObjectField(javaResult, id, jarr);

        env->ReleaseIntArrayElements(jarr, arr, 0);
    }

    id = env->GetFieldID(cls,"rectWS","I");
    env->SetIntField(javaResult, id, rt.ws);

    id = env->GetFieldID(cls,"rectHS","I");
    env->SetIntField(javaResult, id, rt.hs);

    id = env->GetFieldID(cls, "rectLS","I");
    env->SetIntField(javaResult, id, rt.ls);

    id = env->GetFieldID(cls,"rectTS","I");
    env->SetIntField(javaResult, id, rt.ts);

    id = env ->GetFieldID(cls, "msg", "Ljava/lang/String;");
    jstring resultString = env->NewStringUTF((returnValue + std::to_string(rtv)).c_str());
    env->SetObjectField(javaResult, id, resultString);

    return javaResult;
}