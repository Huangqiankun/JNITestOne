#include <jni.h>
#include <string>
#include <android/log.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_hqk_jnitestone_JNITest_sayHello(JNIEnv *env, jclass clazz) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

jstring sayHello2(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello，我是动态注册成功的！";
    return env->NewStringUTF(hello.c_str());
}

static const JNINativeMethod gMethods[] = {
        {"sayHello2", "()Ljava/lang/String;", (jstring *) sayHello2}
};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    __android_log_print(ANDROID_LOG_INFO, "native", "Jni_OnLoad");
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) //从JavaVM获取JNIEnv，一般使用1.4的版本
        return -1;
    jclass clazz = env->FindClass("com/hqk/jnitestone/JNITest");
    if (!clazz) {
        __android_log_print(ANDROID_LOG_INFO, "native",
                            "cannot get class: com/hqk/jnitestone/JNITest");
        return -1;
    }
    if (env->RegisterNatives(clazz, gMethods, sizeof(gMethods) / sizeof(gMethods[0]))) {
        __android_log_print(ANDROID_LOG_INFO, "native", "register native method failed!\n");
        return -1;
    }
    return JNI_VERSION_1_4;
}