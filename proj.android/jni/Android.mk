LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Global.cpp \
                   ../../Classes/GameOptions/GameOptions.cpp \
                   ../../Classes/AlphaBetUtils/AlphaBetUtils.cpp \
                   ../../Classes/Hero/Hero.cpp \
                   ../../Classes/LetterBag/LetterBag.cpp \
                   ../../Classes/ShootItem/ShootItem.cpp \
                   ../../Classes/SoundEffect/SoundEffects.cpp \
                   ../../Classes/Extensions/CCAlertView.cpp \
                   ../../Classes/Scene/CharacterLayer/CharacterLayer.cpp \
                   ../../Classes/Scene/AnnounceLayer/AnnounceLayer.cpp \
                   ../../Classes/Scene/ClockLayer/ClockLayer.cpp \
                   ../../Classes/Scene/TargetLayer/TargetLayer.cpp \
                   ../../Classes/Scene/AboutScene.cpp \
                   ../../Classes/Scene/ChooseLetterScene.cpp \
                   ../../Classes/Scene/GameOptionScene.cpp \
                   ../../Classes/Scene/GameResultScene.cpp \
                   ../../Classes/Scene/HighScoreScene.cpp \
                   ../../Classes/Scene/IntroScene.cpp \
                   ../../Classes/Scene/LoadScene.cpp \
                   ../../Classes/Scene/MainMenuScene.cpp \
                   ../../Classes/Scene/MissedLetterScene.cpp \
                   ../../Classes/Scene/GameScene.cpp \
                   ../../Classes/Scene/StoreScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/GameOptions \
					$(LOCAL_PATH)/../../Classes/AlphaBetUtils \
					$(LOCAL_PATH)/../../Classes/LetterBag \
					$(LOCAL_PATH)/../../Classes/Hero \
					$(LOCAL_PATH)/../../Classes/ShootItem \
					$(LOCAL_PATH)/../../Classes/SoundEffect \
					$(LOCAL_PATH)/../../Classes/Extensions \
					$(LOCAL_PATH)/../../Classes/Scene \
					$(LOCAL_PATH)/../../Classes/Scene/CharacterLayer \
					$(LOCAL_PATH)/../../Classes/Scene/AnnounceLayer \
					$(LOCAL_PATH)/../../Classes/Scene/ClockLayer \
					$(LOCAL_PATH)/../../Classes/Scene/TargetLayer

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
