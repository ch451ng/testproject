package it.unibo.pse.smartcar.tools.bt;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Message;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

import it.unibo.pse.smartcar.exceptions.BtMessageTooBigException;
import it.unibo.pse.smartcar.activities.ActiveModeActivity;
import it.unibo.pse.smartcar.utils.C;

public class BluetoothChannelManager implements Runnable {

    private volatile boolean isConnected = false;
    private volatile boolean stop = false;

    private BluetoothDevice targetDevice = null;

    private BluetoothSocket btSocket;
    private InputStream btInStream;
    private OutputStream btOutStream;

    private static BluetoothChannelManager instance = new BluetoothChannelManager();

    private BluetoothChannelManager(){ }

    public static BluetoothChannelManager getInstance(){
        return instance;
    }

    @Override
    public void run() {

        try {
            btSocket = targetDevice.createRfcommSocketToServiceRecord(UUID.fromString(C.BT_TARGET_DEVICE_UUID));
            btSocket.connect();

            btInStream = btSocket.getInputStream();
            btOutStream = btSocket.getOutputStream();

            isConnected = true;

            Log.d(C.APP_TAG,"BT connected");

            Message m = new Message();
            m.obj = C.BT_CONNECTION_ACK;
            ActiveModeActivity.getHandler().sendMessage(m);

        } catch (IOException e) {
            Log.d(C.APP_TAG,"[BCM] Unable to create RFComm Channel or unable to connect to the created RFComm Channel!");
            stop = true;
        }

        while(!stop){
            try {
                int cnt = 0, size = btInStream.read();

                StringBuilder buffer = new StringBuilder("");

                while (cnt < size) {
                    buffer.append((char) btInStream.read());
                    cnt++;
                }

                Log.d(C.APP_TAG, "message received: " + buffer);

                Message m = new Message();
                m.obj = buffer.toString();
                ActiveModeActivity.getHandler().sendMessage(m);
            } catch (Exception e) {
                Log.e(C.APP_TAG, e.toString());
            }
        }
    }

    public boolean sendMessage(String msg) throws BtMessageTooBigException{
        if (!isConnected)
            return false;

        if (msg.length() > C.BT_MAX_MESSAGE_LENGTH) {
            throw new BtMessageTooBigException();
        }

        char[] array = msg.toCharArray();
        byte[] bytes = new byte[array.length + 1];

        bytes[0] = (byte) msg.length();

        for (int i = 0; i < array.length; i++) {
            bytes[i + 1] = (byte) array[i];
        }

        try {
            btOutStream.write(bytes);
            btOutStream.flush();
            Log.d(C.APP_TAG,"message sended: " + msg);
        } catch (IOException ex) {
            Log.e(C.APP_TAG, ex.toString());
            return false;
        }

        return true;
    }

    public boolean isConnected(){
        return isConnected;
    }

    public void setTargetDevice(BluetoothDevice target){
        this.targetDevice = target;
    }

    public void tearDown(){
        this.stop = true;

        try {
            btSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
