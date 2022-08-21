#include <cmath>

static double XYZ_WHITE_REFERENCE_X = 95.047;
static double XYZ_WHITE_REFERENCE_Y = 100;
static double XYZ_WHITE_REFERENCE_Z = 108.883;
static double XYZ_EPSILON = 0.008856;
static double XYZ_KAPPA = 903.3;

const static int MODE_YIQ = 0;
const static int MODE_CMYK = 1;
const static int MODE_XYZ = 2;
const static int MODE_LAB = 3;
const static int MODE_HSL = 4;

static int alpha(int color) {
    return (int) ((unsigned int) (color) >> 24);
}

static int red(int color) {
    return (color >> 16) & 0xFF;
}

static int green(int color) {
    return (color >> 8) & 0xFF;
}

static int blue(int color) {
    return color & 0xFF;
}

static int rgb(int r, int g, int b) {
    return (0xFF << 24) | (r << 16) | (g << 8) | b;
}

static int argb(int a, int r, int g, int b) {
    return (a << 24) | (r << 16) | (g << 8) | b;
}

static float max(float a, float b, float c) {
    if (a > b && a > c)
        return a;
    if (b > a && b > c)
        return b;
    if (c > a && c > b)
        return c;

    return a;
}

static float constrain(float amount, float low, float high) {
    return amount < low ? low : fmin(amount, high);
}

static int compositeAlpha(int foregroundAlpha, int backgroundAlpha) {
    return 0xFF - (((0xFF - backgroundAlpha) * (0xFF - foregroundAlpha)) / 0xFF);
}

static int compositeComponent(int fgC, int fgA, int bgC, int bgA, int a) {
    if (a == 0) return 0;
    return ((0xFF * fgC * fgA) + (bgC * bgA * (0xFF - fgA))) / (a * 0xFF);
}

static int compositeColors(int foreground, int background) {
    int bgAlpha = alpha(background);
    int fgAlpha = alpha(foreground);
    int a = compositeAlpha(fgAlpha, bgAlpha);

    int r = compositeComponent(red(foreground), fgAlpha, red(background), bgAlpha, a);
    int g = compositeComponent(green(foreground), fgAlpha, green(background), bgAlpha, a);
    int b = compositeComponent(blue(foreground), fgAlpha, blue(background), bgAlpha, a);

    return argb(a, r, g, b);
}

static int setAlphaComponent(int color, int alpha) {
    return (color & 0x00FFFFFF) | (alpha << 24);
}

static double distanceEuclidean(double labX[3], double labY[3]) {
    return sqrt(
            pow(labX[0] - labY[0], 2) +
            pow(labX[1] - labY[1], 2) +
            pow(labX[2] - labY[2], 2)
    );
}

static int blendARGB(int color1, int color2, float ratio) {
    float inverseRatio = 1 - ratio;
    float a = alpha(color1) * inverseRatio + alpha(color2) * ratio;
    float r = red(color1) * inverseRatio + red(color2) * ratio;
    float g = green(color1) * inverseRatio + green(color2) * ratio;
    float b = blue(color1) * inverseRatio + blue(color2) * ratio;
    return argb((int) a, (int) r, (int) g, (int) b);
}

static double pivotXyzComponent(double component) {
    return component > XYZ_EPSILON ? pow(component, (double) 1 / 3) : (XYZ_KAPPA * component + 16) /
                                                                      116;
}

static void RGBToYIQ(int r, int g, int b, int outYIQ[3]) {
    outYIQ[0] = .299 * r + .587 * g + .114 * b;
    outYIQ[1] = .596 * r + .275 * g + .321 * b;
    outYIQ[2] = .212 * r + .523 * g + .311 * b;
}

static void YIQToRGB(int y, int i, int q, int outRGB[3]) {
    outRGB[0] = y + .956 * i + .621 * q;
    outRGB[1] = y - .272 * i - .647 * q;
    outRGB[2] = y - 1.106 * i + 1.703 * q;
}

static void RGBToCMYK(int r, int g, int b, double outCMYK[4]) {
    float fr = r / 255;
    float fg = g / 255;
    float fb = b / 255;

    outCMYK[3] = 1 - max(fr, fg, fb);

    outCMYK[0] = (1 - fr - outCMYK[3]) / (1 - outCMYK[3]);
    outCMYK[1] = (1 - fg - outCMYK[3]) / (1 - outCMYK[3]);
    outCMYK[2] = (1 - fb - outCMYK[3]) / (1 - outCMYK[3]);
}

static void CMYKToRGB(double c, double m, double y, double k, int outRGB[3]) {
    outRGB[0] = 255 * (1 - c / 100) * (1 - k / 100);
    outRGB[1] = 255 * (1 - m / 100) * (1 - k / 100);
    outRGB[2] = 255 * (1 - y / 100) * (1 - k / 100);
}

