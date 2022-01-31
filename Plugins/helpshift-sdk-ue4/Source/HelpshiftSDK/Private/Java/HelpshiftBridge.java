// Copyright (c) 2021 Helpshift

package com.helpshift.unrealsdk;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Context;
import android.util.Log;

import com.helpshift.HSPluginEventBridge;
import com.helpshift.Helpshift;
import com.helpshift.HelpshiftAuthenticationFailureReason;
import com.helpshift.HelpshiftEventsListener;
import com.helpshift.UnsupportedOSVersionException;

import java.util.Map;

import com.epicgames.ue4.GameActivity;

public class HelpshiftBridge {

	public static native void OnHelpshiftEventOccurred(String eventName, Map<String, Object> data);

	public static native void OnHelpshiftAuthError(int type);

	private static HelpshiftEventsListener helpshiftEventsListener;

	public static void init(final Activity context, String domainName, String appId, Map<String, Object> config) {
		HelpshiftPreferences storage = HelpshiftPreferences.getInstance(context);
		storage.putMap(HelpshiftPreferences.INSTALL_CONFIG, config);
		storage.put(HelpshiftPreferences.DOMAIN_NAME, domainName);
		storage.put(HelpshiftPreferences.PLATFORM_ID, appId);

		try {
			HSPluginEventBridge.setPluginEventsAPI(new HSPluginEventBridge.PluginEventsAPI() {
				@Override
				public PendingIntent getPendingIntentForNotification(Context context, PendingIntent pendingIntent) {
					return HelpshiftUtils.wrapPendingIntentWithIntermediateActivity(context, pendingIntent);
				}

				@Override
				public boolean shouldCallFirstForegroundEvent() {
					return GameActivity.Get() != null;
				}
			});

			modifyParameters(context, config);

			Helpshift.install(context.getApplication(), appId, domainName, config);

			helpshiftEventsListener = createHelpshiftDelegate();
			Helpshift.setHelpshiftEventsListener(helpshiftEventsListener);
		} catch (UnsupportedOSVersionException e) {
			e.printStackTrace();
		}
	}

	static HelpshiftEventsListener createHelpshiftDelegate() {
		return new HelpshiftEventsListener() {
			@Override
			public void onEventOccurred(final String eventName, final Map<String, Object> data) {
				Log.d("HelpshiftBridge", "onEventOccurred");
				OnHelpshiftEventOccurred(eventName, data);
			}

			@Override
			public void onUserAuthenticationFailure(final HelpshiftAuthenticationFailureReason reason) {
				Log.d("HelpshiftBridge", "onUserAuthenticationFailure");
				int failureType = reason.ordinal();
				OnHelpshiftAuthError(failureType);
			}
		};
	}

	public static void showConversation(Activity context, Map<String, Object> parameters, String[] tags, Map<String, Object> customIssueFields) {
		parameters.put("tags", tags);
		parameters.put("customIssueFields", customIssueFields);
		Helpshift.showConversation(context, parameters);
	}

	public static void showFaq(Activity context, Map<String, Object> parameters) {
		Helpshift.showFAQs(context, parameters);
	}

	public static void showFaqSection(Activity context, String section, Map<String, Object> parameters) {
		Helpshift.showFAQSection(context, section, parameters);
	}

	public static void showFaqQuestion(Activity context, String question, Map<String, Object> parameters) {
		Helpshift.showSingleFAQ(context, question, parameters);
	}

	public static void setLanguage(String language) {
		Helpshift.setLanguage(language);
	}

	public static void login(Map<String, String> parameters) {
		Helpshift.login(parameters);
	}

	public static void logout() {
		Helpshift.logout();
	}

	public static void clearAnonymousUserOnLogin() {
		Helpshift.clearAnonymousUserOnLogin();
	}

	public static void registerPushToken(String token) {
		Helpshift.registerPushToken(token);
	}

	public static void handlePush(Map<String, String> parameters) {
		Helpshift.handlePush(parameters);
	}

	public static void handlePushCached(Context context, Map<String, String> parameters) {
		HelpshiftUtils.installWithCachedValues(context);
		Helpshift.handlePush(parameters);
	}

	public static void requestUnreadMessageCount(boolean fetchFromServer) {
		Helpshift.requestUnreadMessageCount(fetchFromServer);
	}

	public static void handleApplicationState(boolean isPaused) {
		if (isPaused) {
			Helpshift.onAppBackground();
		} else {
			Helpshift.onAppForeground();
		}
	}

	static int getIconId(Activity context, String fileName) {
		String defaultPackage = context.getPackageName();
		if (defaultPackage != null) {
			Log.d("HelpshiftBridge", "Successfully got the package name");
			try {
				return context.getResources().getIdentifier(fileName, "drawable", context.getPackageName());
			} catch (Exception e) {
				return 0;
			}
		}

		Log.d("HelpshiftBridge", "Could not get the package name. Returning 0.");
		return 0;
	}

	static int getSoundId(Activity context, String fileName) {
		String defaultPackage = context.getPackageName();
		if (defaultPackage != null) {
			Log.d("HelpshiftBridge", "Successfully got the package name");
			try {
				return context.getResources().getIdentifier(fileName, "raw", context.getPackageName());
			} catch (Exception e) {
				return 0;
			}
		}

		Log.d("HelpshiftBridge", "Could not get the package name. Returning 0.");
		return 0;
	}

	static void modifyParameters(Activity context, Map<String, Object> parameters) {
		if (parameters.containsKey("notificationIcon")) {
			String iconName = (String) parameters.get("notificationIcon");
			parameters.put("notificationIcon", getIconId(context, iconName));
		}

		if (parameters.containsKey("notificationLargeIcon")) {
			String iconName = (String) parameters.get("notificationLargeIcon");
			parameters.put("notificationLargeIcon", getIconId(context, iconName));
		}

		if (parameters.containsKey("notificationSoundId")) {
			String soundName = (String) parameters.get("notificationSoundId");
			parameters.put("notificationSoundId", getSoundId(context, soundName));
		}
	}
}
