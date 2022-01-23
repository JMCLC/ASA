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

int initialize_graph(std::vector<vertex> &graph, std::vector<int> &graphInfo) {
    int currentIndex = 0;
    int currentId;
    for (int i = 0; i < graphInfo[0]; i++) {
        vertex newVertex = {i + 1, false};
        graph[i] = newVertex;
    }
    std::vector<int> currentConnection(2, -1);
    for (int i = 0; i < graphInfo[1]; i++) {
        currentConnection[0] = -1;
        currentConnection[1] = -1;
        currentIndex = 0;
        while (std::cin >> currentId) {
            currentConnection[currentIndex++] = currentId; 
            if (std::cin.peek() == '\n' || std::cin.peek() == '\0') {
                break;
            }

        }
        if (currentConnection[0] == -1 || currentConnection[1] == -1 || graph[currentConnection[1] - 1].parents.size() == 2) {
            std::cout << 0 << std::endl;
            return 0;
        }
        graph[currentConnection[1] - 1].parents.push_back(currentConnection[0] - 1);
    }
    return 1;
}

void receive_line(std::vector<int> &subjects) {
    int currentIndex = 0;
    int currentId;
    while (std::cin >> currentId) {
        subjects[currentIndex++] = currentId; 
        if (std::cin.peek() == '\n' || std::cin.peek() == '\0') {
            break;
        }
    }
}

void First_DFS(std::vector<vertex> &graph, int currentValue) {
    int numberOfParents = graph[currentValue].parents.size();
    for (int i = 0; i < numberOfParents; i++) {
        graph[graph[currentValue].parents[i]].visited = true;
        First_DFS(graph, graph[currentValue].parents[i]);
    }
}

void Second_DFS(std::vector<vertex> &graph, std::vector<int> &answers, int currentValue) {
    int numberOfParents = graph[currentValue].parents.size();
    for (int i = 0; i < numberOfParents; i++) {
        if (graph[graph[currentValue].parents[i]].visited == true)
            answers[graph[currentValue].parents[i]] = 1;
        else
            Second_DFS(graph, answers, graph[currentValue].parents[i]);
    }
}

void Third_DFS(std::vector<vertex> &graph, std::vector<int> &answers, int currentValue) {
    int numberOfParents = graph[currentValue].parents.size();
    for (int j = 0; j < numberOfParents; j++) {
        if (graph[graph[currentValue].parents[j]].visited == true && answers[graph[currentValue].parents[j]] == 1)
            answers[graph[currentValue].parents[j]] = 0;
        Third_DFS(graph, answers, graph[currentValue].parents[j]);
    }
}

void exercise(std::vector<vertex> &graph, std::vector<int> &subjects, int *size) {
    std::vector<int> answers(*size, 0);
    graph[subjects[0] - 1].visited = 1;
    First_DFS(graph, subjects[0] - 1);
    if (graph[subjects[1] - 1].visited == 1)
        answers[subjects[1] - 1] = 1;
    Second_DFS(graph, answers, subjects[1] - 1);
    for (int i = 0; i < *size; i++) {
        if (answers[i] == 1)
            Third_DFS(graph, answers, i);
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
    receive_line(subjects);
    receive_line(graphInfo);
    std::vector<vertex> graph(graphInfo[0], {-1});
    int initialized = initialize_graph(graph, graphInfo);
    if (initialized == 1)
        exercise(graph, subjects, &graphInfo[0]);
    return 0;
}