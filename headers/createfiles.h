#include <cstdlib>
#include <string>

void createFolder(std::string name){
    std::string command = "mkdir ";
    std::system((command+name).c_str());
}

void createFolder(){
    
}