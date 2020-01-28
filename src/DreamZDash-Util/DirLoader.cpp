/* 
 * Tristan Hilbert
 * 1/15/2020
 * DreamZDash DirLoader Utility
 * 
 */


#include "DirLoader.hpp"

//#ifdef __linux__
/* directory reading through POSIX */
#include <dirent.h>
//#endif

#include <stdexcept>
#include <cstring>

namespace dzdash{

//#ifdef __linux__

DirLoader::DirLoader(const char * path, int max_buffer_size): 
    loader(max_buffer_size)
{
    DIR * dir = opendir(path);
    if (dir == 0){
        throw std::invalid_argument("Path is invalid!");
    }

    if ((directory_contents = readdir()) == 0){
        throw std::runtime_error("readdir returned 0");
    }

    int count = 0;
    struct dirent * directory_contents = 0;
    while(readdir_r(dir, directory_contents, &directory_contents) == 0){
        if(directory_contents != 0){
            std::cout << directory_contents->d_name << std::endl;
            count ++;
        }
    }

    this->files.reserve(count);
    rewindir(dir);
    while(readdir_r(dir, directory_contents, &directory_contents) == 0){
        if(directory_contents != 0){
            this->files.push_back(std::string(strcat(path, directory_contents));
        }
    }

    if (this->files.size() > 0){
        this->selected = 0;
        this->loader.open(this->files[selected].c_str());
    }else{
        this->selected = -1;
    }
    closedir(dir);
}

//#endif

DirLoader::~DirLoader(){
    this->files.clear();

}

/* File Loading Utilities */
/* Used on "selected file" */
const char* DirLoader::load(){

}

const char* DirLoader::get_buffer(){

}

int DirLoader::get_buffer_size(){

}

int DirLoader::get_current_file_count(){

}

/*  
    * ^^^
    * Instead of returning a reference, let's keep these
    * abstracted in case we decide to not use the File Loader
    * class
    */

/* File Selecting Utilities */
/* Used for selecting and maintaining directory */
std::vector<std::string>& DirLoader::get_file_names(){

}

void DirLoader::select_file(std::string){

}

void DirLoader::select_file(int){

}

std::string DirLoader::get_selected_file(){

}


};