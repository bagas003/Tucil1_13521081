#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function to calculate arithmetic operations
double calc(double a, char op, double b){
	switch(op){
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
	}
}

// Function to solve all possible combination for 24 game
void solve(vector <string> sCard, string &result) {

    // Process the string vector to int vector of cards
    vector <int> iCard;
    for (int i = 0; i < 4; i++) {
        if (sCard[i] == "A") {
            iCard.push_back(1); 
            sCard[i] = "1";
        } 
        else if (sCard[i] == "J") {
            iCard.push_back(11); 
            sCard[i] = "11";
        }
        else if (sCard[i] == "Q") {
            iCard.push_back(12); 
            sCard[i] = "12";
        }
        else if (sCard[i] == "K") {
            iCard.push_back(13); 
            sCard[i] = "13";
        }
        else {
            iCard.push_back(stoi(sCard[i]));
        }
    }

    // get start time for brute force algorithm
    auto start = high_resolution_clock::now();

    // all possible position/permutation for the cards
    int pos[24][4] = {
        {0,1,2,3}, {0,1,3,2}, {0,2,1,3}, {0,2,3,1}, {0,3,1,2}, {0,3,2,1},
        {1,0,2,3}, {1,0,3,2}, {1,2,0,3}, {1,2,3,0}, {1,3,0,2}, {1,3,2,0},
        {2,0,1,3}, {2,0,3,1}, {2,1,0,3}, {2,1,3,0}, {2,3,0,1}, {2,3,1,0},
        {3,0,1,2}, {3,0,2,1}, {3,1,0,2}, {3,1,2,0}, {3,2,0,1}, {3,2,1,0}};
    
    string sym = "/*-+";
    string ops[64], expr;
    vector <string> vecRes;
    double val;
    
    // brute force all possible cards and symbol combinations
    for (int x = 0; x < 24; x++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {

                    // brute force all possible grouping for the equations
                    double temp;
                    temp = calc(calc(calc(iCard[pos[x][0]], sym[i], iCard[pos[x][1]]), 
                            sym[j], iCard[pos[x][2]]), sym[k], iCard[pos[x][3]]);
                    if (temp == 24) {
                        vecRes.push_back("((" + sCard[pos[x][0]] + " " + sym[i] + " " + sCard[pos[x][1]] + ") " + 
                                        sym[j] + " " + sCard[pos[x][2]] + ") " + sym[k] + " " + sCard[pos[x][3]]);                    
                    }

                    temp = calc(calc(iCard[pos[x][0]], sym[i], calc(iCard[pos[x][1]], 
                            sym[j], iCard[pos[x][2]])), sym[k], iCard[pos[x][3]]);
                    if (temp == 24) {
                        vecRes.push_back("(" + sCard[pos[x][0]] + " " + sym[i] + " (" + sCard[pos[x][1]] + " " + 
                                        sym[j] + " " + sCard[pos[x][2]] + ")) " + sym[k] + " " + sCard[pos[x][3]]);
                    }
                    
                    temp = calc(iCard[pos[x][0]], sym[i], calc(calc(iCard[pos[x][1]], 
                            sym[j], iCard[pos[x][2]]), sym[k], iCard[pos[x][3]]));
                    if (temp == 24) {
                        vecRes.push_back(sCard[pos[x][0]] + " " + sym[i] + " ((" + sCard[pos[x][1]] + " " + sym[j] + 
                                        " " + sCard[pos[x][2]] + ") " + sym[k] + " " + sCard[pos[x][3]] + ")");
                    }
                    
                    temp = calc(iCard[pos[x][0]], sym[i], calc(iCard[pos[x][1]], sym[j], 
                            calc(iCard[pos[x][2]], sym[k], iCard[pos[x][3]])));
                    if (temp == 24) {
                        vecRes.push_back(sCard[pos[x][0]] + " " + sym[i] + " (" + sCard[pos[x][1]] + " " + sym[j] + 
                                        " (" + sCard[pos[x][2]] + " " + sym[k] + " " + sCard[pos[x][3]] + "))");
                    }
                    
                    temp = calc(calc(iCard[pos[x][0]], sym[i], iCard[pos[x][1]]), sym[j], 
                            calc(iCard[pos[x][2]], sym[k], iCard[pos[x][3]]));
                    if (temp == 24) {
                        vecRes.push_back("(" + sCard[pos[x][0]] + " " + sym[i] + " " + sCard[pos[x][1]] + ") " + 
                                        sym[j] + " (" + sCard[pos[x][2]] + " " + sym[k] + " " + sCard[pos[x][3]] + ")");
                    }
                }
            }
        }
    }

    // delete duplicated result
    unordered_set <string> undupe(vecRes.begin(), vecRes.end());
    vecRes.assign(undupe.begin(), undupe.end());

    // get stop time and execution time for the algorithm
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // result processing
    result += to_string(vecRes.size()) + " solution(s) found\n";
    for (auto i = vecRes.begin(); i != vecRes.end(); ++i) result += *i + "\n";
    result += "time taken: " + to_string(duration.count()) + " ms\n";
}

