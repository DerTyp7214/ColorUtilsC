#include <math.h>
#include "colorUtils.h"
#include <jni.h>

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_alpha(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint color
) {
    return alpha(color);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_red(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint color
) {
    return red(color);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_green(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint color
) {
    return green(color);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_blue(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint color
) {
    return blue(color);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_rgb(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint r, jint g, jint b
) {
    return rgb(r, g, b);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_argb(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint a, jint r, jint g, jint b
) {
    return argb(a, r, g, b);
}

JNIEXPORT jdouble JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_pivotXyzComponent(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jdouble component
) {
    return pivotXyzComponent(component);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_RGBToXYZ(
        JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint r, jint g, jint b, jdoubleArray out_xyz
) {
    int size = 3;
    double xyz[size];
    RGBToXYZ(r, g, b, xyz);
    (*env)->SetDoubleArrayRegion(env, out_xyz, 0, size, xyz);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_XYZToLab(
        JNIEnv *env,
        __attribute__((unused)) jobject class,
        jdouble x, jdouble y, jdouble z, jdoubleArray out_lab
) {
    int size = 3;
    double lab[size];
    XYZToLab(x, y, z, lab);
    (*env)->SetDoubleArrayRegion(env, out_lab, 0, size, lab);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_RGBToLab(
        JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint r, jint g, jint b, jdoubleArray out_lab
) {
    int size = 3;
    double lab[size];
    RGBToLAB(r, g, b, lab);
    (*env)->SetDoubleArrayRegion(env, out_lab, 0, size, lab);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_colorToLAB(
        JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint color, jdoubleArray out_lab
) {
    int size = 3;
    double lab[size];
    colorToLAB(color, lab);
    (*env)->SetDoubleArrayRegion(env, out_lab, 0, size, lab);
}

JNIEXPORT jdouble JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_calculateColorDifference(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint a, jint b) {
    return calculateColorDifference(a, b);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_invertColor(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint color
) {
    return invertColor(color);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_blendARGB(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint color1, jint color2, jfloat ratio
) {
    return blendARGB(color1, color2, ratio);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_colorToXYZ(
        JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint color, jdoubleArray out_xyz
) {
    int size = 3;
    double xyz[size];
    colorToXYZ(color, xyz);
    (*env)->SetDoubleArrayRegion(env, out_xyz, 0, size, xyz);
}

JNIEXPORT jdouble JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_calculateLuminance(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint color
) {
    return calculateLuminance(color);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_RGBToHSL(
        JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint r, jint g, jint b, jfloatArray out_hsl
) {
    int size = 3;
    float hsl[size];
    RGBToHSL(r, g, b, hsl);
    (*env)->SetFloatArrayRegion(env, out_hsl, 0, size, hsl);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_colorToHSL(
        JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint color, jfloatArray out_hsl
) {
    int size = 3;
    float hsl[size];
    colorToHSL(color, hsl);
    (*env)->SetFloatArrayRegion(env, out_hsl, 0, size, hsl);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_HSLToColor(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jfloatArray hsl
) {
    return HSLToColor(hsl);
}

JNIEXPORT jfloat JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_constrain__FFF(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jfloat amount, jfloat low, jfloat high
) {
    return constrain(amount, low, high);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_constrain__III(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint amount, jint low, jint high
) {
    return (int) constrain((float) amount, (float) low, (float) high);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_compositeAlpha(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint foreground_alpha, jint background_alpha
) {
    return compositeAlpha(foreground_alpha, background_alpha);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_compositeComponent(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint fg_c, jint fg_a, jint bg_c, jint bg_a, jint a
) {
    return compositeComponent(fg_c, fg_a, bg_c, bg_a, a);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_compositeColors(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint foreground, jint background
) {
    return compositeColors(foreground, background);
}

JNIEXPORT jdouble JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_calculateContrast(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint foreground, jint background
) {
    return calculateContrast(foreground, background);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_XYZToColor(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jdouble x, jdouble y, jdouble z
) {
    return XYZToColor(x, y, z);
}

JNIEXPORT void JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_LABToXYZ(
        JNIEnv *env,
        __attribute__((unused)) jobject class,
        jdouble l, jdouble a, jdouble b, jdoubleArray out_xyz
) {
    int size = 3;
    double xyz[size];
    LABToXYZ(l, a, b, xyz);
    (*env)->SetDoubleArrayRegion(env, out_xyz, 0, size, xyz);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_LABToColor(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jdouble l, jdouble a, jdouble b
) {
    return LABToColor(l, a, b);
}

JNIEXPORT jdouble JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_distanceEuclidean(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jdoubleArray lab_x, jdoubleArray lab_y
) {
    return distanceEuclidean(lab_x, lab_y);
}

JNIEXPORT jint JNICALL
Java_de_dertyp7214_colorutilsc_ColorUtilsC_setAlphaComponent(
        __attribute__((unused)) JNIEnv *env,
        __attribute__((unused)) jobject class,
        jint color, jint alpha
) {
    return setAlphaComponent(color, alpha);
}