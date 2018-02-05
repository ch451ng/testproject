package it.unibo.pse.smartcar.tools.mail;

import java.util.List;

class GmailEmail {
    private List<String> toEmailList;
    private String emailSubject;

    private String emailBody;

    GmailEmail(String emailSubject, String emailBody, List<String> toEmailList){
        this.toEmailList = toEmailList;
        this.emailSubject = emailSubject;
        this.emailBody = emailBody;
    }

    String getBody(){
        return this.emailBody;
    }

    String getSubject(){
        return this.emailSubject;
    }

    List<String> getRecipients(){
        return this.toEmailList;
    }
}
