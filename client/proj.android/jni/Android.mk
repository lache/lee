LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := lee/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/LobbyLayer.cpp \
				   ../../Classes/BattleLayer.cpp \
				   ../../Classes/PopText.cpp \
				   ../../Classes/LaneListItem.cpp \
				   ../../Classes/BuyVehicleWindow.cpp \
				   ../../Classes/ResourceBar.cpp \
				   ../../Classes/Rand.cpp \
				   ../../Classes/Actor.cpp \
				   ../../Classes/Player.cpp \
				   ../../Classes/SimplePopup.cpp \
				   ../../Classes/FontSize.cpp \
				   ../../Classes/CheatWindow.cpp \
				   ../../Classes/RecruitContext.cpp \
				   ../../Classes/RecruitButton.cpp \
				   ../../Classes/CharAnimCacheManager.cpp \
				   ../../Classes/BattleResultWindow.cpp \
				   ../../Classes/BattleContext.cpp \
				   ../../Classes/SelectStageButton.cpp \
				   ../../Classes/SelectStageWindow.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
