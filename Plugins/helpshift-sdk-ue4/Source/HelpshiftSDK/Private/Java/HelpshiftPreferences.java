package com.helpshift.unrealsdk;

import android.content.Context;
import android.content.SharedPreferences;

import com.helpshift.util.Utils;

import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class HelpshiftPreferences {
	private static HelpshiftPreferences storage;
	private final SharedPreferences sharedPreferences;

	public static final String DOMAIN_NAME = "domainName";
	public static final String PLATFORM_ID = "platformId";
	public static final String INSTALL_CONFIG = "installConfig";


	private HelpshiftPreferences(Context context) {
		this.sharedPreferences = context.getSharedPreferences("__helpshift_sdkx_ue4_prefs", Context.MODE_PRIVATE);
	}

	public static HelpshiftPreferences getInstance(Context context) {
		if (storage == null) {
			synchronized (HelpshiftPreferences.class) {
				if (storage == null) {
					storage = new HelpshiftPreferences(context);
				}
			}
		}

		return storage;
	}

	public void put(String key, String value) {

		if (Utils.isEmpty(key)) {
			return;
		}

		SharedPreferences.Editor editor = sharedPreferences.edit();
		editor.putString(key, value);
		editor.apply();
	}

	public String getString(String key) {
		if (Utils.isEmpty(key)) {
			return "";
		}
		return sharedPreferences.getString(key, "");
	}

	public void putMap(String key, Map<String, Object> map) {

		if (Utils.isEmpty(key)) {
			return;
		}

		SharedPreferences.Editor editor = sharedPreferences.edit();

		JSONObject jsonObject = new JSONObject(map);
		editor.putString(key, jsonObject.toString());
		editor.apply();
	}

	public HashMap<String, Object> getMap(String key) {
		if (Utils.isEmpty(key)) {
			return new HashMap<>();
		}
		String jsonStringOfMap = sharedPreferences.getString(key, "");
		if (Utils.isEmpty(jsonStringOfMap)) {
			return new HashMap<>();
		}
		return new HashMap<>(Utils.jsonStringToMap(jsonStringOfMap));
	}
}
