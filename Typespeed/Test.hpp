/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* Test.hpp
*/
#include "header.h"

#ifndef TEST_HPP
#define TEST_HPP


/* 
Test ID: Settings Difficulty and Direction Buttons test
Unit: Settings::nextButton for Difficulty and Direction
Description: test to determine if each button in Settings works correctly
Test steps:
1.     Create window object, as well as button and text arrays needed to initialize the Settings object
2.     Create a Settings object
3.     In a while window is open loop, display the Settings screen and check for button clicks
4.     Click the Difficulty button and print the current Difficulty before and after to the terminal
5.     Evaluate if the before Difficulty was Easy (0) and the after Difficulty was Normal (1)
6.     Click the Direction button 4 times, printing the before and after Direction each time
7.     Evalute if the prints follow the pattern of Right (0) to Left (1), Left (1) to Up (2), Up (2) to Down (3), Down (3) to Right (0)
8.     Now click the Difficulty button again, printing the current Difficulty before and after to the terminal
9.     Evaluate if the before Difficulty was Normal (1) and the after Difficulty was Hard (2), as well as if the Direction is now All (4)
10.    While Difficulty is on Hard, click the Direction button, printing the current Direction before and after to the terminal
11.    Evaluate if the before and after Direction was All (4)
Test data: Settings buttons and text arrays in main.cpp
Precondition: Settings explicit constructor works, Settings checkButtons works, createAsset works: Difficulty is on Easy, Direction is on Right
Postcondition: Difficulty is on Hard, Direction is on All
Expected result: Difficulty goes from Easy to Normal to Hard, Direction goes from Right to Left to Up to Down, and then to All while Difficulty is on Hard
Actual result: Difficulty goes from Easy to Normal to Hard, Direction goes from Right to Left to Up to Down, and then to All while Difficulty is on Hard
Status: passed
*/
void testSettingsDD(void);

/* 
Test ID: Settings Music and Sound Effects Buttons test
Unit: Settings::nextButton for Music and Sound Effects
Description: test to determine if each button in Music and Sound Effects works correctly
Test steps:
1.    Create window object, as well as button and text arrays needed to initialize the Settings object
2.    Create a Settings object and a Music object, starting the music
3.    In a while window is open loop, display the Settings screen and check for button clicks
4.    Click the Music button and evaluate if the button changes correctly and the music stops
5.    Click the Sound Effects button and print out the before and after to the terminal
6.    Evaluate if the before Sound Effects was on (1) and the after was off (0)
Test data: Settings buttons and text arrays in main.cpp
Precondition: Settings explicit constructor works, Settings checkButtons works, createAsset works: Music is on, Sound Effects are on
Postcondition: Music is off, Sound Effects are off
Expected result: Music is off with the correct button image, Sound Effects are off with the correct button image
Actual result: Music is off with the correct button image, Sound Effects are off with the correct button image
Status: passed
*/
void testSettingsMSE(void);

/* 
Test ID: Hash Table initialize test
Unit: Hash class, primarily insert()
Description: test to determine if the hash table properly was made
Test steps:
1.    Create a hash table using Files/Words.csv
2.    Print out the hash table using print_hash()
3.    Evaluate if there are 100 words in the terminal
Test data: HashTable class and Words.csv
Precondition: hash table has not been made
Postcondition: hash table has been made and 100 words have been printed to the terminal
Expected result: 100 words have been printed to the terminal
Actual result: 100 words have been printed to the terminal
Status: passed
*/
void testHashTable(void);


/* 
Test ID: Hash Table find word test
Unit: Hash class, primarily at()
Description: test to determine if a word can be found in the hash table and if a word not found be correctly reported as not found
Test steps:
1.    Create a hash table using Files/Words.csv
2.    Search for the word "INFORMATION": it should be found
3.    Conditionally evaluate if the word was found
4.    Search for the word "DOG": it should not be found
5.    Conditionally evaluate if the word was found
Test data: HashTable class and Words.csv
Precondition: Hash Table insert works: hash table has not been made
Postcondition: hash table has been made, "INFORMATION" was found but "DOG" was not
Expected result: "INFORMATION" was found, "DOG" was not
Actual result: "INFORMATOIN" was found, "DOG" was not
Status: passed
*/
void testFindWord(void);

/* 
Test ID: Life Tracker test
Unit: updateLifeTracker() in source.cpp
Description: test to determine if the images properly update in the lifeArray
Test steps:
1.    Create lifeArray and deadArray using Images/
2.    Call updateLifeTracker() and input lifeArray, deadArray, and 1
3.    Conditionally evaluate if lifeArray[0] is equal to deadArray[0]
4.    Call updateLifeTracker() again and input lifeArray, deadArray, and 2
5.    Conditionally evaluate if each index of lifeArray is equal to each index of deadArray
Test data: lifeArray and deadArray with Images/
Precondition: lifeArray is filled with lifeA and deadArray is filled with lifeD
Postcondition: lifeArray is filled with lifeD and deadArray is filled with lifeD
Expected result: lifeArray[0] is lifeD, then all of lifeArray is lifeD
Actual result: lifeArray[0] is lifeD, then all of lifeArray is lifeD
Status: passed
*/
void testLifeTracker(void);

#endif

/* 
Test ID: 
Unit: 
Description: 
Test steps:
1.    
2.    
3.    
Test data: 
Precondition: 
Postcondition: 
Expected result: 
Actual result: 
Status: 
*/