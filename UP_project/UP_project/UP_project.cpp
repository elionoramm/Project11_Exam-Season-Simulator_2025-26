#include <iostream>
#include <windows.h>
#include <fstream>
// Game state variables
double money;
double energy;
double sanity;
double knowledge;
unsigned int examNumber = 0;
unsigned int examsPassed = 0;
unsigned int currentDay = 0;
unsigned int examDays[5] = { 8, 17, 26, 0, 45 };

// Box drawing characters and line width
const char TOP_LEFT = 201;
const char TOP_RIGHT = 187;
const char BOTTOM_LEFT = 200;
const char BOTTOM_RIGHT = 188;
const char HORIZONTAL = 205;
const char VERTICAL = 186;
const int LINE_WIDTH = 40;

void StartGame();
void SetDifficulty();
void LoadGame();
void NewDay();
void Event();
void DailyActivities();
void ProcessCommand();
bool IsExamDay();
void UpdateStat(double& stat, int amount);
void GameOverConditions();
void LimitStat(double& stat);
void Fainting();
double PartialSuccess();
void GoToLectures();
void StudyAtHome();
void StudyWithFriend();
void EatInCafeteria();
void EatDuner();
void GoToBar();
void GoToClub();
void Rest();
void Work();
void TakeExam();
bool PassExam();
void SaveGame();
void EndGame();
void ExitGame();
int DigitsAfterDecimalPoint(double number);
int ToInt(double number);
int SymbolsInNumber(double number);
void NumberToString(double number, char* numberString);
void SetWidthLine(const int width, const char messageStart[], double number = -1, const char messageEnd[] = " ");
void HorizontalLine(int width);
void TopBorder(int width);
void BottomBorder(int width);
int main() {
    StartGame();
    while (currentDay < 45) {
        NewDay();
    }
    EndGame();
    return 0;
}

// in this function, the player can choose to start a new game or load a saved game
void StartGame() {
	TopBorder(LINE_WIDTH);
    SetWidthLine(LINE_WIDTH, "[1] Start a new game");
	SetWidthLine(LINE_WIDTH, "[2] Load game from a file");
	BottomBorder(LINE_WIDTH);
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        system("cls");
        examDays[3] = examDays[2] + 1 + rand() % (examDays[4] - examDays[2] - 1); // generate 4th exam day
        SetDifficulty();
        break;
    case 2:
        system("cls");
        LoadGame();
        break;
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        StartGame();
    }
}

// setting initial stats based on chosen difficulty
void SetDifficulty() {
    std::cout << "Select difficulty level:" << std::endl;
    std::cout << "[1] Easy" << std::endl;
    std::cout << "[2] Medium" << std::endl;
    std::cout << "[3] Hard" << std::endl;
    int choice;
    std::cin >> choice;
    system("cls");
    switch (choice) {
    case 1:
        money = 100;
        energy = 100;
        sanity = 100;
        knowledge = 70;
        break;
    case 2:
        money = 80;
        energy = 80;
        sanity = 80;
        knowledge = 50;
        break;
    case 3:
        money = 60;
        energy = 60;
        sanity = 40;
        knowledge = 35;
        break;
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        SetDifficulty();
    }
}

// loading game state from an existing file
void LoadGame() {
	std::fstream file;
	file.open("savegame.txt", std::fstream::in);
    if (file.is_open()) {
        file >> money;
        file >> energy;
        file >> sanity;
        file >> knowledge;
        file >> examNumber;
        file >> examsPassed;
        file >> currentDay;
        file >> examDays[3];
        file.close();
    }
    else {
        std::cout << "No save file found. Starting a new game." << std::endl;
        SetDifficulty();
	}
}

// progressing to a new day
void NewDay() {
    currentDay++;
    std::cout << TOP_LEFT;
	HorizontalLine(LINE_WIDTH);
	std::cout << TOP_RIGHT << std::endl;
    SetWidthLine(LINE_WIDTH, "Day", (double)currentDay, "out of 45");
    SetWidthLine(LINE_WIDTH, "Money:", money);
    SetWidthLine(LINE_WIDTH, "Energy:", energy);
    SetWidthLine(LINE_WIDTH, "Sanity:", sanity);
    SetWidthLine(LINE_WIDTH, "Knowledge:", knowledge);
    SetWidthLine(LINE_WIDTH, "Exams passed:", (double)examsPassed, "out of 5");
	std::cout << BOTTOM_LEFT;
	HorizontalLine(LINE_WIDTH);
	std::cout << BOTTOM_RIGHT << std::endl;
    Event();
    DailyActivities();
	SaveGame();
	system("cls");
}