static void RGBToXYZ(int r, int g, int b, double outXyz[3]) {
    double sr = (double) r / 255;
    sr = sr < 0.04045 ? sr / 12.92 : pow((sr + 0.055) / 1.055, 2.4);
    double sg = (double) g / 255;
    sg = sg < 0.04045 ? sg / 12.92 : pow((sg + 0.055) / 1.055, 2.4);
    double sb = (double) b / 255;
    sb = sb < 0.04045 ? sb / 12.92 : pow((sb + 0.055) / 1.055, 2.4);

    outXyz[0] = 100 * (sr * 0.4124 + sg * 0.3576 + sb * 0.1805);
    outXyz[1] = 100 * (sr * 0.2126 + sg * 0.7152 + sb * 0.0722);
    outXyz[2] = 100 * (sr * 0.0193 + sg * 0.1192 + sb * 0.9505);
}

static void XYZToLab(double x, double y, double z, double outLab[3]) {
    x = pivotXyzComponent(x / XYZ_WHITE_REFERENCE_X);
    y = pivotXyzComponent(y / XYZ_WHITE_REFERENCE_Y);
    z = pivotXyzComponent(z / XYZ_WHITE_REFERENCE_Z);
    outLab[0] = fmax(0, 116 * y - 16);
    outLab[1] = 500 * (x - y);
    outLab[2] = 200 * (y - z);
}

static void RGBToLAB(int r, int g, int b, double outLab[3]) {
    RGBToXYZ(r, g, b, outLab);
    XYZToLab(outLab[0], outLab[1], outLab[2], outLab);
}

static void RGBToHSL(int r, int g, int b, float outHsl[3]) {
    float rf = r / 255.0;
    float gf = g / 255.0;
    float bf = b / 255.0;

    float max = fmax(rf, fmax(gf, bf));
    float min = fmin(rf, fmin(gf, bf));
    float deltaMaxMin = max - min;

    float h, s;
    float l = (max + min) / 2;

    if (max == min) {
        h = s = 0;
    } else {
        if (max == rf) {
            h = fmod((gf - bf) / deltaMaxMin, 6);
        } else if (max == gf) {
            h = ((bf - rf) / deltaMaxMin) + 2;
        } else {
            h = ((rf - gf) / deltaMaxMin) + 4;
        }

        s = deltaMaxMin / (1 - abs(2 * l - 1));
    }

    h = fmod(h * 60, 360);
    if (h < 0) {
        h += 360;
    }

    outHsl[0] = constrain(h, 0, 360);
    outHsl[1] = constrain(s, 0, 1);
    outHsl[2] = constrain(l, 0, 1);
}

static void LABToXYZ(double l, double a, double b, double outXyz[3]) {
    double fy = (l + 16) / 116;
    double fx = a / 500 + fy;
    double fz = fy - b / 200;

    double tmp = pow(fx, 3);
    double xr = tmp > XYZ_EPSILON ? tmp : (116 * fx - 16) / XYZ_KAPPA;
    double yr = l > XYZ_KAPPA * XYZ_EPSILON ? pow(fy, 3) : l / XYZ_KAPPA;

    tmp = pow(fz, 3);
    double zr = tmp > XYZ_EPSILON ? tmp : (116 * fz - 16) / XYZ_KAPPA;

    outXyz[0] = xr * XYZ_WHITE_REFERENCE_X;
    outXyz[1] = yr * XYZ_WHITE_REFERENCE_Y;
    outXyz[2] = zr * XYZ_WHITE_REFERENCE_Z;
}

static int YIQToColor(int y, int i, int q) {
    int RGB[3];
    YIQToRGB(y, i, q, RGB);
    return rgb(RGB[0], RGB[1], RGB[2]);
}

static int CMYKToColor(double c, double m, double y, double k) {
    int RGB[3];
    CMYKToRGB(c, m, y, k, RGB);
    return rgb(RGB[0], RGB[1], RGB[2]);
}

static int XYZToColor(double x, double y, double z) {
    double r = (x * 3.2406 + y * -1.5372 + z * -0.4986) / 100;
    double g = (x * -0.9689 + y * 1.8758 + z * 0.0415) / 100;
    double b = (x * 0.0557 + y * -0.2040 + z * 1.0570) / 100;

    r = r > 0.0031308 ? 1.055 * pow(r, 1 / 2.4) - 0.055 : 12.92 * r;
    g = g > 0.0031308 ? 1.055 * pow(g, 1 / 2.4) - 0.055 : 12.92 * g;
    b = b > 0.0031308 ? 1.055 * pow(b, 1 / 2.4) - 0.055 : 12.92 * b;

    return rgb(
            constrain((int) round(r * 255), 0, 255),
            constrain((int) round(g * 255), 0, 255),
            constrain((int) round(b * 255), 0, 255)
    );
}

static int LABToColor(double l, double a, double b) {
    double result[3];
    LABToXYZ(l, a, b, result);
    return XYZToColor(result[0], result[1], result[2]);
}

