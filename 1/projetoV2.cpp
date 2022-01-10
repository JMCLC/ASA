#include <vector>
#include <iostream>
#include <string>
#include <chrono>

void receive_sequence(std::vector<int> &sequence) {
    int currentNumber;
    while (std::cin >> currentNumber) {
        sequence.push_back(currentNumber);
        if (std::cin.peek() == '\n' || std::cin.peek() == '\0') {
            break;
        }
    }
}

void receive_second_sequence(std::vector<int> &sequence, std::vector<int> &newSequence) {
    int currentNumber;
    while (std::cin >> currentNumber) {
        bool found = false;
        for (long unsigned int i = 0; i < sequence.size(); i++) {
            if (currentNumber == sequence[i])
                found = true;
        }
        if (found)
            newSequence.push_back(currentNumber);
        if (std::cin.peek() == '\n' || std::cin.peek() == '\0') {
            break;
        }
    }
}


void exercise1(std::vector<int> &sequence) {
    std::vector<std::vector<int>> values(sequence.size(), std::vector<int>(2, 1));
    int res = 0, max = 1;
    for (int i = sequence.size() - 1; i >= 0; i--) {
        for (size_t j = i; j < sequence.size(); j++) {
            if (sequence[i] < sequence[j]) {
                if (values[i][0] - values[j][0] < 1) {
                    values[i][0] = values[j][0] + 1;
                    values[i][1] = values[j][1];
                    if (max < values[i][0]) {
                        res = 0;
                        max = values[i][0];
                    }
                } else if (values[i][0] - values[j][0] == 1)
                    values[i][1] += values[j][1];
            }
        }
        if (values[i][0] == max)
            res += values[i][1];
    }
    std::cout << max << " " << res << std::endl;
    return;
}

// bool areValueInOrderInSecondSequence(std::vector<int> &sequence, int a, int b) {
//     int indexA = -1, indexB = -1;
//     for (long unsigned int i = 0; i < sequence.size(); i++) {
//         if (sequence[i] == a)
//             indexA = i;
//         else if (sequence[i] == b)
//             indexB = i;
//     }
//     return indexA - indexB < 0;
// } 

// void onlyKeepCommonValues(std::vector<int> &sequence, std::vector<int> &sequence2) {
//     for (long unsigned int i = 0; i < sequence2.size(); i++) {
//         bool found = false;
//         for (long unsigned int j = 0; j < sequence.size(); j++) {
//             if (sequence2[i] == sequence[j])
//                 found = true;
//         }
//         if (!found)
//             sequence2.erase(sequence2.begin() + i);
//     }
// }

void exercise2(std::vector<int> &sequence, std::vector<int> &sequence2) {
    std::vector<int> values(sequence.size(), 1);
    int max = 1;
    //onlyKeepCommonValues(sequence, sequence2);
    for (int i = sequence.size() - 1; i >= 0; i--) {
        for (size_t j = i; j < sequence.size(); j++) {
            if (sequence[i] < sequence[j]) {
                int index = -1, index2 = -1;
                for (long unsigned int x = 0; x < sequence2.size(); x++) {
                    if (sequence2[x] == sequence[i])
                        index = x;
                    else if (sequence2[x] == sequence[j])
                        index2 = x;
                }
                if (index < index2) {
                    if (values[i] - values[j] < 1) {
                        values[i] = values[j] + 1;
                        if (max < values[i]) {
                            max = values[i];
                        }
                    }
                }
            }
        }
    }
    std::cout << max << std::endl;
    return;
}

int main() {
    int mode;
    std::string current_vector;
    std::vector<int> sequence;
    std::vector<int> sequence2;
    //auto start = std::chrono::steady_clock::now();
    std::cin >> mode;
    std::cin.ignore();
    receive_sequence(sequence);
    if (mode == 1) {
        exercise1(sequence);
    } else if (mode == 2) {
        //receive_sequence(sequence2);
        receive_second_sequence(sequence, sequence2);
        exercise2(sequence, sequence2);
    }
    //auto end = std::chrono::steady_clock::now();
    //std::cout << "Elapsed time in seconds: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " ns" << std::endl;
    return 0;
}