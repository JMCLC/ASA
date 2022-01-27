/*  
    Projeto 2
    Jose Maria Cardoso 99096
    Gustavo Diogo 99233
*/

#include <vector>
#include <iostream>
#include <string>

typedef struct {
    int id;
    bool visited;
    std::vector<int> parents;
} vertex;

bool foundLoop = false;
bool foundFirstVertex = false;
bool foundSecondVertex = false;

void loopCheck(std::vector<vertex> &graph, int currentValue, int *objective) {
    int numberOfParents = graph[currentValue].parents.size();
    for (int i = 0; i < numberOfParents; i++) {
        if (graph[graph[currentValue].parents[i]].id == *objective) {
            foundLoop = true;
            return;
        } else {
            loopCheck(graph, graph[currentValue].parents[i], objective);
        }
    }
}

int initialize_graph(std::vector<vertex> &graph, std::vector<int> &graphInfo) {
    for (int i = 0; i < graphInfo[0]; i++) {
        vertex newVertex = {i + 1, false};
        graph[i] = newVertex;
    }
    std::vector<int> currentConnection(2, -1);
    int currentParentsSize;
    int numberOfInput;
    for (int i = 0; i < graphInfo[1]; i++) {
        currentConnection[0] = -1;
        currentConnection[1] = -1;
        numberOfInput = scanf("%d %d", &currentConnection[0], &currentConnection[1]);
        if (numberOfInput < 2) {
            std::cout << 0 << std::endl;
            return 0;
        }
        if (currentConnection[0] == -1 || currentConnection[1] == -1 || graph[currentConnection[1] - 1].parents.size() == 2 || currentConnection[0] > graphInfo[0] || currentConnection[1] > graphInfo[0]) {
            std::cout << 0 << std::endl;
            return 0;
        }
        currentParentsSize = graph[currentConnection[0] - 1].parents.size();
        for (int i = 0; i < currentParentsSize; i++) {
            if (graph[currentConnection[0] - 1].parents[i] == currentConnection[1] - 1) {
                std::cout << 0 << std::endl;
                return 0;
            }
        }
        graph[currentConnection[1] - 1].parents.push_back(currentConnection[0] - 1);
        //graph[currentConnection[1] - 1].loopCheck = true;
        // loopCheck(graph, currentConnection[0] - 1, &currentConnection[1]);
        // if (foundLoop == true) {
        //     std::cout << 0 << std::endl;
        //     return 0;
        // }
        // for (int i = 0; i < graphInfo[0]; i++) {
        //     graph[i].loopCheck = false;
        // }
    }
    return 1;
}

void First_DFS(std::vector<vertex> &graph, int currentValue, int *secondVertex, std::vector<bool> &checker) {
    int numberOfParents = graph[currentValue].parents.size();
    for (int i = 0; i < numberOfParents; i++) {
        graph[graph[currentValue].parents[i]].visited = true;
        if (graph[graph[currentValue].parents[i]].id == *secondVertex) {
            foundSecondVertex = true;
            // return;
        }
        if (checker[graph[currentValue].parents[i]] == true) {
            foundLoop = true;
            return;
        }
        checker[graph[currentValue].parents[i]] = true;
        First_DFS(graph, graph[currentValue].parents[i], secondVertex, checker);
    }
}

void Second_DFS(std::vector<vertex> &graph, std::vector<int> &answers, int currentValue, int *firstVertex, std::vector<bool> &checker) {
    int numberOfParents = graph[currentValue].parents.size();
    for (int i = 0; i < numberOfParents; i++) {
        if (graph[graph[currentValue].parents[i]].id == *firstVertex) {
            foundFirstVertex = true;
            return;
        }
        if (checker[graph[currentValue].parents[i]] == true) {
            foundLoop = true;
            return;
        }
        if (graph[graph[currentValue].parents[i]].visited == true)
            answers[graph[currentValue].parents[i]] = 1;
        else {
            checker[graph[currentValue].parents[i]] = true;
            Second_DFS(graph, answers, graph[currentValue].parents[i], firstVertex, checker);
        }
    }
}