static int HSLToColor(float hsl[3]) {
    float h = hsl[0];
    float s = hsl[1];
    float l = hsl[2];

    float c = (1 - abs(2 * l - 1)) * s;
    float m = l - .5 * c;
    float x = c * (1 - abs(fmod(h / 60, 2) - 1));

    int hueSegment = (int) h / 60;

    int r = 0, g = 0, b = 0;

    switch (hueSegment) {
        case 0:
            r = (int) round(255 * (c + m));
            g = (int) round(255 * (x + m));
            b = (int) round(255 * m);
            break;
        case 1:
            r = (int) round(255 * (x + m));
            g = (int) round(255 * (c + m));
            b = (int) round(255 * m);
            break;
        case 2:
            r = (int) round(255 * m);
            g = (int) round(255 * (c + m));
            b = (int) round(255 * (x + m));
            break;
        case 3:
            r = (int) round(255 * m);
            g = (int) round(255 * (x + m));
            b = (int) round(255 * (c + m));
            break;
        case 4:
            r = (int) round(255 * (x + m));
            g = (int) round(255 * m);
            b = (int) round(255 * (c + m));
            break;
        case 5:
        case 6:
            r = (int) round(255 * (c + m));
            g = (int) round(255 * m);
            b = (int) round(255 * (x + m));
            break;
    }

    r = (int) constrain(r, 0, 255);
    g = (int) constrain(g, 0, 255);
    b = (int) constrain(b, 0, 255);

    return rgb(r, g, b);
}

static void colorToLAB(int color, double outLab[3]) {
    RGBToLAB(red(color), green(color), blue(color), outLab);
}

static void colorToXYZ(int color, double outXyz[3]) {
    RGBToXYZ(red(color), green(color), blue(color), outXyz);
}

static void colorToHSL(int color, float outHsl[3]) {
    RGBToHSL(red(color), green(color), blue(color), outHsl);
}

static void colorToRGB(int color, int outRGB[3]) {
    outRGB[0] = red(color);
    outRGB[1] = green(color);
    outRGB[2] = blue(color);
}

static double calculateColorDifference(int a, int b) {
    double lab1[3] = {0, 0, 0};
    double lab2[3] = {0, 0, 0};
    colorToLAB(a, lab1);
    colorToLAB(b, lab2);
    return sqrt(
            pow(lab2[0] - lab1[0], 2) +
            pow(lab2[1] - lab1[1], 2) +
            pow(lab2[2] - lab1[2], 2)
    );
}

static double calculateLuminance(int color) {
    double result[3];
    colorToXYZ(color, result);
    return result[1] / 100;
}

static double calculateContrast(int foreground, int background) {
    if (alpha(foreground) < 255) {
        foreground = compositeColors(foreground, background);
    }

    double luminance1 = calculateLuminance(foreground) + .05;
    double luminance2 = calculateLuminance(background) + .05;

    return fmax(luminance1, luminance2) / fmin(luminance1, luminance2);
}

static int invertColor(int color) {
    int a = alpha(color);
    int r = red(color);
    int g = green(color);
    int b = blue(color);
    return argb(a, a - r, a - g, a - b);
}

static int overlayColors(int topColor, int bottomColor) {
    int topAlpha = alpha(topColor);
    int bottomAlpha = alpha(bottomColor);
    int alphaSum = bottomAlpha + topAlpha;

    int r = (red(bottomColor) * bottomAlpha + red(topColor) * topAlpha) / alphaSum;
    int g = (green(bottomColor) * bottomAlpha + green(topColor) * topAlpha) / alphaSum;
    int b = (blue(bottomColor) * bottomAlpha + blue(topColor) * topAlpha) / alphaSum;

    return argb(fmin(255, alphaSum), r, g, b);
}

static int transformColor(int color, int mode) {
    int r = red(color);
    int g = green(color);
    int b = blue(color);

    double output[3] = {
            static_cast<double>(r),
            static_cast<double>(g),
            static_cast<double>(b)
    };
    double output4[4];
    switch (mode) {
        case MODE_YIQ:
            RGBToYIQ(r, g, b, (int *) output);
            break;
        case MODE_CMYK:
            RGBToCMYK(r, g, b, output4);
            output[0] = output4[0] * 2.55;
            output[1] = output4[2] * 2.55;
            output[2] = output4[2] * 2.55;
            break;
        case MODE_HSL:
            RGBToHSL(r, g, b, (float *) output);
            output[0] = output[0] / 360 * 255;
            output[1] = output[1] * 255;
            output[2] = output[2] * 255;
            break;
        case MODE_LAB:
            RGBToLAB(r, g, b, output);
            output[0] = output[0] * 2.55;
            output[1] = output[1] + 128;
            output[2] = output[2] + 128;
            break;
        case MODE_XYZ:
            RGBToXYZ(r, g, b, output);
            output[0] = output[0] / XYZ_WHITE_REFERENCE_X * 255;
            output[1] = output[1] / XYZ_WHITE_REFERENCE_Y * 255;
            output[2] = output[2] / XYZ_WHITE_REFERENCE_Z * 255;
            break;
    }

    return rgb(output[0], output[1], output[2]);
}