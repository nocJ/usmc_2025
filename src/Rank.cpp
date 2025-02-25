// Rank.cpp
#include "Rank.h"
#include "EEPROM.h"

#include "esp_log.h"
#include "esp_task_wdt.h"

static const char *TAG = "Rank";

#define RANK_EEPROM_ADDR 200
#define RANK_EEPROM_SIZE 512

int displayRankLED = 1000;

void storeRank(int rank) {
    EEPROM.begin(RANK_EEPROM_SIZE);
    // Ensure rank is between 0 and 1000 before storing it (optional check)
    if (rank < 0 || rank > 1000) {
        ESP_LOGE(TAG, "Invalid rank value: %d. Rank should be between 0 and 1000.", rank);
        return;
    }

    ESP_LOGD(TAG, "The rank value being stored is: %d", rank);
    
    // Store the rank as 2 bytes
    EEPROM.write(RANK_EEPROM_ADDR, (rank >> 8) & 0xFF);  // Most significant byte
    EEPROM.write(RANK_EEPROM_ADDR + 1, rank & 0xFF);     // Least significant byte
    EEPROM.commit();  // Commit the changes to EEPROM
    EEPROM.end();
}

int retrieveRank() {
    EEPROM.begin(RANK_EEPROM_SIZE);
    // Read the 2 bytes from EEPROM and combine them to form the integer
    int rank = 0;
    rank |= EEPROM.read(RANK_EEPROM_ADDR) << 8;   // Most significant byte
    rank |= EEPROM.read(RANK_EEPROM_ADDR + 1);     // Least significant byte
    EEPROM.end();
    return rank;
}

void setRankVariable(int value) {
    displayRankLED = value;
    // Store a rank in EEPROM
    storeRank(displayRankLED);
}

void initializeEEPROMsetup() {
    // Retrieve the rank from EEPROM
    int rank = retrieveRank();
    ESP_LOGD(TAG, "The rank value being retrieved is: %d", rank);
    displayRankLED = rank;

}