/*
 * Jhonatan Ewunetie
 * This program is a game called Madlibs. A user chooses a story that
 * has placeholders in it that they can replace with whatever the placeholder
 * specifies (e.g. adjective, verb, celebrity, etc...). Then the program prints the
 * story with all the placeholders replaced with what the user inputs.
 *
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

// prototyping all the functions
string chooseTextFile();
string readLines(string textFile, int& counterPlaceholder);
void replacePlaceholder(string& line, int& counterPlaceholder);
string checkVowel(string word);
string getUserInput(string article, string placeholder);
void counter(int& counterPlaceholder,int& totalPlaceholder, int& counterStory);
void printText(string text, int counterPlaceholder);

int main() {

    // introduces the program and insturctions for the user
    cout << "Welcome to CS 106B Mad Libs!\n"
            "I will ask you to provide various words\n"
            "and phrases to fill in a story.\n"
            "At the end, I will display your story to you.\n" << endl;

    // declare and initialize the counters
    int counterPlaceholder = 0;
    int totalPlaceholder = 0;
    int counterStory = 0;
    bool repeatMadLib = true;

    // a while loop that contains all functions and asks the user if they want to continue with another story
    while(repeatMadLib){
        string textFile = chooseTextFile();
        string story = readLines(textFile, counterPlaceholder);
        printText(story, counterPlaceholder);
        counter(counterPlaceholder, totalPlaceholder, counterStory);
        repeatMadLib = getYesOrNo("Do another Mad Lib (Y/N)? ");
    }

    // prints out number of stories created, total placeholders replaced, and number of placeholders replaced per story;
    cout << "\nMad Lib stories you created: " << counterStory << endl;
    double perStory = double(totalPlaceholder) / double(counterStory);
    cout << "Total placeholders replaced: " << totalPlaceholder << " (" <<
            fixed << setprecision(1) << perStory << " per story)" << endl;

    return 0;
}

// gets the user's chosen text file
string chooseTextFile(){

    // gets user input for the text file
    string textFile = getLine("Mad Lib Text: ");
    ifstream input;
    input.open(textFile);

    // checks if the user input for the text file exists
    while(!fileExists(textFile)){
        cout << "Invalid text file. Please try again." << endl;
        textFile = getLine("Mad Lib Text: ");
    }

    input.close();
    cout << endl;
    return textFile;
}

// reads the text line by line
string readLines(string textFile, int& counterPlaceholder){

    // opens file
    ifstream input;
    input.open(textFile);
    string line;
    string storyText;

    // goes line by line, executing a function to replace all placeholders. Afterward adds each line into a string
    while(getline(input, line)){
        while((line.find(">",line.find("<")) != string::npos)){
            replacePlaceholder(line, counterPlaceholder);
        }
        storyText = storyText + line + "\n";
    }

    input.close();
    return storyText;
}

// replaces a placeholder with a user input
void replacePlaceholder(string& line, int& counterPlaceholder){
    int index1 = line.find("<");
    int index2 = line.find(">", index1);
    string placeholder = line.substr(index1 + 1, index2 - index1 - 1);
    string article = checkVowel(placeholder);
    string userMadlib = getLine("Please type " + article + " " + placeholder + ": ");
    line.replace(index1, index2 - index1 + 1, userMadlib);
    counterPlaceholder++;
}

// checks whether to use "a" or "an" based on whether the placeholder starts with a vowel or not
string checkVowel(string word){
    if (toLowerCase(word[0]) == 'a' || toLowerCase(word[0]) == 'e' || toLowerCase(word[0]) == 'i' ||
            toLowerCase(word[0]) == 'o' || toLowerCase(word[0]) == 'u'){
        return "an";
    } else {
        return "a";
    }
}

// counts the total placeholders replaced and the number of stories played
void counter(int& counterPlaceholder,int& totalPlaceholder, int& counterStory){
    totalPlaceholder += counterPlaceholder;
    counterPlaceholder = 0;
    counterStory++;
}

// prints the story and the number of placeholders replaced
void printText(string text, int counterPlaceholder){
    cout << "\nYour Mad Lib Story:\n" << text << endl;
    cout << "\n" << counterPlaceholder << " placeholder(s) replaced." << endl;
}
