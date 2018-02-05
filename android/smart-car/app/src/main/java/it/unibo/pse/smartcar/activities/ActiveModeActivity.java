package it.unibo.pse.smartcar.activities;

import android.Manifest;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.location.Location;
import android.location.LocationManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.TextView;

import java.lang.ref.WeakReference;
import java.util.Calendar;
import java.util.List;
import java.util.Locale;

import it.unibo.pse.smartcar.R;
import it.unibo.pse.smartcar.exceptions.BtMessageTooBigException;
import it.unibo.pse.smartcar.tools.bt.BluetoothChannelManager;
import it.unibo.pse.smartcar.tools.mail.SendMailTask;
import it.unibo.pse.smartcar.utils.C;
import it.unibo.pse.smartcar.utils.CarStatus;

public class ActiveModeActivity extends AppCompatActivity {

    private Button drivingBtn, parkingBtn, stopBtn;

    private CarStatus carStatus;

    private static UiHandler uiHandler;

    private final String[] alertsReceiversAddresses = new String[]{"pse.student.unibo@gmail.com"};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_active_mode);

        initUI();

        uiHandler = new UiHandler(this);
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        switchMode(CarStatus.IDLE);
    }

    private void initUI() {
        drivingBtn = (Button) findViewById(R.id.driving_mode_btn);
        drivingBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                switchMode(CarStatus.DRIVING);
            }
        });

        parkingBtn = (Button) findViewById(R.id.parking_mode_btn);
        parkingBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                switchMode(CarStatus.PARKING);
            }
        });

        stopBtn = (Button) findViewById(R.id.stop_btn);
        stopBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                switchMode(CarStatus.IDLE);
            }
        });

        drivingBtn.setEnabled(false);
        parkingBtn.setEnabled(false);
        stopBtn.setEnabled(false);

        initUI_driving();
        initUI_parking();
    }

    private void initUI_driving() {
        ((TextView) findViewById(R.id.distance_label)).setText(getString(R.string.null_distance));

        manageDistanceLevelIndicator(Integer.MAX_VALUE);

        SeekBar sb = (SeekBar) findViewById(R.id.serv_mot_seekbar);
        sb.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            final int multiplier = 10;

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                ((TextView) findViewById(R.id.serv_mot_val_label)).setText((progress * multiplier) + C.DEGREE_SYM);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                int value = seekBar.getProgress() * multiplier;
                requestSendBtMessage(C.BT_MSG_CAR_DEFENSE_PREFIX + value);
            }
        });
        sb.setProgress(0);

        Button defenseOffBtn = (Button) findViewById(R.id.defenseOffBtn);
        defenseOffBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                requestSendBtMessage(C.BT_MSG_CAR_DEFENSE_OFF);
                findViewById(R.id.contact_layout).setVisibility(View.GONE);
            }
        });

        findViewById(R.id.driving_layout).setVisibility(View.GONE);
        findViewById(R.id.contact_layout).setVisibility(View.GONE);
    }

    private void initUI_parking() {
        findViewById(R.id.parking_layout).setVisibility(View.GONE);
    }

    private void manageDistanceLevelIndicator(int value) {
        TextView[] levels = new TextView[]{
                (TextView) findViewById(R.id.distance_level_1),
                (TextView) findViewById(R.id.distance_level_2),
                (TextView) findViewById(R.id.distance_level_3),
                (TextView) findViewById(R.id.distance_level_4),
                (TextView) findViewById(R.id.distance_level_5)
        };

        for (TextView t : levels)
            t.setBackgroundColor(Color.WHITE);

        int th = value >= 30 ? 0 : (value >= 25 ? 1 : (value >= 20 ? 2 : (value >= 15 ? 3 : (value >= 10 ? 4 : 5))));

        for (int i = 0; i < th; i++) {
            levels[i].setBackgroundColor(Color.RED);
        }
    }

    private void switchMode(CarStatus status) {
        switch (status) {
            case DRIVING:
                drivingBtn.setEnabled(false);
                parkingBtn.setEnabled(true);
                stopBtn.setEnabled(true);

                findViewById(R.id.driving_layout).setVisibility(View.VISIBLE);
                findViewById(R.id.parking_layout).setVisibility(View.GONE);

                requestSendBtMessage(C.BT_MSG_CAR_STATUS_DRIVING);

                carStatus = CarStatus.DRIVING;

                break;

            case PARKING:
                drivingBtn.setEnabled(true);
                parkingBtn.setEnabled(false);
                stopBtn.setEnabled(true);

                findViewById(R.id.driving_layout).setVisibility(View.GONE);
                findViewById(R.id.parking_layout).setVisibility(View.VISIBLE);

                requestSendBtMessage(C.BT_MSG_CAR_STATUS_PARKING);

                carStatus = CarStatus.PARKING;

                break;

            case IDLE:
                drivingBtn.setEnabled(true);
                parkingBtn.setEnabled(true);
                stopBtn.setEnabled(false);

                findViewById(R.id.driving_layout).setVisibility(View.GONE);
                findViewById(R.id.parking_layout).setVisibility(View.GONE);

                requestSendBtMessage(C.BT_MSG_CAR_STATUS_STOPPED);

                carStatus = CarStatus.IDLE;

                finish();

                break;
        }
    }

    private void manageContactInParkingMode(){
        double lat = 0, lon = 0;
        Location here = getLastKnownLocation();

        if(here != null){
            lat = here.getLatitude();
            lon = here.getLongitude();
        }

        String message = Calendar.getInstance(Locale.ITALY).getTime().toString() + "\n" +
                "Contact Detected @ location("+lat+" , "+lon+")";

        checkAndOptionallySendMail(message);

        ((TextView) findViewById(R.id.parkingLog)).append(message + "\n\n");

        findViewById(R.id.scrollView).post(new Runnable() {
            @Override
            public void run() {
                ((ScrollView) findViewById(R.id.scrollView)).fullScroll(ScrollView.FOCUS_DOWN);
            }
        });
    }

    private void checkAndOptionallySendMail(String body){
        SharedPreferences pref = getSharedPreferences(C.SP_NAME, Context.MODE_PRIVATE);

        if(pref.getBoolean(C.SP_SEND_MAIL_ITEM, false)){
            //SendMail
            new SendMailTask(
                    alertsReceiversAddresses,
                    C.APP_TAG + " - Contact Notification",
                    body
            ).execute();
        }
    }

    private void requestSendBtMessage(String message){
        try {
            BluetoothChannelManager.getInstance().sendMessage(message);
        } catch (BtMessageTooBigException e) {
            e.printStackTrace();
        }
    }

    @Nullable
    private Location getLastKnownLocation() {
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            return null;
        }

        LocationManager lm = (LocationManager) getApplicationContext().getSystemService(LOCATION_SERVICE);
        List<String> providers = lm.getProviders(true);

        Location bestLocation = null;

        for (String provider : providers) {
            Location l = lm.getLastKnownLocation(provider);
            if (l == null) {
                continue;
            }
            if (bestLocation == null || l.getAccuracy() < bestLocation.getAccuracy()) {
                bestLocation = l;
            }
        }
        return bestLocation;
    }

    public static UiHandler getHandler(){
        return uiHandler;
    }

    /**
     * UI HANDLER
     */
    public static class UiHandler extends Handler {
        private final WeakReference<ActiveModeActivity> context;

        UiHandler(ActiveModeActivity context){
            this.context = new WeakReference<>(context);
        }

        public void handleMessage(Message msg) {
            String message = msg.obj.toString();

            if(message.equals(C.BT_CONNECTION_ACK)){
                context.get().drivingBtn.setEnabled(true);
            }

            if(message.equals(C.BT_MSG_CAR_COLLISION_DETECTED)){
                if(context.get().carStatus == CarStatus.DRIVING){
                    context.get().findViewById(R.id.contact_layout).setVisibility(View.VISIBLE);
                }

                if(context.get().carStatus == CarStatus.PARKING){
                    context.get().manageContactInParkingMode();
                }
            }

            if(message.equals(C.BT_MSG_NOCARSINRANGE)){
                ((TextView) context.get().findViewById(R.id.distance_label)).setText(context.get().getString(R.string.null_distance));
                context.get().manageDistanceLevelIndicator(Integer.MAX_VALUE);
            } else if(message.startsWith(C.BT_MSG_CAR_RANGE_PREFIX)){
                String value = message.substring(C.BT_MSG_CAR_RANGE_PREFIX.length(), message.length());
                ((TextView) context.get().findViewById(R.id.distance_label)).setText(value + " " + C.UoM);
                context.get().manageDistanceLevelIndicator(Integer.parseInt(value));
            }
        }
    }
}
