#include <jni.h>
#include <android/bitmap.h>
#include "colorUtils.h"

extern "C" {
JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_alpha(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color
) {
    return alpha(color);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_red(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color
) {
    return red(color);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_green(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color
) {
    return green(color);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_blue(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color
) {
    return blue(color);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_rgb(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint r, jint g, jint b
) {
    return rgb(r, g, b);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_argb(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint a, jint r, jint g, jint b
) {
    return argb(a, r, g, b);
}

JNIEXPORT jdouble JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_pivotXyzComponent(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jdouble component
) {
    return pivotXyzComponent(component);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_RGBToXYZ(
        JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint r, jint g, jint b, jdoubleArray out_xyz
) {
    int size = 3;
    double xyz[size];
    RGBToXYZ(r, g, b, xyz);
    env->SetDoubleArrayRegion(out_xyz, 0, size, xyz);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_XYZToLab(
        JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jdouble x, jdouble y, jdouble z, jdoubleArray out_lab
) {
    int size = 3;
    double lab[size];
    XYZToLab(x, y, z, lab);
    env->SetDoubleArrayRegion(out_lab, 0, size, lab);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_RGBToLab(
        JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint r, jint g, jint b, jdoubleArray out_lab
) {
    int size = 3;
    double lab[size];
    RGBToLAB(r, g, b, lab);
    env->SetDoubleArrayRegion(out_lab, 0, size, lab);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_colorToLAB(
        JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color, jdoubleArray out_lab
) {
    int size = 3;
    double lab[size];
    colorToLAB(color, lab);
    env->SetDoubleArrayRegion(out_lab, 0, size, lab);
}

JNIEXPORT jdouble JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_calculateColorDifference(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint a, jint b) {
    return calculateColorDifference(a, b);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_invertColor(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color
) {
    return invertColor(color);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_blendARGB(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color1, jint color2, jfloat ratio
) {
    return blendARGB(color1, color2, ratio);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_colorToXYZ(
        JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color, jdoubleArray out_xyz
) {
    int size = 3;
    double xyz[size];
    colorToXYZ(color, xyz);
    env->SetDoubleArrayRegion(out_xyz, 0, size, xyz);
}

JNIEXPORT jdouble JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_calculateLuminance(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color
) {
    return calculateLuminance(color);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_RGBToHSL(
        JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint r, jint g, jint b, jfloatArray out_hsl
) {
    int size = 3;
    float HSL[size];
    RGBToHSL(r, g, b, HSL);
    env->SetFloatArrayRegion(out_hsl, 0, size, HSL);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_colorToHSL(
        JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color, jfloatArray out_hsl
) {
    int size = 3;
    float hsl[size];
    colorToHSL(color, hsl);
    env->SetFloatArrayRegion(out_hsl, 0, size, hsl);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_HSLToColor(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jfloatArray hsl
) {
    return HSLToColor(env->GetFloatArrayElements(hsl, (jboolean *) false));
}

JNIEXPORT jfloat JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_constrain(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jfloat amount, jfloat low, jfloat high
) {
    return constrain(amount, low, high);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_compositeAlpha(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint foreground_alpha, jint background_alpha
) {
    return compositeAlpha(foreground_alpha, background_alpha);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_compositeComponent(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint fg_c, jint fg_a, jint bg_c, jint bg_a, jint a
) {
    return compositeComponent(fg_c, fg_a, bg_c, bg_a, a);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_compositeColors(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint foreground, jint background
) {
    return compositeColors(foreground, background);
}

JNIEXPORT jdouble JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_calculateContrast(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint foreground, jint background
) {
    return calculateContrast(foreground, background);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_XYZToColor(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jdouble x, jdouble y, jdouble z
) {
    return XYZToColor(x, y, z);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_LABToXYZ(
        JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jdouble l, jdouble a, jdouble b, jdoubleArray out_xyz
) {
    int size = 3;
    double xyz[size];
    LABToXYZ(l, a, b, xyz);
    env->SetDoubleArrayRegion(out_xyz, 0, size, xyz);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_LABToColor(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jdouble l, jdouble a, jdouble b
) {
    return LABToColor(l, a, b);
}

JNIEXPORT jdouble JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_distanceEuclidean(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jdoubleArray lab_x, jdoubleArray lab_y
) {
    return distanceEuclidean((double *) lab_x, (double *) lab_y);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_setAlphaComponent(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color, jint alpha
) {
    return setAlphaComponent(color, alpha);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_RGBToCMYK(
        JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint r, jint g, jint b, jdoubleArray out_cmyk
) {
    int size = 4;
    double CMYK[size];
    RGBToCMYK(r, g, b, CMYK);
    env->SetDoubleArrayRegion(out_cmyk, 0, size, CMYK);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_CMYKToRGB(
        JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jdouble c, jdouble m, jdouble y, jdouble k, jintArray out_rgb
) {
    int size = 3;
    int RGB[size];
    CMYKToRGB(c, m, y, k, RGB);
    env->SetIntArrayRegion(out_rgb, 0, size, RGB);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_CMYKToColor(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jdouble c, jdouble m, jdouble y, jdouble k
) {
    return CMYKToColor(c, m, y, k);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_RGBToYIQ(
        JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint r, jint g, jint b, jintArray out_yiq
) {
    int size = 3;
    int YIQ[size];
    RGBToYIQ(r, g, b, YIQ);
    env->SetIntArrayRegion(out_yiq, 0, size, YIQ);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_YIQToRGB(
        JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint y, jint i, jint q, jintArray out_rgb
) {
    int size = 3;
    int RGB[size];
    YIQToRGB(y, i, q, RGB);
    env->SetIntArrayRegion(out_rgb, 0, size, RGB);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_YIQToColor(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint y, jint i, jint q
) {
    return YIQToColor(y, i, q);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_transformColor(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color, jint mode
) {
    return transformColor(color, mode);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_colorToRGB(
        JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color, jintArray out_rgb
) {
    int size = 3;
    int RGB[size];
    colorToRGB(color, RGB);
    env->SetIntArrayRegion(out_rgb, 0, size, RGB);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_overlayColors(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint top_color, jint bottom_color) {
    return overlayColors(top_color, bottom_color);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_associateColors(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jint color, jint red, jint green, jint blue) {
    return associateColors(color, red, green, blue);
}

JNIEXPORT jdouble JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_calculateBitmapLuminance(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject clazz,
        jobject bitmap) {

    if (!bitmap) {
        return -1.0;
    }

    AndroidBitmapInfo info;

    if (AndroidBitmap_getInfo(env, bitmap, &info) < 0) {
        return -2.0;
    }

    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        return -3.0;
    }

    if (!info.width || !info.height) {
        return -4.0;
    }

    if (!info.stride) {
        return -5.0;
    }

    return calculateBitmapLuminance(env, bitmap, info);
}
}