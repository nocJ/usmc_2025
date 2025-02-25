#ifndef LED_SCENE_MANAGER_H
#define LED_SCENE_MANAGER_H

#include <memory>
#include <mutex>
#include "freertos/FreeRTOS.h"
#include <unordered_map>
#include "freertos/semphr.h"
#include "Scene.h"

// List of LED animation scenes
enum class SceneType {
    NONE,
    RED_WHITE_BLUE,
    CELESTIAL_CLOUDS,
    GONE_TO_HELL,
    SECRET_COMBINATIONS,
    THE_SALAMANDER,
    TAPIR_JOYRIDE,
    SUPPRESSIVE_BADGE,
    CRAZY,
    THETAN_POSSESSION,
    DRUNK_AS_HELL,
    GONE_CLEAR,
    AMERICAN,
    USMC_2025
};

// List of LED Rank animation
enum class RankLevel {
    NONE = 1000,
    Private = 1,
    Private_First_Class = 2,
    Lance_Corporal = 3,
    Corporal = 4,
    Sergeant = 5,
    Staff_Sergeant = 6,
    Gunnery_Sergeant = 7,
    Master_Sergeant = 8,
    First_Sergeant = 9,
    Master_Gunnery_Sergeant = 10,
    Sergeant_Major = 11,
    Sergeant_Major_Of_The_Marine_Corps = 12,
    Warrant_Officer_1 = 13,
    Chief_Warrant_Officer_2 = 14,
    Chief_Warrant_Officer_3 = 15,
    Chief_Warrant_Officer_4 = 16,
    Chief_Warrant_Officer_5 = 17,
    Second_Lieutenant = 18,
    First_Lieutenant = 19,
    Captain = 20,
    Major = 21,
    Lieutenant_Colonel = 22,
    Colonel = 23,
    Brigadier_General = 24,
    Major_General = 25,
    Lieutenant_General = 26,
    General = 27
};

// Scene manager to track and switch between LED animation scenes
class SceneManager {
  public:
    static SceneManager &getInstance() {
        static SceneManager instance;
        return instance;
    }
    void init();
    void setScene(SceneType scene);
    void setRank(RankLevel rank);
    static void sceneTask(void *pvParameters);

  private:
    SceneManager() : currentScene(nullptr) {};
    SceneManager(const SceneManager &)            = delete;
    SceneManager &operator=(const SceneManager &) = delete;
    bool initialized                              = false;

    std::unordered_map<SceneType, std::unique_ptr<Scene>> scenes;
    Scene *currentScene;
    std::mutex sceneMutex;
};

#endif // LED_SCENE_MANAGER_H
