#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

// Structure to store a question, its options, and the correct answer
struct Question {
  string questionText;
  vector<string> options;
  int correctAnswerIndex; // (0 - 3) represents the correct answer index
};

// Function to print a divider for better UI
void printDivider() {
  cout << "----------------------------------------\n";
}

// Function to print a question with its options
void printQuestion(const Question& q) {
  cout << q.questionText << "\n";
  for (int i = 0; i < q.options.size(); ++i) {
    cout << i + 1 << ". " << q.options[i] << "\n";
  }
  printDivider();
}

// Function to ask the audience for help (randomized)
void askTheAudience(int correctIndex) {
  srand(time(0));
  vector<int> audienceVotes(4, 0);
  audienceVotes[correctIndex] = 60 + rand() % 21; // 60% to 80% for the correct answer

  int remainingVotes = 100 - audienceVotes[correctIndex];
  for (int i = 0; i < 4; ++i) {
    if (i != correctIndex) {
      audienceVotes[i] = rand() % (remainingVotes / 2 + 1);
      remainingVotes -= audienceVotes[i];
    }
  }

  cout << "The audience voted as follows:\n";
  for (int i = 0; i < 4; ++i) {
    cout << char('A' + i) << ": " << audienceVotes[i] << "%\n";
  }
  printDivider();
}

// Function to remove two incorrect answers (50:50)
void fiftyFifty(vector<string>& options, int correctIndex) {
  srand(time(0));
  int removedCount = 0;
  while (removedCount < 2) {
    int randomIndex = rand() % 4;
    if (randomIndex != correctIndex && !options[randomIndex].empty()) {
      options[randomIndex] = ""; // Remove the answer
      ++removedCount;
    }
  }

  cout << "Two options have been removed. Remaining options:\n";
  for (int i = 0; i < options.size(); ++i) {
    if (!options[i].empty()) {
      cout << char('A' + i) << ". " << options[i] << "\n";
    }
  }
  printDivider();
}

// Function to load questions from a file
vector<Question> loadQuestionsFromFile(const string& filename) {
  vector<Question> questions;
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "Error: Could not open file \"" << filename << "\". Using default questions.\n";
    return questions;
  }

  string line;
  while (getline(file, line)) {
    stringstream ss(line);
    Question q;
    getline(ss, q.questionText, ';');
    for (int i = 0; i < 4; ++i) {
      string option;
      getline(ss, option, ';');
      q.options.push_back(option);
    }
    string correctAnswerIndexStr;
    getline(ss, correctAnswerIndexStr, ';');
    q.correctAnswerIndex = stoi(correctAnswerIndexStr) - 1;
    questions.push_back(q);
  }
  file.close();
  return questions;
}

// Main game function
void playGame(vector<Question>& questions) {
  int currentPrize = 0;
  vector<int> prizeLevels = { 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 500000, 1000000 };
  int lifelines = 2; // Audience help (1) and 50:50 (2)

  for (int i = 0; i < questions.size(); ++i) {
    printQuestion(questions[i]);

    cout << "Current prize: $" << currentPrize << "\n";
    cout << "Next prize: $" << prizeLevels[i] << "\n";
    if (lifelines > 0) {
      cout << "You have " << lifelines << " lifelines remaining: (1) Ask the Audience, (2) 50:50.\n";
    }
    cout << "What is your answer? (Enter 1-4 or 0 to use a lifeline): ";
    int choice;
    cin >> choice;

    if (choice == 0 && lifelines > 0) {
      cout << "Choose your lifeline: (1) Ask the Audience, (2) 50:50: ";
      int lifelineChoice;
      cin >> lifelineChoice;

      if (lifelineChoice == 1) {
        askTheAudience(questions[i].correctAnswerIndex);
        --lifelines;
      }
      else if (lifelineChoice == 2) {
        fiftyFifty(questions[i].options, questions[i].correctAnswerIndex);
        --lifelines;
      }
      else {
        cout << "Invalid lifeline choice.\n";
      }
      --i; // Reattempt the same question
      continue;
    }

    if (choice - 1 == questions[i].correctAnswerIndex) {
      cout << "\nCorrect answer! You won $" << prizeLevels[i] << "!\n\n";
      currentPrize = prizeLevels[i];
      printDivider();
    }
    else {
      cout << "\nWrong answer! Game over. You won $" << currentPrize << ".\n";
      break;
    }

    if (i == questions.size() - 1) {
      cout << "Congratulations! You won $ " << currentPrize <<"!\n";
      printDivider();
    }
  }
}

int main() {
  string filename = "questions.txt";

  // Load questions from file
  vector<Question> questions = loadQuestionsFromFile(filename);

  // Default questions if file loading fails
  if (questions.empty()) {
    questions = {
      {"What is the capital of Egypt?", {"Cairo", "Alexandria", "Aswan", "Luxor"}, 0},
      {"What is the largest planet in our solar system?", {"Jupiter", "Earth", "Mars", "Venus"}, 0},
      {"How many continents are there on Earth?", {"7", "6", "5", "8"}, 0},
      {"Which organ pumps blood in the human body?", {"Heart", "Lungs", "Brain", "Liver"}, 0},
      {"What is the boiling point of water?", {"100°C", "90°C", "120°C", "80°C"}, 0},
      {"What is the name of the planet we live on?", {"Earth", "Mars", "Venus", "Jupiter"}, 0},
      {"What is the color of the sky on a clear day?", {"Blue", "Red", "Green", "White"}, 0},
      {"What is the opposite of 'Hot'?", {"Cold", "Warm", "Cool", "Chilly"}, 0},
      {"How many legs does a spider have?", {"8", "6", "4", "10"}, 0},
      {"What is 5 + 5?", {"10", "15", "20", "25"}, 0},
      {"Which month has 28 or 29 days?", {"February", "January", "April", "December"}, 0},
      {"What do bees produce?", {"Honey", "Milk", "Wax", "Oil"}, 0}
    };
  }


  cout << "===> Welcome to Who Wants to Be a Millionaire >.< ! <===\n";
  printDivider();
  playGame(questions);

  system("pause");
  return 0;
}

// Terminal command to run...
// alias start='g++ -g main.cpp -o main.exe && start main.exe'
// g++ -g main.cpp -o main.exe && start main.exe