/*
 * Tristan Hilbert
 * 1/10/2020
 * DreamZKernel
 *
 */

#include <iostream>
#include <string>
#include <cstring>

// POSIX
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

// Kill signal for x86 and ARM architectures
#define KILL 9

bool kernel(int);
void dash_child();
std::string share();
std::string get_command(std::string);
char ** parse_command_list(std::string);



// Stand-in till actual development begins.
int main(int argc, char* argv[]){
    std::cout << "Starting DreamZDash" << std::endl;
    int pid = 0;
    bool isDone = false;
    while(isDone == false){
        if(pid = fork()){
            isDone = !kernel(pid);
        }else{
            dash_child();
            return 0;
        }
        std::cout << "DONE? " << isDone << std::endl;
    }
}

bool kernel(int pid){
    int status = 0;
    int options = WNOHANG;
    int w = 0;
    std::string command_list;

    do{
        w = waitpid(pid, &status, options);
        if(w < 0){
            std::cerr << "Error on Lookup!" << std::endl;
            exit(errno);
        }else if(w == 0){
            command_list = share();
            if(command_list.size() > 0){
                kill(pid, KILL);
                break;
            }
        }else{
            std::cout << "Exitting!" << command_list.size() << std::endl;
            break;
        }
    }while(true);

    if(command_list.size() > 0){
        if(pid = fork()){
            do{
                w = waitpid(pid, &status, 0) < 0;
            }while(w >= 0 && !WIFEXITED(status));
        }else{
            std::string command = get_command(command_list);
            char ** argv = parse_command_list(command_list);

            std::cout << command << std::endl;
            std::cout << argv[0] << " " << argv[1] << " " << argv[2] << std::endl;

            execv(command.c_str(), argv);
            return false;
        }
        return true;
    }else{
        return false;
    }
}

void dash_child(){
    if(execl("ping", "-c 3 www.oregonstate.edu\0")){
        std::cerr << "Error occured trying to execute ./dash" << std::endl;
        exit(1);
    }
}

std::string share(){
    return std::string("ping -c 3 www.oregonstate.edu");
}

std::string get_command(std::string list){
    return list.substr(0, list.find_first_of(" "));
}

char ** parse_command_list(std::string list){
    int count = 0;

    // Count number of spaces
    for(int i = 0; i < list.size(); i ++){
        if(list[i] == ' '){
            count ++;
        }
    }

    // Turn into argv with null termination (count + 2)

    char ** argv = new char*[count + 2];
    argv[count + 1] = new char[1];
    argv[count + 1][0] = '\0';

    int temp = 0;
    for(int i = 0; i < count; i ++){
        temp = list.find_first_of(" ");
        argv[i] = new char[temp + 1];
        strncpy(argv[i], list.c_str(), count);
        argv[i][temp] = '\0';
        list.erase(0, temp - 1);
    }

    argv[count] = new char[list.size() + 1];
    strcpy(argv[count], list.c_str());
    argv[count][list.size() + 1] = '\0';

    // Return argvs
    return argv;
}
