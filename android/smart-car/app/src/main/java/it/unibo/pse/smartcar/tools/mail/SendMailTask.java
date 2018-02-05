package it.unibo.pse.smartcar.tools.mail;


import java.io.UnsupportedEncodingException;
import java.util.Arrays;

import android.os.AsyncTask;
import android.util.Log;

import javax.mail.MessagingException;

import it.unibo.pse.smartcar.utils.C;

public class SendMailTask extends AsyncTask<Void, Void, Boolean> {

    private static final String USERNAME = "pse.student.unibo@gmail.com";
    private static final String PASSWORD = "pse.student";

    private String[] toList;
    private String subject;
    private String body;

    public SendMailTask(String[] toList, String subject, String body){
        this.toList = Arrays.copyOf(toList,toList.length);
        this.subject = subject;
        this.body = body;
    }

    @Override
    protected Boolean doInBackground(Void... params) {
        try {
            GmailClient client = new GmailClient(USERNAME, PASSWORD);
            client.sendEmail(new GmailEmail(subject, body, Arrays.asList(toList)));
        } catch (UnsupportedEncodingException | MessagingException e) {
            return false;
        }

        return true;
    }

    @Override
    protected void onPostExecute(Boolean res) {
        if(res){
            Log.d(C.APP_TAG, "[" + SendMailTask.class.getName() + "] Mail Sended!");
        } else {
            Log.d(C.APP_TAG, "[" + SendMailTask.class.getName() + "] Mail not sendend!");
        }
    }
}