// random events that can occur at the start of a new day
void Event() {
    if (!IsExamDay()) {
        int chance = 1 + rand() % 30;
		if (chance == 1) { // 1/30 chance of random event
			int eventNumber = 1 + rand() % 4; //1/4 chance for each different event
            std::cout << std::endl;
            std::cout << "Random event for the day:" << std::endl;
            switch (eventNumber) {
            case 1: 
                std::cout << "Mom and dad have sent you money." << std::endl;

                UpdateStat(money, 30);
                break;
            case 2:
                std::cout << "A friend buys you coffee." << std::endl;
                UpdateStat(sanity, 10);
                break;
            case 3:
                std::cout << "You got sick." << std::endl;
                UpdateStat(energy, -20);
                break;
            case 4:
                std::cout << "There is no electricity in your building." << std::endl;
                currentDay++;
                std::cout << "[0] To continue to the next day" << std::endl;
                int next;
                std::cin >> next;
                while (next != 0) {
                    std::cin >> next;
                }
				system("cls");
                std::cout << TOP_LEFT;
                HorizontalLine(LINE_WIDTH);
                std::cout << TOP_RIGHT << std::endl;
                SetWidthLine(LINE_WIDTH, "Day", (double)currentDay, "out of 45");
                SetWidthLine(LINE_WIDTH, "Money:", money);
                SetWidthLine(LINE_WIDTH, "Energy:", energy);
                SetWidthLine(LINE_WIDTH, "Sanity:", sanity);
                SetWidthLine(LINE_WIDTH, "Knowledge:", knowledge);
                SetWidthLine(LINE_WIDTH, "Exams passed:", (double)examsPassed, "out of 5");
                std::cout << BOTTOM_LEFT;
                HorizontalLine(LINE_WIDTH);
                std::cout << BOTTOM_RIGHT << std::endl;
                Event();
                break;
            }
            std::cout << std::endl;
        }
    }
}

// presenting daily activity options to the player
void DailyActivities() {
    std::cout << "What would you like to do today?" << std::endl;
    std::cout << "[1] Go to lectures" << std::endl;
    std::cout << "[2] Study at home" << std::endl;
    std::cout << "[3] Study with a friend" << std::endl;
    std::cout << "[4] Eat in the campus cafeteria" << std::endl;
    std::cout << "[5] Eat duner" << std::endl;
    std::cout << "[6] Go to a bar" << std::endl;
    std::cout << "[7] Go to a club" << std::endl;
    std::cout << "[8] Rest" << std::endl;
    std::cout << "[9] Work" << std::endl;
    std::cout << "[10] Take an exam" << std::endl;
    std::cout << "[11] Leave the game" << std::endl;
    if (IsExamDay()) {
        int choice;
        
        do {
            std::cout << "Today is an exam day! You must take the exam." << std::endl;
            std::cin >> choice;
        }
        while (choice != 10);
        TakeExam();
    }
    else {
        ProcessCommand();
    }
}

// processing the player's chosen activity
void ProcessCommand() {
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        GoToLectures();
        break;
    case 2:
        StudyAtHome();
        break;
    case 3:
        StudyWithFriend();
        break;
    case 4:
        EatInCafeteria();
        break;
    case 5:
        EatDuner();
        break;
    case 6:
        GoToBar();
        break;
    case 7:
        GoToClub();
        break;
    case 8:
        Rest();
        break;
    case 9:
        Work();
        break;
    case 10:
        std::cout << "Today is not an exam day!. Please choose a different activity for today." << std::endl;
        ProcessCommand();
        break;
    case 11:
        ExitGame();
        break;
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        ProcessCommand();
        break;
    }
}

// checking if the current day is an exam day
bool IsExamDay() {
    if (currentDay != examDays[0] && currentDay != examDays[1] && currentDay != examDays[2] && // split for better readability
        currentDay != examDays[3] && currentDay != examDays[4]) {
        return false;
    }
    else {
        return true;
    }
}

// updating player stats and checking for game over conditions
void UpdateStat(double& stat, int amount) {
    stat += amount;
    Fainting();
    GameOverConditions();
    LimitStat(stat);
}

// checking if any game over conditions are met
void GameOverConditions() {
    if (sanity <= 0) {
        EndGame();
        ExitGame();
    }
    if (money <= 0) {
        EndGame();
        ExitGame();
    }
}

// limiting stats to be within 0-100 range
void LimitStat(double& stat) {
    if (stat > 100) {
        stat = 100;
    }
    else if (stat < 0) {
        stat = 0;
    }
}

