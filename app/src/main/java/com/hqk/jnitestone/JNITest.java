package com.hqk.jnitestone;

public class JNITest  {
    static {
        System.loadLibrary("native-lib");
    }

    public static native String sayHello();

    public static native String sayHello2();
}
