#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

// Function to display the ASCII text logo
void displayLogo() {
    std::cout << "    __    _  _    __    ____   ___  _   _  _  _    ____  _____  _  _  _  _ " << std::endl;
    std::cout << "   /__\\  ( \\( )  /__\\  (  _ \\ / __)( )_( )( \\/ )  ( ___)(  _  )( \\/ )( \\/ )" << std::endl;
    std::cout << "  /(__)\\  )  (  /(__)\\  )   /( (__  ) _ (  \\  /    )__)  )(_)(  )  (  \\  / " << std::endl;
    std::cout << " (__)(__)(_)\\_)(__)(__)(_)\\_) \\___)(_) (_) (__)   (__)  (_____)(_/\\_) (__)  " << std::endl;
    std::cout << "   ___  _   _  ____  __    __   " << std::endl;
    std::cout << " / __)( )_( )( ___)(  )  (  )  " << std::endl;
    std::cout << " \\__ \\ ) _ (  )__)  )(__  )(__ " << std::endl;
    std::cout << " (___/(_) (_)(____)(____)(____)" << std::endl;
}

// Function to parse the input command and arguments
void parseCommand(const std::string& input, std::string& command, std::vector<std::string>& arguments) {
    std::istringstream iss(input);
    iss >> command;
    
    arguments.clear(); // Clear the previous arguments

    std::string arg;
    while (iss >> arg) {
        arguments.push_back(arg);
    }
}

// Function to execute a command with arguments
void executeCommand(const std::string& command, const std::vector<std::string>& arguments) {
    if (command == "exit") {
        std::cout << "Anarchy Foxy Says Goodbye!" << std::endl;
        exit(0);
    }

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork error" << std::endl;
    } else if (pid == 0) {
        // Child process executes the command
        std::vector<char*> argv;
        argv.push_back(const_cast<char*>(command.c_str()));
        for (const std::string& arg : arguments) {
            argv.push_back(const_cast<char*>(arg.c_str()));
        }
        argv.push_back(nullptr);

        execvp(command.c_str(), argv.data());
        std::cerr << "Command execution error" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        // Parent process waits for the child to complete
        waitpid(pid, nullptr, 0);
    }
}

int main() {
    std::string input;
    std::string command;
    std::vector<std::string> arguments;

    displayLogo();

    while (true) {
        std::cout << std::endl;
        std::cout << "Anarchy Foxy Shell :> ";
        std::getline(std::cin, input);

        parseCommand(input, command, arguments);
        executeCommand(command, arguments);
    }

    return 0;
}
