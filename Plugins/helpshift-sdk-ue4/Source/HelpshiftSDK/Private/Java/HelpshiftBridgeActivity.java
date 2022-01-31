package com.helpshift.unrealsdk;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import com.helpshift.core.HSContext;

public class HelpshiftBridgeActivity extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.d("HelpshiftBridgeActivity", "onCreate: 1");
		try {
			if (!HelpshiftUtils.installWithCachedValues(getApplicationContext())) {
				finish();
				Log.d("HelpshiftBridgeActivity", "onCreate: 2");
				return;
			}

			Log.d("HelpshiftBridgeActivity", "onCreate: 3");
			// Synchronously wait for the install call to finish else we have a feature to start the default activity of the app
			// if install is not finished before starting the Helpshift's activity.
			HSContext.getInstance().getHsThreadingService().awaitForSyncExecution();

			// Get the actual intent to be fired to Helpshift.
			Intent intent = getIntent();
			Log.d("HelpshiftBridgeActivity", "onCreate: 4");
			PendingIntent pendingIntent = intent.getParcelableExtra(HelpshiftUtils.DELEGATE_INTENT);
			if (pendingIntent != null) {
				Log.d("HelpshiftBridgeActivity", "onCreate: 5");
				try {
					Log.d("HelpshiftBridgeActivity", "onCreate: 6");
					pendingIntent.send();
				}
				catch (PendingIntent.CanceledException e) {
					Log.d("HelpshiftBridgeActivity", "onCreate: 7");
					e.printStackTrace();
				}
			}
		}
		finally {
			finish();
		}
	}
}
