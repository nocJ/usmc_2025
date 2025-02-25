// Rank.h
#ifndef RANK_H
#define RANK_H

void initializeEEPROMsetup();

// Declare the variable (extern indicates it's defined elsewhere)
extern int displayRankLED;

// Declare the setter function
void setRankVariable(int value);

#endif