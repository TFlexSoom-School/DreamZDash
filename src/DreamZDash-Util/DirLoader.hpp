#pragma once
/*
 * Tristan Hilbert
 * 1/20/2020
 * DreamZDash Directory Loader
 * 
 * I decided that making seperate loaders for Files
 * and directories may decrease memory consumption.
 * For cases where we can pack binary files it may be easier to 
 * use a "File Loader"
 * 
 */

#ifndef DREAMZDASH_DIR_LOADER_HPP
#define DREAMZDASH_DIR_LOADER_HPP

#include "FileLoader.hpp"
#include <vector>

namespace dzdash{

class DirLoader{
    private:
        /* Dir Fields */
        const char * path;
        std::vector<std::string> files;
        int selected;
        
        /* Singular Loader */
        FileLoader loader;
        
        /* 
         * Note we can still cache outside of the loader
         * class if we want extra memory management.
         * 
         * -- Use a profiler!
         */
    
    public:
        DirLoader(const char *, int max_buffer_size = buffer_size_default);
        virtual ~DirLoader();
        
        /* File Loading Utilities */
        /* Used on "selected file" */
        virtual const char* load();
        virtual const char* get_buffer();
        virtual int get_buffer_size();
        virtual int get_current_file_count();
        /*  
         * ^^^
         * Instead of returning a reference, let's keep these
         * abstracted in case we decide to not use the File Loader
         * class
         */

        /* File Selecting Utilities */
        /* Used for selecting and maintaining directory */
        virtual std::vector<std::string>& get_file_names();
        virtual void select_file(std::string);
        virtual void select_file(int);
        virtual std::string get_selected_file();


};

};

#endif