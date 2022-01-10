/*  
    Projeto 1
    Jose Maria Cardoso 99096
    Gustavo Diogo 99233
*/

#include <vector>
#include <iostream>
#include <string>


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
    int currentNumber, sizeSequence = sequence.size();
    while (std::cin >> currentNumber) {
        bool found = false;
        for (int i = 0; i < sizeSequence; i++) {
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
    int res = 0, max = 1, sizeSequence = sequence.size();
    std::vector<std::vector<int>> values(sizeSequence, std::vector<int>(2, 1));
    for (int i = sizeSequence - 1; i >= 0; i--) {
        for (int j = i; j < sizeSequence; j++) {
            if (sequence[i] < sequence[j]) {
                if (values[i][0] - values[j][0] < 1) {
                    values[i] = {values[j][0] + 1, values[j][1]};
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

void exercise2_aux_aux(std::vector<int> &sequence, std::vector<int> &sequence2, int sizeSequence, int sizeSecondSequence, std::vector<int> &values, std::vector<int> &valuesSecondSequence, int *max) {
    if (sizeSecondSequence == 0)
        return;
    long unsigned int currentValue = sizeSequence - 1;
    long unsigned int currentValueSecondSequence = sizeSecondSequence - 1;
    if (sequence[currentValue] < sequence2[currentValueSecondSequence] && values[currentValue] < valuesSecondSequence[currentValueSecondSequence])
        values[currentValue] = valuesSecondSequence[currentValueSecondSequence];
    else if (sequence[currentValue] == sequence2[currentValueSecondSequence] && values[currentValue] > valuesSecondSequence[currentValueSecondSequence] - 1) {
        valuesSecondSequence[currentValueSecondSequence] = values[currentValue] + 1;
        if (*max < valuesSecondSequence[currentValueSecondSequence])
            *max = valuesSecondSequence[currentValueSecondSequence];
    }
    sizeSecondSequence = currentValueSecondSequence;
    return exercise2_aux_aux(sequence, sequence2, sizeSequence, sizeSecondSequence, values, valuesSecondSequence, max);
}


void exercise2_aux(std::vector<int> &sequence, std::vector<int> &sequence2, int sizeSequence, int sizeSecondSequence, std::vector<int> &values, std::vector<int> &valuesSecondSequence, int *max) {
    if (sizeSequence == 0)
        return;
    exercise2_aux_aux(sequence, sequence2, sizeSequence, sizeSecondSequence, values, valuesSecondSequence, max);
    sizeSequence = sizeSequence - 1;
    return exercise2_aux(sequence, sequence2, sizeSequence, sizeSecondSequence, values, valuesSecondSequence, max);
}

void exercise2(std::vector<int> &sequence, std::vector<int> &sequence2) {
    int max = 0, sizeSequence = sequence.size(), sizeSecondSequence = sequence2.size();
    std::vector<int> values(sizeSequence, 0);
    std::vector<int> valuesSecondSequence(sizeSecondSequence, 0);
    exercise2_aux(sequence, sequence2, sizeSequence, sizeSecondSequence, values, valuesSecondSequence, &max);
    std::cout << max << std::endl;
    return;
}

int main() {
    int mode;
    std::string current_vector;
    std::vector<int> sequence;
    std::vector<int> sequence2;
    std::cin >> mode;
    std::cin.ignore();
    receive_sequence(sequence);
    if (mode == 1) {
        exercise1(sequence);
    } else if (mode == 2) {
        receive_second_sequence(sequence, sequence2);
        exercise2(sequence, sequence2);
    }
    return 0;
}