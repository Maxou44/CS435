package com.example.asm.finalproject;

import android.bluetooth.BluetoothDevice;

/**
 * Created by mart_- on 19/06/2018.
 */

public class DeviceItem {
    private BluetoothDevice bluetoothDevice;

    public DeviceItem(BluetoothDevice bluetoothDevice) {
        this.bluetoothDevice = bluetoothDevice;
    }

    public String getName() {
        return bluetoothDevice.getName() == null ? bluetoothDevice.getAddress() : bluetoothDevice.getName();
    }

    public String getAddress() {
        return bluetoothDevice.getAddress();
    }

    public BluetoothDevice getBluetoothDevice() {
        return bluetoothDevice;
    }
}
