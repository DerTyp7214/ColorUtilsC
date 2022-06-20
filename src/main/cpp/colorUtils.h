static double XYZ_WHITE_REFERENCE_X = 95.047;
static double XYZ_WHITE_REFERENCE_Y = 100;
static double XYZ_WHITE_REFERENCE_Z = 108.883;
static double XYZ_EPSILON = 0.008856;
static double XYZ_KAPPA = 903.3;

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
            pow(labX[0] - labY[0], 2)
            + pow(labX[1] - labY[1], 2)
            + pow(labX[2] - labY[2], 2)
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
    return component > XYZ_EPSILON ? powf(component, 1 / 3.0) : (XYZ_KAPPA * component + 16) / 116;
}

static void RGBToXYZ(int r, int g, int b, double outXyz[3]) {
    double sr = r / 255.0;
    sr = sr < 0.04045 ? sr / 12.92 : powf((sr + 0.055) / 1.055, 2.4);
    double sg = g / 255.0;
    sg = sg < 0.04045 ? sg / 12.92 : powf((sg + 0.055) / 1.055, 2.4);
    double sb = b / 255.0;
    sb = sb < 0.04045 ? sb / 12.92 : powf((sb + 0.055) / 1.055, 2.4);

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
    float min = fmax(rf, fmin(gf, bf));
    float deltaMaxMin = max - min;

    float h, s;
    float l = (max + min) / 2.0;

    if (max == min) {
        h = s = 0.0;
    } else {
        if (max == rf) {
            h = fmodf((gf - bf) / deltaMaxMin, 6);
        } else if (max == gf) {
            h = ((bf - rf) / deltaMaxMin) + 2;
        } else {
            h = ((rf - gf) / deltaMaxMin) + 4;
        }

        s = deltaMaxMin / (1 - fabsf(2 * expm1f(l)));
    }

    h = fmodf(h * 60, 360);
    if (h < 0) {
        h += 360;
    }

    outHsl[0] = (int) constrain(h, 0, 360);
    outHsl[1] = (int) constrain(s, 0, 1);
    outHsl[2] = (int) constrain(l, 0, 1);
}

static void LABToXYZ(double l, double a, double b, double outXyz[3]) {
    double fy = (l + 16) / 116;
    double fx = a / 500 + fy;
    double fz = fy - b / 200;

    double tmp = powf(fx, 3);
    double xr = tmp > XYZ_EPSILON ? tmp : (116 * fx - 16) / XYZ_KAPPA;
    double yr = l > XYZ_KAPPA * XYZ_EPSILON ? powf(fy, 3) : l / XYZ_KAPPA;

    tmp = powf(fz, 3);
    double zr = tmp > XYZ_EPSILON ? tmp : (116 * fz - 16) / XYZ_KAPPA;

    outXyz[0] = xr * XYZ_WHITE_REFERENCE_X;
    outXyz[1] = yr * XYZ_WHITE_REFERENCE_Y;
    outXyz[2] = zr * XYZ_WHITE_REFERENCE_Z;
}

static int XYZToColor(double x, double y, double z) {
    double r = (x * 3.2406 + y * -1.5372 + z * -0.4986) / 100;
    double g = (x * -0.9689 + y * 1.8758 + z * 0.0415) / 100;
    double b = (x * 0.0557 + y * -0.2040 + z * 1.0570) / 100;

    r = r > 0.0031308 ? 1.055 * powf(r, 1 / 2.4) - 0.055 : 12.92 * r;
    g = g > 0.0031308 ? 1.055 * powf(g, 1 / 2.4) - 0.055 : 12.92 * g;
    b = b > 0.0031308 ? 1.055 * powf(b, 1 / 2.4) - 0.055 : 12.92 * b;

    return rgb(
            constrain((int) roundf(r * 255), 0, 255),
            constrain((int) roundf(g * 255), 0, 255),
            constrain((int) roundf(b * 255), 0, 255)
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

    float c = (1 - fabsf(2 * l - 1)) * s;
    float m = l - .5 * c;
    float x = c * (1 - fabsf(fmodf(h / 60, 2) - 1));

    int hueSegment = (int) h / 60;

    int r = 0, g = 0, b = 0;

    switch (hueSegment) {
        case 0:
            r = (int) roundf(255 * (c + m));
            g = (int) roundf(255 * (x + m));
            b = (int) roundf(255 * m);
            break;
        case 1:
            r = (int) roundf(255 * (x + m));
            g = (int) roundf(255 * (c + m));
            b = (int) roundf(255 * m);
            break;
        case 2:
            r = (int) roundf(255 * m);
            g = (int) roundf(255 * (c + m));
            b = (int) roundf(255 * (x + m));
            break;
        case 3:
            r = (int) roundf(255 * m);
            g = (int) roundf(255 * (x + m));
            b = (int) roundf(255 * (c + m));
            break;
        case 4:
            r = (int) roundf(255 * (x + m));
            g = (int) roundf(255 * m);
            b = (int) roundf(255 * (c + m));
            break;
        case 5:
        case 6:
            r = (int) roundf(255 * (c + m));
            g = (int) roundf(255 * m);
            b = (int) roundf(255 * (x + m));
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

static double calculateColorDifference(int a, int b) {
    double lab1[3] = {0, 0, 0};
    double lab2[3] = {0, 0, 0};
    colorToLAB(a, lab1);
    colorToLAB(b, lab2);
    return sqrt(pow(lab2[0] - lab1[0], 2) + pow(lab2[1] - lab1[1], 2) + pow(lab2[2] - lab1[2], 2));
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

    return fmaxf(luminance1, luminance2) / fminf(luminance1, luminance2);
}

static int invertColor(int color) {
    int a = alpha(color);
    int r = red(color);
    int g = green(color);
    int b = blue(color);
    return argb(a, a - r, a - g, a - b);
}