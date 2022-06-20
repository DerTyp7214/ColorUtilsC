package de.dertyp7214.colorutilsc

import androidx.annotation.ColorInt
import androidx.annotation.FloatRange
import androidx.annotation.IntRange

@Suppress("FunctionName")
object ColorUtilsC {
    fun init() {
        System.loadLibrary("colorutilsc")
    }

    private const val XYZ_WHITE_REFERENCE_X = 95.047
    private const val XYZ_WHITE_REFERENCE_Y = 100.0
    private const val XYZ_WHITE_REFERENCE_Z = 108.883

    /**
     * Extracts the alpha component of the given color
     *
     * @param color color value
     * @return alpha component
     */
    @IntRange(from = 0x0, to = 0xFF)
    external fun alpha(@ColorInt color: Int): Int

    /**
     * Extracts the red component of the given color
     *
     * @param color color value
     * @return red component
     */
    @IntRange(from = 0x0, to = 0xFF)
    external fun red(@ColorInt color: Int): Int

    /**
     * Extracts the green component of the given color
     *
     * @param color color value
     * @return green component
     */
    @IntRange(from = 0x0, to = 0xFF)
    external fun green(@ColorInt color: Int): Int

    /**
     * Extracts the blue component of the given color
     *
     * @param color color value
     * @return blue component
     */
    @IntRange(from = 0x0, to = 0xFF)
    external fun blue(@ColorInt color: Int): Int

    /**
     * Converts rgb values to color value.
     *
     * @param r red component[0..255]
     * @param g green component[0..255]
     * @param b blue component[0..255]
     * @return color value
     */
    @ColorInt
    external fun rgb(
        @IntRange(from = 0x0, to = 0xFF) r: Int,
        @IntRange(from = 0x0, to = 0xFF) g: Int,
        @IntRange(from = 0x0, to = 0xFF) b: Int
    ): Int

    /**
     * Converts argb values to decimal color value.
     *
     * @param a alpha component[0..255]
     * @param r red component[0..255]
     * @param g green component[0..255]
     * @param b blue component[0..255]
     * @return decimal color value
     */
    @ColorInt
    external fun argb(
        @IntRange(from = 0x0, to = 0xFF) a: Int,
        @IntRange(from = 0x0, to = 0xFF) r: Int,
        @IntRange(from = 0x0, to = 0xFF) g: Int,
        @IntRange(from = 0x0, to = 0xFF) b: Int
    ): Int

    external fun constrain(
        amount: Float,
        low: Float,
        high: Float
    ): Float

    external fun constrain(
        amount: Int,
        low: Int,
        high: Int
    ): Int

    external fun compositeAlpha(foregroundAlpha: Int, backgroundAlpha: Int): Int

    external fun compositeComponent(
        fgC: Int, fgA: Int, bgC: Int, bgA: Int, a: Int
    ): Int

    /**
     * Composite two potentially translucent colors over each other and returns the result.
     */
    @ColorInt
    external fun compositeColors(
        @ColorInt foreground: Int,
        @ColorInt background: Int
    ): Int

    /**
     * Returns the euclidean distance between two LAB colors.
     */
    external fun distanceEuclidean(labX: DoubleArray, labY: DoubleArray): Double

    external fun pivotXyzComponent(component: Double): Double

    /**
     * Convert RGB components to its CIE XYZ representative components.
     *
     * <p>The resulting XYZ representation will use the D65 illuminant and the CIE
     * 2° Standard Observer (1931).</p>
     *
     * <ul>
     * <li>outXyz[0] is X [0, 95.047)</li>
     * <li>outXyz[1] is Y [0, 100)</li>
     * <li>outXyz[2] is Z [0, 108.883)</li>
     * </ul>
     *
     * @param r red component value [0, 255]
     * @param g green component value [0, 255]
     * @param b blue component value [0, 255]
     * @param outXyz 3-element array which holds the resulting XYZ components
     */
    external fun RGBToXYZ(
        @IntRange(from = 0x0, to = 0xFF) r: Int,
        @IntRange(from = 0x0, to = 0xFF) g: Int,
        @IntRange(from = 0x0, to = 0xFF) b: Int,
        outXyz: DoubleArray
    )

