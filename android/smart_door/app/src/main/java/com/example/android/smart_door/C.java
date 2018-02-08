package com.example.android.smart_door;


public class C {
    public static final String APP_TAG = "C04";

    public static final String BT_TARGET_DEVICE_NAME = "isi00"; //TODO: modificare con il nome del device target!

    public static final String BT_TARGET_DEVICE_UUID = "00001101-0000-1000-8000-00805F9B34FB";

    public static final int BT_MAX_MESSAGE_LENGTH = 255;

    //public static final String SP_NAME = "PSE-3-SharedPreferences";

    public static final String BT_MSG_CAR_STATUS_STOPPED = "sc:m0";
    public static final String BT_MSG_CAR_STATUS_DRIVING = "sc:m1";
    public static final String BT_MSG_CAR_STATUS_PARKING = "sc:m2";

    public static final String BT_MSG_CAR_COLLISION_DETECTED = "sc:c";
    public static final String BT_MSG_CAR_RANGE_PREFIX = "sc:r";
    public static final String BT_MSG_NOCARSINRANGE = "sc:roff";

    public static final String BT_MSG_CAR_DEFENSE_PREFIX = "sc:d";
    public static final String BT_MSG_CAR_DEFENSE_OFF = "sc:doff";

    public static  final String BT_CONNECTION_ACK = "connected";

    public static final String UoM = "cm";
    public static final String DEGREE_SYM = "°";
}
