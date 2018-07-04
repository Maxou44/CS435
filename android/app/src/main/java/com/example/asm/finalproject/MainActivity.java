package com.example.asm.finalproject;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.media.AudioManager;
import android.media.ToneGenerator;
import android.os.Build;
import android.os.Bundle;
import android.os.IBinder;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.afollestad.materialdialogs.DialogAction;
import com.afollestad.materialdialogs.MaterialDialog;

import org.greenrobot.eventbus.EventBus;
import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.UUID;

@RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN_MR2)
public class MainActivity extends AppCompatActivity implements OnClickDeviceItemListener {

    public static int REQUEST_BLUETOOTH = 1;
    private BluetoothAdapter bTAdapter = BluetoothAdapter.getDefaultAdapter();;
    private DeviceItemAdapter deviceItemAdapter;
    private Intent gattServiceIntent;
    private boolean isBound;
    private ArrayList<ArrayList<BluetoothGattCharacteristic>> mGattCharacteristics =
            new ArrayList<ArrayList<BluetoothGattCharacteristic>>();
    private int [][] caratteristiche = new int [5][2];

    private BluetoothLeService mBluetoothLeService;
    private String mDeviceAddress;

    private final String LIST_NAME = "NAME";
    private final String LIST_UUID = "UUID";

    private TextView morseText;
    private MaterialDialog dialog;
    private ToneGenerator toneGen1;