// Function to get cards from user input
void cardInput(vector <string> &card) {
    // get user input
    cout << "\nPlease enter 4 valid values [A,2,3,..,Q,K]\nseparated with space\n>> ";
    string strIn;
    getline(cin, strIn);
    const char* delim = " ";
    char *token = strtok(const_cast<char*>(strIn.c_str()), delim);
    while (token != nullptr) {
        card.push_back(string(token));
        token = strtok(nullptr, delim);
    }
    
    // input validation
    if (card.size() != 4) {
        cout << "Invalid Input!\n";
        card.clear();
        cardInput(card);
        return;
    }

    for (int i = 0; i < 4; i++) {
        try{
            int x = stoi(card[i]);
            if (x < 2 || x > 10) {
                cout << "Invalid Input!\n";
                card.clear();
                cardInput(card);
                return;
            }
        }
        catch(const exception& e) {
            if (!(card[i] == "A" || card[i] == "J" || card[i] == "Q" || card[i] == "K")) {
                cout << "Invalid Input!\n";
                card.clear();
                cardInput(card);
                return;
            }
        }
    }
}

// Function to generate random cards
void cardRandom(vector <string> &card) {
    srand(time(0));

    cout << "\nRandom Cards:\n>> ";
    for (int i = 0; i < 4; i++) {
        int temp = rand() % 13 + 1;
        // card.push_back(to_string(temp));
        switch (temp) {
            case 1: card.push_back("A"); break;
            case 11: card.push_back("J"); break;
            case 12: card.push_back("Q"); break;
            case 13: card.push_back("K"); break;
            default: card.push_back(to_string(temp)); break;
        }
        cout << card[i] << " ";
    }
    cout << endl;
}

// Function to get a valid choice input from user (1/2)
void validateChoice(int &c) {
    string strIn;
    vector <string> in;
    cout << ">> ";
    getline(cin, strIn);
    const char* delim = " ";
    char *token = strtok(const_cast<char*>(strIn.c_str()), delim);
    while (token != nullptr) {
        in.push_back(string(token));
        token = strtok(nullptr, delim);
    }
    
    if (!(in.size() == 1 && (in[0] == "1" || in[0] == "2"))) {
        cout << "\nInvalid Input! Please enter [1/2]" << endl;
        in.clear();
        validateChoice(c);
        return;
    }
    
    c = stoi(in[0]);
}

// Function to save string result to txt file
void saveResult(string result, vector <string> card) {
    string fname;
    cout << "\nEnter Filename: ";
    cin >> fname;

    result = card[0] + " " + card[1] + " " + card[2] + " " + card[3] + "\n" + result;
    
    ofstream fout;
    fout.open("../test/" + fname + ".txt");
    fout << result;
    fout.close();
    cout << "\nSaved succesfully!\n";
}

// main program
int main() {
    vector <string> card;
    string result = "\n";
    int pil;

    cout << "\n24 GAME\n";
    cout << "\n1. Input Cards   2. Random Cards\n";
    validateChoice(pil);
    
    if (pil == 1) cardInput(card);
    else cardRandom(card);

    solve(card, result);
    cout << result;

    cout << "\nSave solution(s)?\n";
    cout << "1. Yes   2. No\n";
    validateChoice(pil);

    if (pil == 1) saveResult(result, card);
    
	return 0;
}