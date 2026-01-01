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
void gameOverConditions() {
    if (sanity < 0) {
        std::cout << "You have lost your sanity. Game over!" << std::endl;
        //exitGame();
    }
    if (money < 0) {
        std::cout << "You are out of money. Game over!" << std::endl;
        //exitGame();
	}
}
void limitStat(double& stat) {
    if(stat > 100) {
        stat = 100;
	}
    else if (stat < 0) {
		stat = 0;
    }
}
void fainting() {
    if (energy <= 0) {
        std::cout << "You have fainted due to exhaustion. You lose a day." << std::endl;
        energy = 40;
		updateStat(sanity, -10);
		currentDay++;
	}
}
void updateStat(double& stat, int amount) {
    stat += amount;
    gameOverConditions();
    limitStat(stat);
}
double partialSuccess() {
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
void goToLectures() {
    updateStat(knowledge, 15 * partialSuccess());
	updateStat(energy, -15);
	updateStat(sanity, -10);
}
void studyAtHome() {
	updateStat(knowledge, 20 * partialSuccess());
	updateStat(energy, -20);
	updateStat(sanity, -15);
}
void studyWithFriend() {
	updateStat(knowledge, 5 * partialSuccess());
	updateStat(energy, -10);
	updateStat(sanity, 10 * partialSuccess());
}
void eatInCafeteria() {
    updateStat(energy, 15 * partialSuccess());
    updateStat(money, -5);
	updateStat(sanity, 5 * partialSuccess());
}
void eatDuner() {
	updateStat(energy, 20 * partialSuccess());
	updateStat(money, -10);
	updateStat(sanity, 15 * partialSuccess());
}
void goToBar() {
	updateStat(sanity, 20 * partialSuccess());
    updateStat(money, -20);
	updateStat(energy, -15);
}
void goToClub() {
    updateStat(sanity, 40 * partialSuccess());
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
bool isExamDay() {
	if (currentDay != firstExamDay && currentDay != secondExamDay && currentDay != thirdExamDay) { // split for better readability
        if (currentDay != forthExamDay && currentDay != fifthExamDay) {
            return  false;
        }
        else {
			examNumber++;
			return true;
        }
    }
    else {
        examNumber++;
		return true;
    }
}
bool passExam() {
	double luck = rand() % 101;
	double penalty = (examNumber - 1) * 5;
    double success = knowledge * 0.75 + sanity * 0.1 + energy * 0.1 + luck * 0.2 - penalty;
	return success >= 75;
}
void takeExam() {
    if (isExamDay()) {
        updateStat(energy, -20);
        if (passExam()) {
            examsPassed++;
            updateStat(sanity, 20);
            updateStat(energy, -20);
        }
        else {
            updateStat(sanity, -30);
            updateStat(energy, -20);
        }
    }
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
		std::cout << "Today is not an exam day!. Please choose a different activity for today." << std::endl;
		processCommand();
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
    if (isExamDay()) {
		int choice;
		std::cin >> choice;
        while (choice != 10) {
            std::cout << "Today is an exam day! You must take the exam." << std::endl;
        }
		takeExam();
    }
    else {
		processCommand();
    }
}
void event() {
	int chance = 1 + rand() % 30;
    if (chance == 1) {
        int eventNumber = 1 + rand() % 4;
        switch (eventNumber) {
        case 1:
            std::cout << "Mom and dad have sent you money." << std::endl;
            updateStat(money, 30);
            break;
        case 2:
            std::cout << "A friend buys you coffee." << std::endl;
            updateStat(sanity, 10);
            break;
        case 3:
            std::cout << "You got sick." << std::endl;
            updateStat(energy, -20);
            break;
        case 4:
            std::cout << "There is no electricity in your building." << std::endl;
            currentDay++;
            event();
            break;
        }
    }
}
void newDay() {
    currentDay++;
    event();
	dailyActivities();
}
int main()
{
    startGame();
    newDay();
    return 0;
}