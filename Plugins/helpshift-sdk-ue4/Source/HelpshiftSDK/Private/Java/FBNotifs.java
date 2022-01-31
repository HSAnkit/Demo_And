package com.helpshift.unrealsdk;

import com.google.firebase.messaging.FirebaseMessagingService;
import com.google.firebase.messaging.RemoteMessage;
import com.helpshift.*;
import java.util.*;

public class MyFirebaseMessagingService extends FirebaseMessagingService {
    @Override
    public void onNewToken(String newToken) {
       Helpshift.registerPushToken(newToken);
    }
    @Override
    public void onMessageReceived(RemoteMessage message) {
        Map<String, String> data = message.getData();
        String origin = data.get("origin");
        if (origin != null && origin.equals("helpshift")) {
           Helpshift.handlePush(data);
        }
    }
}