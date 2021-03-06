cmake_minimum_required(VERSION 3.4.1)

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

add_library(gl2jni SHARED

		__DROID.cpp
		AssetConfigMenu.cpp
		AssetWad.cpp
		AssetWadGameEffects.cpp
		AssetWadGameInterface.cpp
		Balloon.cpp
		Bomb.cpp
		BrickHead.cpp
		CameraMenu.cpp
		Constraint.cpp
		core_app_shell.cpp
		core_social.cpp
		core_web.cpp
		Dart.cpp
		DiffuseConfiguration.cpp
		DiffuseLightMenu.cpp
		DragableCanvas.cpp
		EditorMenuAttachment.cpp
		EditorMenuFormation.cpp
		EditorMenuFormationGrid.cpp
		EditorMenuFormationPicker.cpp
		EditorMenuFormationPickerCell.cpp
		EditorMenuFormationSpawnPicker.cpp
		EditorMenuFormationUtilities.cpp
		EditorMenuGameTest.cpp
		EditorMenuGameTestUtils.cpp
		EditorMenuMotion.cpp
		EditorMenuMotionTypePanel.cpp
		EditorMenuObjectClearing.cpp
		EditorMenuPath.cpp
		EditorMenuPathControl.cpp
		EditorMenuPermanent.cpp
		EditorMenuPermanentUtils.cpp
		EditorMenuPermPicker.cpp
		EditorMenuPermSpawnPicker.cpp
		EditorMenuSections.cpp
		EditorMenuSpawn.cpp
		EditorMenuSpawnPicker.cpp
		EditorMenuWavesPicker.cpp
		EffectBalloonBurst.cpp
		EffectDartFadeStar.cpp
		FAchievement.cpp
		FAnimation.cpp
		FApp.cpp
		FBuffer.cpp
		FBufferCache.cpp
		FButton.cpp
		FCanvas.cpp
		FColor.cpp
		FDrawQuad.cpp
		FFile.cpp
		FFileTable.cpp
		FFloatBufferCache.cpp
		FFloatList.cpp
		FFont.cpp
		FGestureCanvas.cpp
		FHashMap.cpp
		FImage.cpp
		FImageBundler.cpp
		FIndexBufferCache.cpp
		FIndexList.cpp
		FIntList.cpp
		FJoystick.cpp
		FJSON.cpp
		FLight.cpp
		FLine.cpp
		FList.cpp
		FloatingCamera.cpp
		FMath.cpp
		FMatrix.cpp
		FModelData.cpp
		FModelDataPacked.cpp
		FModelDataSequence.cpp
		FNotificationCenter.cpp
		FObject.cpp
		FormationCollection.cpp
		FParticle.cpp
		FPointList.cpp
		FPolyPath.cpp
		FPrimitive.cpp
		FQuad.cpp
		FRandomizer.cpp
		FRect.cpp
		FResource.cpp
		FScrollCanvas.cpp
		FScrollCanvasPaged.cpp
		FSize.cpp
		FSlider.cpp
		FSound.cpp
		FSpline.cpp
		FSprite.cpp
		FSpriteSequence.cpp
		FString.cpp
		FTexture.cpp
		FTextureCache.cpp
		FTouchManager.cpp
		FUniforms.cpp
		FVec2.cpp
		FVec3.cpp
		FVertexBuffer.cpp
		FWindow.cpp
		FXML.cpp
		Game.cpp
		GameContainer.cpp
		GameEditor.cpp
		GameEditorGrid.cpp
		GameFormationEditor.cpp
		GameInfoOverlay.cpp
		GameInfoTextBubble.cpp
		GameLevelController.cpp
		GameObject.cpp
		GameOverlay.cpp
		GamePathEditor.cpp
		GamePermanentEditor.cpp
		GameRenderer.cpp
		GameTestEditorOverlay.cpp
		GameTestRunningMainMenu.cpp
		GameTestRunningOverlay.cpp
		GFXApp.cpp
		GraphicsInterface.cpp
		HangingThread.cpp
		HangingThreadKnot.cpp
		HangingThreadSegment.cpp
		HangingThreadTestMenu.cpp
		Level.cpp
		LevelData.cpp
		LevelFormation.cpp
		LevelFormationBlueprint.cpp
		LevelFormationNode.cpp
		LevelFormationTracer.cpp
		LevelFormationTracerBlueprint.cpp
		LevelFormationTracerNode.cpp
		LevelGroup.cpp
		LevelMotionController.cpp
		LevelMotionControllerBlueprint.cpp
		LevelMotionControllerSlice.cpp
		LevelMotionControllerSliceBlueprint.cpp
		LevelNode.cpp
		LevelPath.cpp
		LevelPathBlueprint.cpp
		LevelPermSpawn.cpp
		LevelPermSpawnBlueprint.cpp
		LevelSection.cpp
		LevelSectionBlueprint.cpp
		LevelSectionPermanent.cpp
		LevelSectionPermanentBlueprint.cpp
		LevelSelectorScreen.cpp
		LevelWave.cpp
		LevelWaveBlueprint.cpp
		LevelWaveSpawn.cpp
		LevelWaveSpawnBlueprint.cpp
		LightConfigurationScene.cpp
		OpenGLEngine.cpp
		os_core_app_shell_android.cpp
		os_core_graphics.cpp
		os_core_includes.cpp
		os_core_music_android.cpp
		os_core_outlets_android.cpp
		os_core_social.cpp
		os_core_sound_android.cpp
		os_core_web.cpp
		OSMusicBuffer.cpp
		OSMusicPlayer.cpp
		OSSoundBuffer.cpp
		OSSoundBufferPool.cpp
		PhongConfiguration.cpp
		PhongLightMenu.cpp
		PlatformGraphicsInterface.cpp
		ShaderProgram.cpp
		ShaderProgramModelIndexed.cpp
		ShaderProgramModelIndexedLightedAmbient.cpp
		ShaderProgramModelIndexedLightedDiffuse.cpp
		ShaderProgramModelIndexedLightedPhong.cpp
		ShaderProgramModelIndexedLightedSimpleSpotlight.cpp
		ShaderProgramShape3D.cpp
		ShaderProgramShapeNode.cpp
		ShaderProgramSimpleModel.cpp
		ShaderProgramSimpleModelIndexed.cpp
		ShaderProgramSprite.cpp
		ShaderProgramSpriteNode.cpp
		ShaderProgramSpriteWhite.cpp
		SimpleSpotLightMenu.cpp
		SoundConfigMenu.cpp
		SpotLightSimpleConfiguration.cpp
		StuckDart.cpp
		ToolMenu.cpp
		ToolMenuHeader.cpp
		ToolMenuPanel.cpp
		ToolMenuPanelHeader.cpp
		ToolMenuSection.cpp
		ToolMenuSectionRow.cpp
		Transform2D.cpp
		Transform3D.cpp
		Turtle.cpp
		UIAlignmentPicker.cpp
		UIAlignmentPickerButton.cpp
		UIButton.cpp
		UICheckBox.cpp
		UIElement.cpp
		UIImagePicker.cpp
		UIImagePickerCell.cpp
		UILabel.cpp
		UIRoundedRect.cpp
		UISegment.cpp
		UISegmentButton.cpp
		UISlider.cpp
		UIStepper.cpp
		UITextBox.cpp
		Util_ScreenFrame.cpp
		WadGlobalConfiguration.cpp
		WindSpeedSimulator.cpp
		WindSpeedSimulatorChannel.cpp
		WorldConfigScene.cpp
        )

# add lib dependencies
target_link_libraries(gl2jni
                      android
                      log 
                      EGL
                      GLESv2
		              OpenSLES)

