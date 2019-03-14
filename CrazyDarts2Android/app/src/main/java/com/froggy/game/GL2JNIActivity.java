/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.froggy.game;

import android.app.Activity;
import android.os.Bundle;
import android.content.Context;
import android.util.Log;
import android.view.WindowManager;

import java.io.File;


public class GL2JNIActivity extends Activity {

    GL2JNIView mView;
    private JavaOutlets mOutlets;

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);

        System.out.println("ON_CREATE...");

        mOutlets = new JavaOutlets();
        GL2JNILib.NativeAppShellPreinitialize();

        File aFile = getDir("documents", Context.MODE_PRIVATE);
        String aDocumentsDirectory = aFile.getAbsolutePath();
        aDocumentsDirectory = getFilesDir().getAbsolutePath();
        aDocumentsDirectory += "/";

        GL2JNILib.NativeAppShellSetDirectoryDocuments(aDocumentsDirectory);


        mView = new GL2JNIView(getApplication());
	    setContentView(mView);
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
        GL2JNILib.NativeAppShellPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();

        GL2JNILib.NativeAppShellResume();
    }




}
