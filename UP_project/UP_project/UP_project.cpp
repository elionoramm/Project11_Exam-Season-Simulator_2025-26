#include <iostream>
int money;
int energy;
int sanity;
int knowledge;
unsigned int examsPassed = 0;
unsigned int currentDay;
const unsigned int fistExamDay = 8;
const unsigned int secondExamDay = 17;
const unsigned int thirdExamDay = 26;
const unsigned int forthExamDay = thirdExamDay + 1 + rand() % (fifthExamDay - thirdExamDay - 1);
const unsigned int fifthExamDay = 45;
void setDifficulty() {
	std::cout << "Select difficulty level:" << std::endl;
    std::cout << "[1] Easy" << std::endl;
    std::cout << "[2] Medium" << std::endl;
    std::cout << "[3] Hard" << std::endl;
	currentDay = 1;
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
		setDifficulty();
    }
}
void startGame() { //not finished
    std::cout << "[1] Start a new game!" << std::endl;
    std::cout << "[2] Load game from a file" << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        setDifficulty();
        break;
    case 2:
        //loadGame();
        break;
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        startGame();
    }
}
void endGameConditions() {
    if (sanity < 0) {
        std::cout << "You have lost your sanity. Game over!" << std::endl;
        //exitGame();
    }
    if (money < 0) {
        std::cout << "You are out of money. Game over!" << std::endl;
        //exitGame();
	}
}
void limitStat(int& stat) {
    if(stat > 100) {
        stat = 100;
	}
    else if (stat < 0) {
		stat = 0;
    }
}
void updateStat(int& stat, int amount) {
    stat += amount;
	endGameConditions();
    limitStat(stat);
}
void goToLectures() {
    updateStat(knowledge, 15);
	updateStat(energy, -15);
	updateStat(sanity, -10);
}
void studyAtHome() {
	updateStat(knowledge, 20);
	updateStat(energy, -20);
	updateStat(sanity, -15);
}
void studyWithFriend() {
	updateStat(knowledge, 5);
	updateStat(energy, -10);
	updateStat(sanity, 10);
}
void eatInCafeteria() {
    updateStat(energy, 15);
    updateStat(money, -5);
	updateStat(sanity, 5);
}
void eatDuner() {
	updateStat(energy, 20);
	updateStat(money, -10);
	updateStat(sanity, 15);
}
void goToBar() {
	updateStat(sanity, 20);
    updateStat(money, -20);
	updateStat(energy, -15);
}
void goToClub() {
    updateStat(sanity, 40);
	updateStat(money, -25);
	updateStat(energy, -30);
}
void rest() {
	updateStat(energy, 50);
	updateStat(sanity, 10);
}
void work() {
	updateStat(money, 40);
    updateStat(energy, -20);
	updateStat(sanity, -10);
}
void takeExam() {
	updateStat(energy, -20);
}
void processCommand() {
	int choice;
	std::cin >> choice;
    switch (choice) {
    case 1: 
        goToLectures();
        break;
    case 2:
        studyAtHome();
		break;
    case 3:
        studyWithFriend();
		break;
    case 4:
		eatInCafeteria();
		break;
    case 5:
		eatDuner();
		break;
    case 6:
		goToBar();
		break;
    case 7:
		goToClub();
		break;
    case 8:
		rest();
		break;
    case 9:
		work();
		break;
    case 10:
		takeExam();
		break;
    case 11:
        //exitGame();
		break;
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        processCommand();
		break;
    }
}
void dailyActivities() {
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
    processCommand();
}
int main()
{
    startGame();
	dailyActivities();
    return 0;
}