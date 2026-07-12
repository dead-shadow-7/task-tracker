#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

json loadTasks(const std::string& path) {
    std::ifstream in(path);
    if (!in) {             
        return json::array();   
    }
    json tasks;
    in >> tasks;            
    return tasks;
}
void saveTasks(const std::string& path, const json& tasks) {
    std::ofstream out(path);
    out << tasks.dump(2);   
}


int main(int argc, char* argv[]){
    std::string path = "tasks.json";
    json tasks = loadTasks(path);

    if (argc < 2){
        std::cout << "Usage: " << argv[0] << " [command] [options]\n";
        std::cout << "Commands:\n  --greet [name]   Greets a user\n  --version        Shows version\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "--version") {
        std::cout << "Task Tracker App v1.0.0\n";
    } 
    else if (command == "add"){
        if (argc < 3) { std::cerr << "Error: add requires a task description.\n"; return 1; }
        std::string value = argv[2];
        int maxId = 0;
        for (auto& t : tasks) maxId = std::max(maxId, t["id"].get<int>());
        json task = {
            {"id", maxId + 1},
            {"desc", value},
            {"done", false}
        };
        tasks.push_back(task);
        std::cout << "Added Task: " << value<<std::endl;
    }
    else if (command == "remove"){
        if (argc < 3) { std::cerr << "Error: add requires a task ID.\n"; return 1; }
        int id = std::stoi(argv[2]); 
       for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if ((*it)["id"] == id) {
            tasks.erase(it);
            break;
        }
    }
    std::cout << "Removed Task: " << id << "\n";


    }
    else if (command == "update"){
    if (argc < 3) { std::cerr << "Error: add requires a task ID.\n"; return 1; }
    if (argc < 4) { std::cerr << "Error: add requires a task description.\n"; return 1; }
    int id = std::stoi(argv[2]);
    std::string newDesc = argv[3];   
    for (auto& t : tasks) {
        if (t["id"] == id) {
            t["desc"] = newDesc;
            break;
        }
    }
    std::cout << "Updated Task: " << id << "\n";
    }
    else if (command == "list"){
        for (auto& t : tasks) {
        std::cout << t["id"] << ": " << t["desc"].get<std::string>()
          << (t["done"] ? " [done]" : "") << "\n";

        }
    }
    else {
        std::cerr << "Unknown command: " << command << "\n";
        return 1;
    }
    saveTasks(path, tasks); 
    return 0;
}