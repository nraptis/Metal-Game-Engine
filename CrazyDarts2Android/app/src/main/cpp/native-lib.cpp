#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL

Java_com_froggy_dartsii_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "We Talk to C++ Now";
    return env->NewStringUTF(hello.c_str());
}
