#include <Geode/Geode.hpp>
#include <Geode/modify/AppDelegate.hpp>

using namespace geode::prelude;

#ifdef GEODE_IS_ANDROID
#include <jni.h>
#include <platform/android/jni/JniHelper.h>

static void forceHighRefreshRate(float hz) {
    auto env = cocos2d::JniHelper::getEnv();
    if (!env) return;

    jobject activity = cocos2d::JniHelper::getActivity();
    if (!activity) return;

    jclass activityClass = env->GetObjectClass(activity);
    jmethodID getWindow = env->GetMethodID(activityClass, "getWindow", "()Landroid/view/Window;");
    jobject window = env->CallObjectMethod(activity, getWindow);
    if (!window) return;

    jclass windowClass = env->GetObjectClass(window);
    jmethodID getAttributes = env->GetMethodID(
        windowClass, "getAttributes", "()Landroid/view/WindowManager$LayoutParams;");
    jobject params = env->CallObjectMethod(window, getAttributes);
    if (!params) return;

    jclass paramsClass = env->GetObjectClass(params);
    jfieldID preferredRefreshRateField = env->GetFieldID(paramsClass, "preferredRefreshRate", "F");
    env->SetFloatField(params, preferredRefreshRateField, hz);

    jmethodID setAttributes = env->GetMethodID(
        windowClass, "setAttributes", "(Landroid/view/WindowManager$LayoutParams;)V");
    env->CallVoidMethod(window, setAttributes, params);

    log::info("FpsUnlocker: requested {} Hz preferred refresh rate", hz);
}
#endif

class $modify(AppDelegate) {
    bool applicationDidFinishLaunching() {
        bool res = AppDelegate::applicationDidFinishLaunching();
        #ifdef GEODE_IS_ANDROID
        forceHighRefreshRate(120.0f);
        #endif
        return res;
    }
};
