/* 
 * Tristan Hilbert
 * 1/15/2020
 * DreamZDash DirLoader Utility
 * 
 * 
 * 
 */


#include "DirLoader.hpp"

#ifdef __linux__
/* directory reading through POSIX */
#include <dirent.h>
#endif

#include <stdexcept>
#include <cstring>
#include <iostream>

namespace dzdash{

#ifdef __linux__

DirLoader::DirLoader(const char * path, int max_buffer_size, bool recursive): 
    loader(max_buffer_size)
{
    // Variable initializations
    DIR * dir = 0;
    struct dirent * directory_contents = 0;
    std::string name;
    std::vector<std::string> directories;
    int count = 0;
    
    // Reserve for better performance
    directories.reserve(10);

    // Open Dir stream
    dir = opendir(path);
    if (dir == 0){
        throw std::invalid_argument("Path is invalid!");
    }

    if ((directory_contents = readdir(dir)) == 0){
        throw std::runtime_error("readdir returned 0");
    }

    // Read through base directory
    while(readdir_r(dir, directory_contents, &directory_contents) == 0 && directory_contents != 0){
        if(directory_contents -> d_type != DT_DIR){
            count ++;
        }else if(strcmp(directory_contents->d_name, "..\0") != 0 && strcmp(directory_contents->d_name, ".\0") != 0){
            directories.push_back(path);
            if (path[sizeof(path)] != '/'){
                directories.back() += "/";
            }
            directories.back() += directory_contents->d_name;
        }
    }

    // Reserve count in memory based on files
    this->files.reserve(count);

    // Read through base directory again
    rewinddir(dir);
    if ((directory_contents = readdir(dir)) == 0){
        throw std::runtime_error("readdir returned 0");
    }

    while(readdir_r(dir, directory_contents, &directory_contents) == 0 && directory_contents != 0){
        if(directory_contents -> d_type != DT_DIR){
            this->files.push_back(path);
            if (path[sizeof(path)] != '/'){
                this->files.back() += "/";
            }
            this->files.at(this->files.size() - 1) += directory_contents->d_name;
        }
    }

    // Close directory
    closedir(dir);

    if (recursive){
        // Read through each sub directory
        while(directories.size() > 0){
            name = directories.back();
            directories.pop_back();
            dir = opendir(name.c_str());
            
            if ((directory_contents = readdir(dir)) == 0){
                throw std::runtime_error("readdir returned 0");
            }

            // Read Directory for number of files
            while(readdir_r(dir, directory_contents, &directory_contents) == 0 && directory_contents != 0){
                if(directory_contents -> d_type != DT_DIR){
                    count ++;
                }else if(strcmp(directory_contents->d_name, "..\0") != 0 && strcmp(directory_contents->d_name, ".\0") != 0){
                    directories.push_back(name);
                    directories.back() += "/";
                    directories.back() += directory_contents->d_name;
                }
            }

            // Read directory for names
            this->files.reserve(count);
            rewinddir(dir);

            if ((directory_contents = readdir(dir)) == 0){
                throw std::runtime_error("readdir returned 0");
            }

            while(readdir_r(dir, directory_contents, &directory_contents) == 0 && directory_contents != 0){
                if(directory_contents -> d_type != DT_DIR){
                    this->files.push_back(name);
                    this->files.back() += "/";
                    this->files.back() += directory_contents->d_name;
                }
            }
        }
    }

    if (this->files.size() > 0){
        this->selected = 0;
        this->loader.open(this->files[selected].c_str());
    }else{
        this->selected = -1;
    }
}

#endif

DirLoader::~DirLoader(){
    this->files.clear();

}

/* File Loading Utilities */
/* Used on "selected file" */
const char* DirLoader::load(){
    if(this->selected == -1){
        return NULL;
    }

    return this->loader.load();
}

const char* DirLoader::get_buffer(){
    return this->loader.get_buffer();
}

int DirLoader::get_buffer_size(){
    return this->loader.get_buffer_size();
}

int DirLoader::get_current_file_count(){
    return this->files.size();
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
    return this->files;
}


// select_file int is faster
void DirLoader::select_file(std::string filename){
    for(int i = 0; i < this->files.size(); i ++){
        if (this->files[i] == filename){
            select_file(i);
        }
    }
}

void DirLoader::select_file(int select){
    if(select > 0 && select < this->files.size()){
        this->selected = select;
        this->loader.open(this->files[this->selected].c_str());
    }
}

std::string DirLoader::get_selected_file(){
    if(this->selected == -1){
        return "";
    }
    return this->files[this->selected];
}

#ifdef __linux__
#include <stdlib.h>
#include <cassert>
#include <string>

void test_DirLoader(){
    std::cout << "Calling System Commands to Create new files" << std::endl;
    if (system(NULL)){
        // Create Files
        system("mkdir new");
        system("touch new/example_example.txt");
        system("touch new/example_example1.txt");
        system("mkdir new/example_dir");
        system("touch new/example_dir/example.txt");
        system("touch new/example_dir/example1.txt");

        dzdash::DirLoader a("new");
        std::vector<std::string> names = a.get_file_names();
        assert(names[0] == std::string("new/example_example.txt"));
        assert(names[1] == std::string("new/example_example1.txt"));
        assert(names[2] == std::string("new/example_dir/example.txt") || 
                names[3] == std::string("new/example_dir/example.txt"));
        assert(names[2] == std::string("new/example_dir/example1.txt") || 
                names[3] == std::string("new/example_dir/example1.txt"));
        assert(names.size() == 4);

        dzdash::DirLoader b("new", 2048, false);
        names = b.get_file_names();
        assert(names.at(0) == std::string("new/example_example.txt"));
        assert(names.at(1) == std::string("new/example_example1.txt"));
        assert(names.size() == 2);

        // Cleanup
        system("rm -f new/example_example.txt");
        system("rm -f new/example_example1.txt");
        system("rm -f new/example_dir/example.txt");
        system("rm -f new/example_dir/example1.txt");
        system("rmdir -p new/example_dir");
    }
}

};

#endif