// handling fainting due to exhaustion
void Fainting() {
    if (energy < 0) {
        system("cls");
        std::cout << "You have fainted due to exhaustion. You lose a day." << std::endl;
        energy = 40;
        UpdateStat(sanity, -10);
		if (currentDay + 1 > examDays[4]) {
            EndGame();
            ExitGame();
        }
        currentDay++;
        if(IsExamDay()) {
			std::cout << "You have missed an exam due to fainting." << std::endl;
            examNumber++;
        }
        std::cout << "[0] To continue to the next day" << std::endl;
        int next;
        std::cin >> next;
        while (next != 0) {
            std::cin >> next;
        }
    }
}

// calculating partial success based on energy levels
double PartialSuccess() {
    if (energy >= 80) {
        return 1;
    }
    else if (energy >= 40) {
        return 0.75;
    }
    else {
        return 0.5;
    }
}

// activity implementations
void GoToLectures() {
    int chanceOfSkipping = rand() % 10; // 1/10 chance of skipping
    if (chanceOfSkipping == 0) {
        system("cls");
        std::cout << "You've decided to skip some of the lectures today." << std::endl;
        UpdateStat(knowledge, 10 * PartialSuccess());
        UpdateStat(energy, -10);
        UpdateStat(sanity, -5);
        std::cout << "[0] To continue to the next day" << std::endl;
        int next;
        std::cin >> next;
        while (next != 0) {
			std::cout << "Invalid choice. Please try again." << std::endl;
            std::cin >> next;
        }
    }
    else {
        UpdateStat(knowledge, 15 * PartialSuccess());
        UpdateStat(energy, -15);
        UpdateStat(sanity, -10);
    }
} 
void StudyAtHome() {
    int chanceOfDistraction = rand() % 5; // 2/5 chance of distraction
    if (chanceOfDistraction < 2) {
        system("cls");
        std::cout << "You got distracted while studying at home." << std::endl;
        UpdateStat(knowledge, 10 * PartialSuccess());
        UpdateStat(energy, -10);
        UpdateStat(sanity, -5);
        std::cout << "[0] To continue to the next day" << std::endl;
        int next;
        std::cin >> next;
        while (next != 0) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cin >> next;
        }
    }
    else {
        UpdateStat(knowledge, 20 * PartialSuccess());
        UpdateStat(energy, -20);
        UpdateStat(sanity, -15);
    }
}
void StudyWithFriend() {
    int chanceOfFun = rand() % 5; // 3/5 chance of fun
    if (chanceOfFun < 3) {
        system("cls");
        std::cout << "You had too much fun while studying with your friend." << std::endl;
        UpdateStat(knowledge, 5 * PartialSuccess());
        UpdateStat(sanity, 15 * PartialSuccess());
        UpdateStat(energy, -10);
        std::cout << "[0] To continue to the next day" << std::endl;
        int next;
        std::cin >> next;
        while (next != 0) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cin >> next;
        }
    }
    else {
        UpdateStat(knowledge, 10 * PartialSuccess());
        UpdateStat(sanity, 10 * PartialSuccess());
        UpdateStat(energy, -10);
    }
}
void EatInCafeteria() {
    int chanceOfBadFood = rand() % 15; // 1/15 chance of bad food
    if (chanceOfBadFood == 0) {
        system("cls");
        std::cout << "The food in the cafeteria was bad." << std::endl;
        UpdateStat(energy, 5 * PartialSuccess());
        UpdateStat(sanity, -5);
        UpdateStat(money, -5);
        std::cout << "[0] To continue to the next day" << std::endl;
        int next;
        std::cin >> next;
        while (next != 0) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cin >> next;
        }
    }
    else {
        UpdateStat(sanity, 5 * PartialSuccess());
        UpdateStat(energy, 15 * PartialSuccess());
        UpdateStat(money, -5);
    }
}
void EatDuner() {
    int chanceOfBadDuner = rand() % 12; // 1/12 chance of bad duner
    if (chanceOfBadDuner == 0) {
        system("cls");
        std::cout << "The duner you ate had gone bad." << std::endl;
        UpdateStat(energy, 10 * PartialSuccess());
        UpdateStat(sanity, -10);
        UpdateStat(money, -10);
        std::cout << "[0] To continue to the next day" << std::endl;
        int next;
        std::cin >> next;
        while (next != 0) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cin >> next;
        }
    }
    else {
        UpdateStat(sanity, 15 * PartialSuccess());
        UpdateStat(energy, 20 * PartialSuccess());
        UpdateStat(money, -10);
    }
}
void GoToBar() {
    int chanceOfDrinkingTooMuch = rand() % 5; // 1/5 chance of getting drunk
    if (chanceOfDrinkingTooMuch == 0) {
        system("cls");
        std::cout << "You drank too much the bar." << std::endl;
        UpdateStat(sanity, 10 * PartialSuccess());
        UpdateStat(money, -25);
        UpdateStat(energy, -25);
        std::cout << "[0] To continue to the next day" << std::endl;
        int next;
        std::cin >> next;
        while (next != 0) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cin >> next;
        }
    }
    else {
        UpdateStat(sanity, 20 * PartialSuccess());
        UpdateStat(money, -20);
        UpdateStat(energy, -15);
    }
}
void GoToClub() {
    int chanceOfOverdancing = rand() % 4; // 1/4 chance of overdancing
    if (chanceOfOverdancing == 0) {
        system("cls");
        std::cout << "You overdanced at the club." << std::endl;
        UpdateStat(sanity, 30 * PartialSuccess());
        UpdateStat(money, -30);
        UpdateStat(energy, -40);
        std::cout << "[0] To continue to the next day" << std::endl;
        int next;
        std::cin >> next;
        while (next != 0) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cin >> next;
        }
    }
    else {
        UpdateStat(sanity, 40 * PartialSuccess());
        UpdateStat(money, -30);
        UpdateStat(energy, -30);
    }
}
void Rest() {
    int chanceOfDreams = rand() % 4; // 1/4 chance of good dreams
    if (chanceOfDreams == 0) {
        system("cls");
        std::cout << "You dreamt of passing all your exams." << std::endl;
        UpdateStat(energy, 60);
        UpdateStat(sanity, 20);
        std::cout << "[0] To continue to the next day" << std::endl;
        int next;
        std::cin >> next;
        while (next != 0) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cin >> next;
        }
    }
    else if (chanceOfDreams == 1) { // 1/4 chance of nightmares
        system("cls");
        std::cout << "You had nightmares about failing your exams." << std::endl;
        UpdateStat(energy, 40);
        UpdateStat(sanity, -10);
        std::cout << "[0] To continue to the next day" << std::endl;
        int next;
        std::cin >> next;
        while (next != 0) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cin >> next;
        }
    }
    else {
        UpdateStat(energy, 50);
        UpdateStat(sanity, 10);
    }
}
void Work() {
    int chanceOfHardDay = rand() % 6; // 1/6 chance of hard day
    if (chanceOfHardDay == 0) {
		system("cls");
        std::cout << "You had a hard day at work." << std::endl;
        UpdateStat(money, 40 * PartialSuccess());
        UpdateStat(energy, -30);
        UpdateStat(sanity, -15);
        std::cout << "[0] To continue to the next day" << std::endl;
        int next;
        std::cin >> next;
        while (next != 0) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cin >> next;
        }
    }
    else {
        UpdateStat(money, 40 * PartialSuccess());
        UpdateStat(energy, -20);
        UpdateStat(sanity, -10);
    }
}

