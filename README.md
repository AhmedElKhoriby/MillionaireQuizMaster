# MillionaireQuizMaster 🎲💡

## 🏆 Project Overview

MillionaireQuizMaster is an interactive console-based quiz game inspired by the popular TV show "Who Wants to Be a Millionaire". This project was developed as part of the Assembly Language course at the college, showcasing fundamental programming concepts in C++.

### 🌟 Note

**Academic Project**: This implementation was created as a college assignment for the Assembly Language course, demonstrating practical application of programming principles.

## ✨ Features

### 🎮 Gameplay Mechanics

- Progressive difficulty with increasing prize levels
- 12 unique quiz questions covering various topics
- Ability to win up to $1,000,000

### 🆘 Lifeline Options

1. **Ask the Audience**

   - Provides probabilistic audience voting
   - Gives hints by showing percentage distribution of answers
   - Simulates real game show audience help mechanism

2. **50:50 Lifeline**
   - Eliminates two incorrect answers
   - Helps player narrow down possible correct options

### 📂 Question Management

- Dynamic question loading from external text file
- Fallback to default questions if file loading fails
- Easily extensible question bank

## 🛠 Technical Specifications

- **Language**: C++
- **Compilation**: g++ compiler
- **Platform**: Windows (uses `system("pause")`)
- **File Dependencies**:
  - `main.cpp`: Main game logic
  - `questions.txt`: External question database

## 📋 Requirements

- C++ Compiler (g++)
- Windows Operating System (for `system("pause")`)

## 🚀 How to Run

### Using Terminal

```bash
g++ -g main.cpp -o main.exe
./main.exe
```

### Compilation Alias (as shown in code)

```bash
alias start='g++ -g main.cpp -o main.exe && start main.exe'
```

## 🎲 Game Flow

1. Game starts with welcome message
2. Questions are presented one by one
3. Player chooses answers (1-4)
4. Can use lifelines when stuck
5. Winning condition: Answer all 12 questions correctly
6. Losing condition: Answering a question incorrectly

## 📊 Prize Structure

- Incremental prize levels from $100 to $1,000,000
- Prizes increase with each correct answer

## 🔧 Customization

- Modify `questions.txt` to add/change questions
- Adjust prize levels in `prizeLevels` vector

## 🤝 Contribution

Feel free to fork, modify, and improve the project. Suggestions and pull requests are welcome!

## 📜 License

Open-source project. Use and modify as needed.

## 📞 Support

For any questions or issues, please open an issue in the repository.

---

**Developed with ❤️ as a College Assembly Language Course Project**