void Third_DFS(std::vector<vertex> &graph, std::vector<int> &answers, int currentValue, std::vector<bool> &checker) {
    int numberOfParents = graph[currentValue].parents.size();
    for (int j = 0; j < numberOfParents; j++) {
        // if (checker[graph[currentValue].parents[j]] == true) {
        //     foundLoop = true;
        //     return;
        // }
        if (graph[graph[currentValue].parents[j]].visited == true && answers[graph[currentValue].parents[j]] == 1)
            answers[graph[currentValue].parents[j]] = 0;
        checker[graph[currentValue].parents[j]] = true;
        Third_DFS(graph, answers, graph[currentValue].parents[j], checker);
    }
}

// int loopCheck_aux(std::vector<vertex> &graph, int currentValue) {
//     int numberOfParents = graph[currentValue].parents.size();
//     for (int i = 0; i < numberOfParents; i++) {
//         graph[graph[currentValue].parents[i]].loopCheck = true;
//         if (graph[graph[currentValue].parents[i]].) {
//             foundSecondVertex = true;
//             return;
//         }
//         First_DFS(graph, graph[currentValue].parents[i]);
//     }
// }

// int loopCheck(std::vector<vertex> &graph) {
//     for (vertex v: graph) {
//         if (v.loopCheck == false) {
//             // loopCheck_aux(graph, v.id - 1);
//             int numberOfParents = v.parents.size();
//             for (int i = 0; i < numberOfParents; i++) {
//                 graph[v.parents[i]].loopCheck = true;                
//             }
//         }
//     }
//     return 1;
// }

void exercise(std::vector<vertex> &graph, std::vector<int> &subjects, int *size) {
    std::vector<int> answers(*size, 0);
    std::vector<bool> loopCheck(*size, false);
    graph[subjects[0] - 1].visited = 1;
    First_DFS(graph, subjects[0] - 1, &subjects[1], loopCheck);
    loopCheck.assign(*size, false);
    if (foundLoop == true) {
        std::cout << 0 << " " << std::endl;
        return;
    } else if (foundSecondVertex == true) {
        std::cout << subjects[1] << " " << std::endl;
        return;
    }
    if (graph[subjects[1] - 1].visited == 1)
        answers[subjects[1] - 1] = 1;
    Second_DFS(graph, answers, subjects[1] - 1, &subjects[0], loopCheck);
    loopCheck.assign(*size, false);
    if (foundLoop == true) {
        std::cout << 0 << " " << std::endl;
        return;
    } else if (foundFirstVertex == true) {
        std::cout << subjects[0] << " " << std::endl;
        return;
    }
    for (int i = 0; i < *size; i++) {
        if (answers[i] == 1) {
            Third_DFS(graph, answers, i, loopCheck);
            loopCheck.assign(*size, false);
            if (foundLoop == true) {
                std::cout << 0 << " " << std::endl;
                return;
            }
        }
    }
    std::vector<int> finalAnswer;
    for (int i = 0; i < *size; i++) {
        if (answers[i] == 1)
            finalAnswer.push_back(graph[i].id);
    }
    int answersSize = finalAnswer.size();
    if (answersSize == 0)
        std::cout << "-" << std::endl;
    else {
        for (int i = 0; i < answersSize; i++)
            std::cout << finalAnswer[i] << " ";
        std::cout << std::endl;
    }
}

int main() {
    std::vector<int> subjects(2, -1);
    std::vector<int> graphInfo(2, -1);
    int numberOfSubjects = scanf("%d %d", &subjects[0], &subjects[1]);
    if (numberOfSubjects < 2) {
        std::cout << 0 << std::endl;
        return 0;
    }
    int numberOfGraphInfo = scanf("%d %d", &graphInfo[0], &graphInfo[1]);
    if (numberOfGraphInfo < 2) {
        std::cout << 0 << std::endl;
        return 0;
    }
    std::vector<vertex> graph(graphInfo[0], {-1});
    int initialized = initialize_graph(graph, graphInfo);
    if (initialized == 1) {
        // int loopExistence = loopCheck();
        // if (loopExistence == 1)
        exercise(graph, subjects, &graphInfo[0]);
    }
    return 0;
}