    /**
     * Converts a color from CIE XYZ to CIE Lab representation.
     *
     * <p>This method expects the XYZ representation to use the D65 illuminant and the CIE
     * 2° Standard Observer (1931).</p>
     *
     * <ul>
     * <li>outLab[0] is L [0, 100]</li>
     * <li>outLab[1] is a [-128, 127)</li>
     * <li>outLab[2] is b [-128, 127)</li>
     * </ul>
     *
     * @param x X component value [0, 95.047)
     * @param y Y component value [0, 100)
     * @param z Z component value [0, 108.883)
     * @param outLab 3-element array which holds the resulting Lab components
     */
    external fun XYZToLab(
        @FloatRange(from = .0, to = XYZ_WHITE_REFERENCE_X) x: Double,
        @FloatRange(from = .0, to = XYZ_WHITE_REFERENCE_X) y: Double,
        @FloatRange(from = .0, to = XYZ_WHITE_REFERENCE_X) z: Double,
        outLab: DoubleArray
    )

    /**
     * Convert RGB components to its CIE Lab representative components.
     *
     * <ul>
     * <li>outLab[0] is L [0, 100]</li>
     * <li>outLab[1] is a [-128, 127)</li>
     * <li>outLab[2] is b [-128, 127)</li>
     * </ul>
     *
     * @param r red component value [0, 255]
     * @param g green component value [0, 255]
     * @param b blue component value [0, 255]
     * @param outLab 3-element array which holds the resulting LAB components
     */
    external fun RGBToLab(
        @IntRange(from = 0x0, to = 0xFF) r: Int,
        @IntRange(from = 0x0, to = 0xFF) g: Int,
        @IntRange(from = 0x0, to = 0xFF) b: Int,
        outLab: DoubleArray
    )

    /**
     * Convert RGB components to HSL (hue-saturation-lightness).
     * <ul>
     * <li>outHsl[0] is Hue [0, 360)</li>
     * <li>outHsl[1] is Saturation [0, 1]</li>
     * <li>outHsl[2] is Lightness [0, 1]</li>
     * </ul>
     *
     * @param r red component value [0, 255]
     * @param g green component value [0, 255]
     * @param b blue component value [0, 255]
     * @param outHsl 3-element array which holds the resulting HSL components
     */
    external fun RGBToHSL(
        @IntRange(from = 0x0, to = 0xFF) r: Int,
        @IntRange(from = 0x0, to = 0xFF) g: Int,
        @IntRange(from = 0x0, to = 0xFF) b: Int,
        outHsl: FloatArray
    )

    /**
     * Converts a color from CIE Lab to CIE XYZ representation.
     *
     * <p>The resulting XYZ representation will use the D65 illuminant and the CIE
     * 2° Standard Observer (1931).</p>
     *
     * <ul>
     * <li>outXyz[0] is X [0, 95.047)</li>
     * <li>outXyz[1] is Y [0, 100)</li>
     * <li>outXyz[2] is Z [0, 108.883)</li>
     * </ul>
     *
     * @param l L component value [0, 100]
     * @param a A component value [-128, 127)
     * @param b B component value [-128, 127)
     * @param outXyz 3-element array which holds the resulting XYZ components
     */
    external fun LABToXYZ(
        @FloatRange(from = .0, to = 100.0) l: Double,
        @FloatRange(from = -128.0, to = 127.0) a: Double,
        @FloatRange(from = -128.0, to = 127.0) b: Double,
        outXyz: DoubleArray
    )

    /**
     * Converts a color from CIE Lab to its RGB representation.
     *
     * @param l L component value [0, 100]
     * @param a A component value [-128, 127]
     * @param b B component value [-128, 127]
     * @return int containing the RGB representation
     */
    @ColorInt
    external fun LABToColor(
        @FloatRange(from = .0, to = 100.0) l: Double,
        @FloatRange(from = -128.0, to = 127.0) a: Double,
        @FloatRange(from = -128.0, to = 127.0) b: Double
    ): Int

