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
        if (std::cin.peek() == EOF || std::cin.peek() == '\n' || std::cin.peek() == '\0') {
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

// void exercise2(std::vector<int> &sequence, std::vector<int> &sequence2) {
//     std::vector<int> values(sequence.size(), 1);
//     int max = 1;
//     for (int i = sequence.size() - 1; i >= 0; i--) {
//         for (size_t x = i; x < sequence.size(); x++) {
//             for (int j = sequence2.size() -1; j >= 0; j--) {
//                 if (sequence[i] < sequence[x] && sequence[i] == sequence2[j]) {
//                     if (values[i] - values[x] < 1) {
//                         values[i] = values[x] + 1;
//                         if (max < values[i]) {
//                             max = values[i];
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     // for (long unsigned int i = 0; i < values.size(); i++)
//     //     std::cout << values[i] << std::endl;
//     std::cout << max << std::endl;
//     return;
// }

void exercise2(std::vector<int> &sequence, std::vector<int> &sequence2) {
    std::vector<int> values(sequence.size(), 1);
    int size = sequence.size(), size2 = sequence2.size(), max = 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size2; j++) {
            for (int z = i; z < size; z++) {
                if (sequence2[j] == sequence[z]) {
                    std::cout << sequence2[j] << " "<< sequence[z] << " " << sequence[i] << "Equal Values" << std::endl;
                    if (sequence[i] < sequence2[j]) {
                        if (values[i] - values[z] < 1) {
                            values[i] = values[z] + 1;
                            std::cout << sequence2[j] << " "<< sequence[z] << " " << sequence[i] << "Increase Values" << std::endl;
                            if (max < values[i]) {
                                max = values[i];
                            }
                        }
                    }
                }
            }
        }
    }
    // for (long unsigned int i = 0; i < values.size(); i++)
    //     std::cout << values[i] << std::endl;
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