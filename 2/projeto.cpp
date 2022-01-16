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
    std::vector<int> connections;
} vertex;

*vertex new_vertex(int id) {
    vertex new_vertex;
    new_vertex.id = id;
    return *vertex;
}

void initialize_graph(std::vector<vertex> &graph, std::vector<int> &graphInfo) {
    int currentIndex;
    int currentId;
    for (int i = 0; i < graphInfo[0]; i++) {
        graph[i] = *new_vertex(i);
    }
    for (int i = 0; i < graphInfo[1]; i++) {
        vector<int> currentConnection(2, -1);
        while (std::cin >> currentId) {
            subjects[currentIndex] = currentId; 
            if (std::cin.peek() == '\n' || std::cin.peek() == '\0') {
                break;
            }
        }
        graph[currentConnection[0]].connections.push_back(currentConnection[1]);
    }
    return;
}

void receive_line(std::vector<int> &subjects) {
    int currentIndex;
    int currentId;
    while (std::cin >> currentId) {
        subjects[currentIndex] = currentId; 
        if (std::cin.peek() == '\n' || std::cin.peek() == '\0') {
            break;
        }
    }
}

int main() {
    vector<int> subjects(2, -1);
    vector<int> graphInfo(2, -1)
    receive_line(subjects);
    receive_line(graphInfo);
    vector<vertex> graph(graphInfo[0], -1);
    initialize_graph(graph, graphInfo);
    return 0;
}