    /**
     * Converts a color from CIE XYZ to its RGB representation.
     *
     * <p>This method expects the XYZ representation to use the D65 illuminant and the CIE
     * 2° Standard Observer (1931).</p>
     *
     * @param x X component value [0, 95.047)
     * @param y Y component value [0, 100)
     * @param z Z component value [0, 108.883)
     * @return int containing the RGB representation
     */
    @ColorInt
    external fun XYZToColor(
        @FloatRange(from = .0, to = XYZ_WHITE_REFERENCE_X) x: Double,
        @FloatRange(from = .0, to = XYZ_WHITE_REFERENCE_Y) y: Double,
        @FloatRange(from = .0, to = XYZ_WHITE_REFERENCE_Z) z: Double
    ): Int

    /**
     * Convert HSL (hue-saturation-lightness) components to a RGB color.
     * <ul>
     * <li>hsl[0] is Hue [0, 360)</li>
     * <li>hsl[1] is Saturation [0, 1]</li>
     * <li>hsl[2] is Lightness [0, 1]</li>
     * </ul>
     * If hsv values are out of range, they are pinned.
     *
     * @param hsl 3-element array which holds the input HSL components
     * @return the resulting RGB color
     */
    @ColorInt
    external fun HSLToColor(hsl: FloatArray): Int

    /**
     * Convert the ARGB color to its CIE Lab representative components.
     *
     * @param color the ARGB color to convert. The alpha component is ignored
     * @param outLab 3-element array which holds the resulting LAB components
     */
    external fun colorToLAB(
        @ColorInt color: Int,
        outLab: DoubleArray
    )

    /**
     * Convert the ARGB color to its CIE XYZ representative components.
     *
     * <p>The resulting XYZ representation will use the D65 illuminant and the CIE
     * 2° Standard Observer (1931).</p>
     *
     * <ul>
     * <li>outXyz[0] is X [0, 95.047)</li>
     * <li>outXyz[1] is Y [0, 100)</li>
     * <li>outXyz[2] is Z [0, 108.883)</li>
     * </ul>
     *
     * @param color the ARGB color to convert. The alpha component is ignored
     * @param outXyz 3-element array which holds the resulting LAB components
     */
    external fun colorToXYZ(
        @ColorInt color: Int,
        outXyz: DoubleArray
    )

    /**
     * Convert the ARGB color to its HSL (hue-saturation-lightness) components.
     * <ul>
     * <li>outHsl[0] is Hue [0, 360)</li>
     * <li>outHsl[1] is Saturation [0, 1]</li>
     * <li>outHsl[2] is Lightness [0, 1]</li>
     * </ul>
     *
     * @param color the ARGB color to convert. The alpha component is ignored
     * @param outHsl 3-element array which holds the resulting HSL components
     */
    external fun colorToHSL(
        @ColorInt color: Int,
        outHsl: FloatArray
    )

    /**
     * Calculates the difference between 2 colors.
     *
     * @param a first Color value
     * @param b second Color value
     * @return color difference
     */
    external fun calculateColorDifference(
        @ColorInt a: Int,
        @ColorInt b: Int
    ): Double

    /**
     * Returns the luminance of a color as a float between {@code 0.0} and {@code 1.0}.
     * <p>Defined as the Y component in the XYZ representation of {@code color}.</p>
     */
    @FloatRange(from = .0, to = 1.0)
    external fun calculateLuminance(@ColorInt color: Int): Double

    /**
     * Returns the contrast ratio between {@code foreground} and {@code background}.
     * {@code background} must be opaque.
     * <p>
     * Formula defined
     * <a href="http://www.w3.org/TR/2008/REC-WCAG20-20081211/#contrast-ratiodef">here</a>.
     */
    external fun calculateContrast(
        @ColorInt foreground: Int,
        @ColorInt background: Int
    ): Double

    /**
     * Inverts the given color.
     *
     * @param color Color value
     * @return inverted color
     */
    @ColorInt
    external fun invertColor(@ColorInt color: Int): Int

    /**
     * Blend between two ARGB colors using the given ratio.
     *
     * <p>A blend ratio of 0.0 will result in {@code color1}, 0.5 will give an even blend,
     * 1.0 will result in {@code color2}.</p>
     *
     * @param color1 the first ARGB color
     * @param color2 the second ARGB color
     * @param ratio the blend ratio of {@code color1} to {@code color2}
     */
    @ColorInt
    external fun blendARGB(
        @ColorInt color1: Int,
        @ColorInt color2: Int,
        @FloatRange(from = .0, to = 1.0) ratio: Float
    ): Int
}