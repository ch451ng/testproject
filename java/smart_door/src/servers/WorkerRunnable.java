package servers;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.IOException;
import java.net.Socket;

import seiot.modulo_lab_3_3.devices.Serial;
import smart_door.*;


public class WorkerRunnable implements Runnable{

    protected Socket clientSocket = null;
    protected String serverText   = null;
    private Serial serialDevice;

    public WorkerRunnable(Socket clientSocket, String serverText, Serial serialDevice) {
        this.clientSocket = clientSocket;
        this.serverText   = serverText;
        this.serialDevice = serialDevice;
    }

    public void run() {
        try {
            InputStream input  = clientSocket.getInputStream();
            OutputStream output = clientSocket.getOutputStream();
            long time = System.currentTimeMillis();
            serialDevice.sendMsg("TEMP");
            output.write(("HTTP/1.1 200 OK\n\nWorkerRunnable: " +
this.serverText + " - " +
time +
"").getBytes());
            
            output.close();
            input.close();
            System.out.println("Request processed: " + time);
        } catch (IOException e) {
            //report exception somewhere.
            e.printStackTrace();
        }
    }
}