    private static IntentFilter makeGattUpdateIntentFilter() {
        final IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothLeService.ACTION_GATT_CONNECTED);
        intentFilter.addAction(BluetoothLeService.ACTION_GATT_DISCONNECTED);
        intentFilter.addAction(BluetoothLeService.ACTION_GATT_SERVICES_DISCOVERED);
        intentFilter.addAction(BluetoothLeService.ACTION_DATA_AVAILABLE);
        intentFilter.addAction(BluetoothDevice.ACTION_FOUND);
        return intentFilter;
    }


    private final ServiceConnection mServiceConnection = new ServiceConnection() {

        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            mBluetoothLeService = ((BluetoothLeService.LocalBinder) service).getService();
            if (!mBluetoothLeService.initialize()) {
                //String currentTime = new SimpleDateFormat("HH:mm:ss").format(new Date());
                //DeviceScanActivity.log.add(new visualLog(currentTime,"Unable to initialize Bluetooth"));
                System.out.println("Unable to initialize Bluetooth");
                finish();
            }
            System.out.println("SERVICE CONNECT");
            mBluetoothLeService.connect(mDeviceAddress);
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            mBluetoothLeService = null;
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        morseText = findViewById(R.id.text_morse);
        toneGen1 = new ToneGenerator(AudioManager.STREAM_MUSIC, 100);
        if (CheckBluetooth())
            AskBluetoothPermission();
    }

    private boolean CheckBluetooth() {
        if (bTAdapter == null) {
            new AlertDialog.Builder(this)
                    .setTitle("Not compatible")
                    .setMessage("Your phone does not support Bluetooth")
                    .setPositiveButton("Exit", new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int which) {
                            MainActivity.this.finish();
                        }
                    })
                    .setIcon(android.R.drawable.ic_dialog_alert)
                    .show();
            return false;
        }
        return true;
    }

    private void AskBluetoothPermission() {
        if (!bTAdapter.isEnabled()) {
            Intent enableBT = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBT, REQUEST_BLUETOOTH);
        }
    }

    private final BroadcastReceiver bReciever = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                System.out.println("Device == " + device.getName() + " " + device.getAddress());

                // Create a new device item
                DeviceItem newDevice = new DeviceItem(device);

                // Add it to our adapter
                deviceItemAdapter.add(newDevice);
            } else if (BluetoothLeService.ACTION_DATA_AVAILABLE.equals(action)) {
                System.out.println("ACTION_DATA_AVAILABLE");
            } else if (BluetoothLeService.ACTION_GATT_SERVICES_DISCOVERED.equals(action)) {
                System.out.println("ACTION_GATT_SERVICES_DISCOVERED");
                displayGattServices(mBluetoothLeService.getSupportedGattServices());
            }
        }
    };

    public void OnClickSend(View view) {
        System.out.println("OnClick");
    }

    public void OnClickFindBluetooth(View view) {
        System.out.println("Find Bluetooth");
        registerReceiver(bReciever, makeGattUpdateIntentFilter());
        bTAdapter.startDiscovery();
        deviceItemAdapter = new DeviceItemAdapter(this);
        dialog = new MaterialDialog.Builder(this)
                .title("Bluetooth Search")
                .customView(R.layout.bluetooth_list, false)
                .negativeText("Cancel")
                .onNegative(new MaterialDialog.SingleButtonCallback() {
                    @Override
                    public void onClick(MaterialDialog dialog, DialogAction which) {
                        unregisterReceiver(bReciever);
                        bTAdapter.cancelDiscovery();
                    }
                })
                .build();
        View viewCustom = dialog.getCustomView();
        RecyclerView rv = viewCustom.findViewById(R.id.list);
        rv.setAdapter(deviceItemAdapter);
        rv.setLayoutManager(new LinearLayoutManager(this));
        dialog.show();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        try {
            this.unregisterReceiver(bReciever);
        } catch (IllegalArgumentException ignored) {
        }
    }

    @Override
    public void onStart() {
        super.onStart();
        EventBus.getDefault().register(this);
    }

    @Override
    public void onStop() {
        super.onStop();
        EventBus.getDefault().unregister(this);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMessageEvent(DataReceivedEvent event) {
        final int time;

        if (event.getData().equals("0")) {
            morseText.setText(morseText.getText() + ".");
            time = 0;
        } else {
            time = 1;
            morseText.setText(morseText.getText() + "-");
        }

        new Thread(new Runnable() {
            @Override
            public void run() {
                if (time == 0)
                    toneGen1.startTone(ToneGenerator.TONE_CDMA_ABBR_ALERT, 300);
                else
                    toneGen1.startTone(ToneGenerator.TONE_CDMA_ABBR_ALERT, 12000);
            }
        }).start();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    public void OnClickDeviceItem(DeviceItem deviceItem) {
        if (deviceItem == null || !deviceItem.getName().equals("BlueNRG")) {
            return;
        }
        mDeviceAddress = deviceItem.getAddress();

        gattServiceIntent = new Intent(this, BluetoothLeService.class);

        isBound = getApplicationContext().bindService(gattServiceIntent, mServiceConnection, BIND_AUTO_CREATE);

        Thread dataThread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    int j = 0;
                    while (mGattCharacteristics == null || mGattCharacteristics.size() == 0) {
                        Thread.sleep(500);
                        System.out.println("thread__waiting_data");
                    }
                    BluetoothGattCharacteristic characteristic0 = mGattCharacteristics.get(caratteristiche[0][0]).get(caratteristiche[0][1]);
                    mBluetoothLeService.setCharacteristicNotification(characteristic0, true);
                    Thread.sleep(150);
                    BluetoothGattCharacteristic characteristic4 = mGattCharacteristics.get(caratteristiche[4][0]).get(caratteristiche[4][1]);
                    mBluetoothLeService.setCharacteristicNotification(characteristic4, true);
                    while (true) {
                        for (int i = 1; i <= 3; i++) {
                            BluetoothGattCharacteristic characteristic1 = mGattCharacteristics.get(caratteristiche[i][0]).get(caratteristiche[i][1]);
                            mBluetoothLeService.readCharacteristic(characteristic1);
                            Thread.sleep(500);
                            j++;
                        }
                        Thread.sleep(500);
                        mBluetoothLeService.readRemoteRssi();
                    }
                } catch (Exception e) {
                    e.getLocalizedMessage();
                }
            }
        });
        dataThread.start();

        dialog.dismiss();
    }

    private void displayGattServices(List<BluetoothGattService> gattServices) {
        if (gattServices == null) return;
        String uuid = null;

        String unknownServiceString = "Unknown Service";
        String unknownCharaString = "Unknown Chara";
        ArrayList<HashMap<String, String>> gattServiceData = new ArrayList<HashMap<String, String>>();
        ArrayList<ArrayList<HashMap<String, String>>> gattCharacteristicData
                = new ArrayList<ArrayList<HashMap<String, String>>>();
        mGattCharacteristics = new ArrayList<ArrayList<BluetoothGattCharacteristic>>();


        for (BluetoothGattService gattService : gattServices) {
            HashMap<String, String> currentServiceData = new HashMap<String, String>();
            uuid = gattService.getUuid().toString();
            currentServiceData.put(
                    LIST_NAME, unknownServiceString);
            currentServiceData.put(LIST_UUID, uuid);
            gattServiceData.add(currentServiceData);

            ArrayList<HashMap<String, String>> gattCharacteristicGroupData =
                    new ArrayList<>();
            List<BluetoothGattCharacteristic> gattCharacteristics =
                    gattService.getCharacteristics();
            ArrayList<BluetoothGattCharacteristic> charas =
                    new ArrayList<>();


            for (BluetoothGattCharacteristic gattCharacteristic : gattCharacteristics) {
                charas.add(gattCharacteristic);
                HashMap<String, String> currentCharaData = new HashMap<String, String>();
                uuid = gattCharacteristic.getUuid().toString();
                currentCharaData.put(
                        LIST_NAME, unknownCharaString);
                currentCharaData.put(LIST_UUID, uuid);
                gattCharacteristicGroupData.add(currentCharaData);
            }
            mGattCharacteristics.add(charas);
            gattCharacteristicData.add(gattCharacteristicGroupData);
        }

        int i=0,j;
        for (ArrayList<BluetoothGattCharacteristic> service : mGattCharacteristics){
            j=0;
            for (BluetoothGattCharacteristic gatt : service){
                UUID uid = gatt.getUuid();
                if (BluetoothLeService.UUID_ACCELERATION.equals(uid)) {
                    String currentTime = new SimpleDateFormat("HH:mm:ss").format(new Date());
                    //DeviceScanActivity.log.add(new visualLog(currentTime,"Found acceleration"));
                    caratteristiche[0][0]=i;
                    caratteristiche[0][1]=j;
                    Log.d("stefano", "UUID_ACCELERATION");
                }
                j++;
            }
            i++;
        }
    }

}
