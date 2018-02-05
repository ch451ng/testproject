package it.unibo.pse.smartcar.activities;

import android.Manifest;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.Switch;

import java.util.Set;

import it.unibo.pse.smartcar.tools.bt.BluetoothChannelManager;
import it.unibo.pse.smartcar.utils.C;
import it.unibo.pse.smartcar.R;

public class MainActivity extends AppCompatActivity {

    private static final int REQUEST_ENABLE_BT = 1;
    private static final int ACCESS_FINE_LOCATION_REQUEST = 2;

    private BluetoothDevice btTargetDevice;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initUI();

        checkBluetoothPrerequisites();

        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, ACCESS_FINE_LOCATION_REQUEST );
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        shutdown();
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        shutdown();
    }

    @Override
    public void onActivityResult (int reqID , int res , Intent data ){

        switch (reqID){
            case REQUEST_ENABLE_BT:
                if(res == RESULT_OK){
                    Log.d(C.APP_TAG,"Bluetooth enabling request granted!");
                    checkBluetoothPrerequisites();
                }

                if(res == RESULT_CANCELED){
                    Log.d(C.APP_TAG,"Bluetooth enabling request rejected!");
                    showInfoAlert("Bluetooth Error!", "User has rejected the bluetooth activation request!\n\nGoing to shutdown...",
                            new DialogInterface.OnClickListener(){
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                    dialog.dismiss();
                                    MainActivity.this.finish();
                                }
                            }
                    );
                }
                break;

            default:
                break;
        }
    }

    private void initUI() {
        Button drivingModeButton = (Button) findViewById(R.id.start_button);
        drivingModeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(btTargetDevice != null && !BluetoothChannelManager.getInstance().isConnected()){
                    BluetoothChannelManager.getInstance().setTargetDevice(btTargetDevice);
                    new Thread(BluetoothChannelManager.getInstance()).start();
                }

                startActivity(new Intent(MainActivity.this, ActiveModeActivity.class));
            }
        });

        Switch mailSettingSwitch = (Switch) findViewById(R.id.settings_email_switch);
        mailSettingSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

                SharedPreferences pref = getSharedPreferences(C.SP_NAME, Context.MODE_PRIVATE);
                SharedPreferences.Editor editor = pref.edit();

                if(isChecked){
                    editor.putBoolean(C.SP_SEND_MAIL_ITEM, true);
                } else {
                    editor.putBoolean(C.SP_SEND_MAIL_ITEM, false);
                }

                editor.apply();
            }
        });

        mailSettingSwitch.setChecked(true);
    }

    @Override
    public void onRequestPermissionsResult(int reqCode, @NonNull String permissions[], @NonNull int[] res) {
        switch (reqCode) {
            case ACCESS_FINE_LOCATION_REQUEST:
                if (res.length > 0 && res[0] == PackageManager.PERMISSION_GRANTED) {
                    Log.d(C.APP_TAG,"Location permission granted!");
                } else {
                    Log.d(C.APP_TAG,"Location permission denied!");
                }
                break;
        }
    }

    private void checkBluetoothPrerequisites(){
        BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();

        if(btAdapter != null){
            //BT Available
            if(btAdapter.isEnabled()){
                //BT enabled
                btTargetDevice = lookingForBtTargetDevice(C.BT_TARGET_DEVICE_NAME);

                if(btTargetDevice == null){
                    Log.d(C.APP_TAG,"Bluetooth target device [" + C.BT_TARGET_DEVICE_NAME + "] not found!");
                    showInfoAlert("Bluetooth Error!", "Bluetooth target device [\" + BT_TARGET_DEVICE_NAME + \"] not found!\n\nGoing to shutdown...",
                        new DialogInterface.OnClickListener(){
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                dialog.dismiss();
                                MainActivity.this.finish();
                            }
                        }
                    );
                }
            } else {
                //BT not enabled
                startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), REQUEST_ENABLE_BT);
            }
        } else {
            //BT unavailable
            Log.d(C.APP_TAG,"Bluetooth unavailable on this device!");
            showInfoAlert("Bluetooth Error!", "Bluetooth unavailable on this device!\n\nGoing to shutdown...",
                new DialogInterface.OnClickListener(){
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                        MainActivity.this.finish();
                    }
                }
            );
        }
    }

    @Nullable
    private BluetoothDevice lookingForBtTargetDevice(String name){
        Set<BluetoothDevice> pairedList = BluetoothAdapter.getDefaultAdapter().getBondedDevices();
        if (pairedList.size() > 0) {
            for (BluetoothDevice device : pairedList) {
                if (device.getName().equals(name)) {
                    return device;
                }
            }
        }

        return null;
    }

    private void shutdown(){
        if(BluetoothChannelManager.getInstance().isConnected()){
            BluetoothChannelManager.getInstance().tearDown();
        }
    }

    private void showInfoAlert(String title, String message, DialogInterface.OnClickListener action){
        AlertDialog dialog = new AlertDialog.Builder(MainActivity.this)
                .setTitle(title)
                .setMessage(message)
                .setCancelable(false)
                .setPositiveButton("OK", action)
                .create();

        dialog.show();
    }
}