// handling exam taking and results
void TakeExam() {
    examNumber++;
    if (IsExamDay()) {
        UpdateStat(energy, -20);
        if (PassExam()) {
            examsPassed++;
            UpdateStat(sanity, 20);
            UpdateStat(energy, -20);
        }
        else {
            UpdateStat(sanity, -30);
            UpdateStat(energy, -20);
        }
    }
}

// determining if the player passes the exam
bool PassExam() {
    double luck = rand() % 101;
    double penalty = (examNumber - 1) * 5;
    double success = knowledge * 0.75 + sanity * 0.1 + energy * 0.15 + luck * 0.2 - penalty;
    return success >= 75;
}

// saving game state to a file
void SaveGame() {
    std::fstream file;
    file.open("savegame.txt", std::fstream::out);
    if (file.is_open()) {
        file << money << std::endl;
        file << energy << std::endl;
        file << sanity << std::endl;
        file << knowledge << std::endl;
        file << examNumber << std::endl;
        file << examsPassed << std::endl;
        file << currentDay << std::endl;
        file << examDays[3] << std::endl;
        file.close();
    }
}

// handling end game scenarios
void EndGame() {
    if (examsPassed == 5) {
		TopBorder(LINE_WIDTH);
		SetWidthLine(LINE_WIDTH, "Congratulations!");
		SetWidthLine(LINE_WIDTH, "You have passed all your exams and");
        SetWidthLine(LINE_WIDTH, "survived the exam season of your life!");
		BottomBorder(LINE_WIDTH);
    }
    else if (sanity <= 0){
		TopBorder(LINE_WIDTH);
		SetWidthLine(LINE_WIDTH, "Game Over!");
        SetWidthLine(LINE_WIDTH, "Your psyche couldn't handle it");
		SetWidthLine(LINE_WIDTH, "and you dropped out of university.");
		BottomBorder(LINE_WIDTH);
    }
    else if (money <= 0) {
        TopBorder(LINE_WIDTH);
        SetWidthLine(LINE_WIDTH, "Game Over!");
        SetWidthLine(LINE_WIDTH, "You ran out of money but you had");
        SetWidthLine(LINE_WIDTH, "enough savings for a train back home...");
        BottomBorder(LINE_WIDTH);
    }
    else {
        TopBorder(LINE_WIDTH);
        SetWidthLine(LINE_WIDTH, "Exam season is over!");
        SetWidthLine(LINE_WIDTH, "You managed to pass", (double)examsPassed, "out of 5 exams.");
        SetWidthLine(LINE_WIDTH, "Better luck next time!");
		BottomBorder(LINE_WIDTH);
    }
    ExitGame();
}

