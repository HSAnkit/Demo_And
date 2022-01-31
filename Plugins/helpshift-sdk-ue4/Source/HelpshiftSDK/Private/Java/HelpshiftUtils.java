package com.helpshift.unrealsdk;

import android.app.Activity;
import android.app.Application;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;

import com.helpshift.Helpshift;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Random;

public class HelpshiftUtils {
	public static final String DELEGATE_INTENT = "delegateIntent";
	private static boolean isHelpshiftInitSuccessful;

	public static boolean installWithCachedValues(Context context) {
		if (isHelpshiftInitSuccessful) {
			return true;
		}

		try {
			HelpshiftPreferences storage = HelpshiftPreferences.getInstance(context);
			String domain = storage.getString(HelpshiftPreferences.DOMAIN_NAME);
			String platformId = storage.getString(HelpshiftPreferences.PLATFORM_ID);
			HashMap<String, Object> config = storage.getMap(HelpshiftPreferences.INSTALL_CONFIG);
			Helpshift.install((Application) context.getApplicationContext(), platformId, domain, config);

			isHelpshiftInitSuccessful = true;
			return true;
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		return false;
	}

	public static PendingIntent wrapPendingIntentWithIntermediateActivity(Context context, PendingIntent originalPendingIntent) {
		Intent intermediateActivityIntent = new Intent(context, HelpshiftBridgeActivity.class);

		// Insert the actual intent to be called from delegate after dex is loaded.
		intermediateActivityIntent.putExtra(DELEGATE_INTENT, originalPendingIntent);

		return PendingIntent.getActivity(context, new Random().nextInt(), intermediateActivityIntent, PendingIntent.FLAG_CANCEL_CURRENT);
	}

	public static HashMap<String, Object> toMap(JSONObject object) throws JSONException {
		HashMap<String, Object> map = new HashMap<>();
		Iterator keys = object.keys();
		while (keys.hasNext()) {
			String key = (String) keys.next();
			map.put(key, fromJson(object.get(key)));
		}
		return map;
	}

	public static List toList(JSONArray array) throws JSONException {
		List list = new ArrayList();
		for (int i = 0; i < array.length(); i++) {
			list.add(fromJson(array.get(i)));
		}
		return list;
	}

	private static Object fromJson(Object json) throws JSONException {
		if (json == JSONObject.NULL) {
			return null;
		}
		else if (json instanceof JSONObject) {
			return toMap((JSONObject) json);
		}
		else if (json instanceof JSONArray) {
			return toList((JSONArray) json);
		}
		else {
			return json;
		}
	}
}
