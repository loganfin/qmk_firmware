#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 10
#define QUICK_TAP_TERM_PER_KEY
#define ONESHOT_TIMEOUT 5000
#define TAPPING_TERM 200

#ifdef HAPTIC_ENABLE
#    define DRV2605L_FB_ERM_LRA 1
#    define DRV2605L_FB_BRAKEFACTOR 3 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#    define DRV2605L_FB_LOOPGAIN 1    /* For  Low:0, Medium:1, High:2, Very High:3 */

#    define DRV2605L_RATED_VOLTAGE 2
#    define DRV2605L_V_PEAK 2.8
#    define DRV2605L_V_RMS 2.0
#    define DRV2605L_F_LRA 150 /* resonance freq */

#    define DRV2605L_GREETING DRV2605L_EFFECT_750_MS_ALERT_100
#    define DRV2605L_DEFAULT_MODE DRV2605L_EFFECT_BUZZ_1_100

#    define SPLIT_HAPTIC_ENABLE

#    define NO_HAPTIC_ALPHA
#    define NO_HAPTIC_PUNCTUATION
#    define NO_HAPTIC_LOCKKEYS
#    define NO_HAPTIC_NAV
#    define NO_HAPTIC_NUMERIC
#endif
