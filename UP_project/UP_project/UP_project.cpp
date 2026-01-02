#include <iostream>
double money;
double energy;
double sanity;
double knowledge;
unsigned int examNumber = 0;
unsigned int examsPassed = 0;
unsigned int currentDay;
const unsigned int firstExamDay = 8;
const unsigned int secondExamDay = 17;
const unsigned int thirdExamDay = 26;
const unsigned int fifthExamDay = 45;
const unsigned int forthExamDay = thirdExamDay + 1 + rand() % (fifthExamDay - thirdExamDay - 1);
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
void EndGame();
void exitGame();
int main()
{
    StartGame();
    while (currentDay <= 45) {
        NewDay();
		if (currentDay == 45) {
            EndGame();
        }
    }
    return 0;
}
void StartGame() { //not finished
    std::cout << " [1] Start a new game" << std::endl;
    std::cout << " [2] Load game from a file" << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        SetDifficulty();
        break;
    case 2:
        //loadGame();
        break;
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        StartGame();
    }
}
void SetDifficulty() {
    std::cout << "Select difficulty level:" << std::endl;
    std::cout << "[1] Easy" << std::endl;
    std::cout << "[2] Medium" << std::endl;
    std::cout << "[3] Hard" << std::endl;
    currentDay = 0;
    int choice;
    std::cin >> choice;
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
void LoadGame() {
    //to be implemented
}
void NewDay() {
    currentDay++;
    std::cout << " Day " << currentDay << " out of 45" << std::endl;
    std::cout << " Money: " << money << std::endl;
    std::cout << " Energy: " << energy << std::endl;
    std::cout << " Sanity: " << sanity << std::endl;
    std::cout << " Knowledge: " << knowledge << std::endl;
    std::cout << " Exams passed: " << examsPassed << " out of 5" << std::endl;
    Event();
    DailyActivities();
}
void Event() {
    int chance = 1 + rand() % 30;
    if (chance == 1) {
        int eventNumber = 1 + rand() % 4;
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
            Event();
            break;
        }
    }
}
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
        std::cin >> choice;
        while (choice != 10) {
            std::cout << "Today is an exam day! You must take the exam." << std::endl;
            std::cin >> choice;
        }
        TakeExam();
    }
    else {
        ProcessCommand();
    }
}
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
        exitGame();
        break;
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        ProcessCommand();
        break;
    }
}
bool IsExamDay() {
    if (currentDay != firstExamDay && currentDay != secondExamDay && currentDay != thirdExamDay && // split for better readability
        currentDay != forthExamDay && currentDay != fifthExamDay) {
        return false;
    }
    else {
        examNumber++;
        return true;
    }
}
void UpdateStat(double& stat, int amount) {
    stat += amount;
    Fainting();
    GameOverConditions();
    LimitStat(stat);
}
void GameOverConditions() {
    if (sanity < 0) {
        EndGame();
        exitGame();
    }
    if (money < 0) {
        EndGame();
        exitGame();
    }
}
void LimitStat(double& stat) {
    if (stat > 100) {
        stat = 100;
    }
    else if (stat < 0) {
        stat = 0;
    }
}
void Fainting() {
    if (energy <= 0) {
        std::cout << "You have fainted due to exhaustion. You lose a day." << std::endl;
        energy = 40;
        UpdateStat(sanity, -10);
        currentDay++;
    }
}
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
void GoToLectures() {
    int chanceOfSkipping = 1 + rand() % 10; // 1/10 chance of skipping
    if (chanceOfSkipping == 1) {
        std::cout << "You've decided to skip some of the lectures today." << std::endl;
        UpdateStat(knowledge, 10 * PartialSuccess());
        UpdateStat(energy, -10);
        UpdateStat(sanity, -5);
    }
    else {
        UpdateStat(knowledge, 15 * PartialSuccess());
        UpdateStat(energy, -15);
        UpdateStat(sanity, -10);
    }
}
void StudyAtHome() {
    int chanceOfDistraction = 1 + rand() % 5; // 2/5 chance of distraction
    if (chanceOfDistraction <= 2) {
        std::cout << "You got distracted while studying at home." << std::endl;
        UpdateStat(knowledge, 10 * PartialSuccess());
        UpdateStat(energy, -10);
        UpdateStat(sanity, -5);
    }
    else {
        UpdateStat(knowledge, 20 * PartialSuccess());
        UpdateStat(energy, -20);
        UpdateStat(sanity, -15);
    }
}
void StudyWithFriend() {
    int chanceOfFun = 1 + rand() % 5; // 3/5 chance of fun
    if (chanceOfFun <= 3) {
        std::cout << "You had too much fun while studying with your friend." << std::endl;
        UpdateStat(knowledge, 10 * PartialSuccess());
        UpdateStat(sanity, 15 * PartialSuccess());
        UpdateStat(energy, -10);
        return;
    }
    UpdateStat(knowledge, 5 * PartialSuccess());
    UpdateStat(sanity, 10 * PartialSuccess());
    UpdateStat(energy, -10);
}
void EatInCafeteria() {
    int chanceOfBadFood = 1 + rand() % 15; // 1/15 chance of bad food
    if (chanceOfBadFood == 1) {
        std::cout << "The food in the cafeteria was bad." << std::endl;
        UpdateStat(energy, 5 * PartialSuccess());
        UpdateStat(sanity, -5);
        UpdateStat(money, -5);
    }
    else {
        UpdateStat(sanity, 5 * PartialSuccess());
        UpdateStat(energy, 15 * PartialSuccess());
        UpdateStat(money, -5);
    }
}
void EatDuner() {
    int chanceOfBadDuner = 1 + rand() % 12; // 1/12 chance of bad duner
    if (chanceOfBadDuner == 1) {
        std::cout << "The duner you ate had gone bad." << std::endl;
        UpdateStat(energy, 10 * PartialSuccess());
        UpdateStat(sanity, -10);
        UpdateStat(money, -10);
    }
    else {
        UpdateStat(sanity, 15 * PartialSuccess());
        UpdateStat(energy, 20 * PartialSuccess());
        UpdateStat(money, -10);
    }
}
void GoToBar() {
    int chanceOfDrinkingTooMuch = 1 + rand() % 5; // 1/5 chance of getting drunk
    if (chanceOfDrinkingTooMuch == 1) {
        std::cout << "You drank too much the bar." << std::endl;
        UpdateStat(sanity, 10 * PartialSuccess());
        UpdateStat(money, -20);
        UpdateStat(energy, -25);
    }
    else {
        UpdateStat(sanity, 20 * PartialSuccess());
        UpdateStat(money, -20);
        UpdateStat(energy, -15);
    }
}
void GoToClub() {
    int chanceOfOverdancing = 1 + rand() % 4; // 1/4 chance of overdancing
    if (chanceOfOverdancing == 1) {
        std::cout << "You overdanced at the club." << std::endl;
        UpdateStat(sanity, 30 * PartialSuccess());
        UpdateStat(money, -25);
        UpdateStat(energy, -40);
    }
    else {
        UpdateStat(sanity, 40 * PartialSuccess());
        UpdateStat(money, -25);
        UpdateStat(energy, -30);
    }
}
void Rest() {
    int chanceOfDreams = 1 + rand() % 4; // 1/4 chance of good dreams
    if (chanceOfDreams == 1) {
        std::cout << "You dreamt of passing all your exams." << std::endl;
        UpdateStat(energy, 60);
        UpdateStat(sanity, 20);
    }
    else if (chanceOfDreams == 2) { // 1/4 chance of nightmares
        std::cout << "You had nightmares about failing your exams." << std::endl;
        UpdateStat(energy, 40);
        UpdateStat(sanity, -10);
    }
    else {
        UpdateStat(energy, 50);
        UpdateStat(sanity, 10);
    }
}
void Work() {
    int chanceOfHardDay = 1 + rand() % 6; // 1/6 chance of hard day
    if (chanceOfHardDay == 1) {
        std::cout << "You had a hard day at work." << std::endl;
        UpdateStat(money, 40 * PartialSuccess());
        UpdateStat(energy, -30);
        UpdateStat(sanity, -15);
    }
    else {
        UpdateStat(money, 40 * PartialSuccess());
        UpdateStat(energy, -20);
        UpdateStat(sanity, -10);
    }
}
void TakeExam() {
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
bool PassExam() {
    double luck = rand() % 101;
    double penalty = (examNumber - 1) * 5;
    double success = knowledge * 0.75 + sanity * 0.1 + energy * 0.1 + luck * 0.2 - penalty;
    return success >= 75;
}
void EndGame() {
    if (examsPassed == 5) {
        std::cout << "Congratulations!" << std::endl;
        std::cout << "You have passed all your exams and" << std::endl;
        std::cout << "survived the exam season of your life!" << std::endl;
    }
    else {
        std::cout << "Game Over!" << std::endl;
        std::cout << "Your psyche couldn't handle it" << std::endl;
        std::cout << "and you dropped out of university." << std::endl;
    }
    exitGame();
}
void exitGame() {
    exit(0);
}