// exiting the game
void ExitGame() {
    exit(0);
}

// utility functions for formatting output
int DigitsAfterDecimalPoint(double number) {
    if (number - (int)number == 0) {
        return 0;
    }
    else if (number * 10 - (int)(number * 10) == 0) {
        return 1;
    }
    else {
        return 2;
    }
}
int ToInt (double number) {
    return number * pow(10, DigitsAfterDecimalPoint(number));
}
int SymbolsInNumber(double number) {
    if (number < 0) {
        return 0;
    }
    else if (number == 0) {
        return 1;
	}
    else {
		int numberAsInt = ToInt(number);
        int count = 0;
        while (numberAsInt > 0) {
            numberAsInt /= 10;
            count++;
        }
        if (DigitsAfterDecimalPoint(number)) {
			count++; // for decimal point
        }
        return count;
    }
}
void NumberToString(double number, char* numberString) {
	int numberAsInt = ToInt(number);
    int digitsAfterDecimalPoint = DigitsAfterDecimalPoint(number);
    int length = SymbolsInNumber(numberAsInt);
    if (length == 0) {
		numberString[0] = '\0';
    }
    else if (digitsAfterDecimalPoint == 0) {
        for (int i = 0; i < length; i++) {
            numberString[length - i - 1] = (numberAsInt % 10) + '0';
            numberAsInt /= 10;
        }
        numberString[length] = '\0';
    }
    else {
        for (int i = 0; i <= length; i++) {
            if (i == digitsAfterDecimalPoint) {
                numberString[length - i] = '.';
            }
            else {
                numberString[length - i] = (numberAsInt % 10) + '0';
                numberAsInt /= 10;
            }
        }
        numberString[length + 1] = '\0';
    }
}
// prints a line with a message and optional number, formatted to fit within the specified width
void SetWidthLine(const int width, const char messageStart[], double number, const char messageEnd[]) {
    int messageStartLength = strlen(messageStart);
    int messageEndLength = strlen(messageEnd);
	int numberLength = SymbolsInNumber(number); 
    char* numberToString = new char[numberLength + 1]; // +1 for the null terminator
	NumberToString(number, numberToString);
    int messageLength = messageStartLength + numberLength + messageEndLength;
    std::cout << VERTICAL;
    for (int i = 0; i < width; i++) {
        // print first half of a message 
        if (i < messageStartLength) {
            std::cout << messageStart[i];
        }
        // print number after adding space after the end of message start if there is a number
        else if (number != -1 && i >= messageStartLength + 1 && i <= messageStartLength + numberLength) {
            std::cout << numberToString[i - messageStartLength - 1];
        }
        // print the last half of the message after adding space behind the number if there is one
        else if (messageEnd != " " && i >= messageStartLength + numberLength + 2 && i < messageLength + 2) {
            std::cout << messageEnd[i - messageStartLength - numberLength - 2];
        }
        // fill the rest with spaces
        else {
            std::cout << " ";
        }
    }
    std::cout << VERTICAL << std::endl;
    delete[] numberToString;
    numberToString = nullptr;
}
void HorizontalLine(int width) {
    for (int i = 0; i < width; i++) {
        std::cout << HORIZONTAL;
    }
}
void TopBorder(int width) {
    std::cout << TOP_LEFT;
    HorizontalLine(width);
    std::cout << TOP_RIGHT << std::endl;
}
void BottomBorder(int width) {
    std::cout << BOTTOM_LEFT;
    HorizontalLine(width);
    std::cout << BOTTOM_RIGHT << std::endl;
}