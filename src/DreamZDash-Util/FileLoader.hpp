#pragma once

/* 
 * Tristan Hilbert
 * 1/15/2020
 * DreamZDash Loader Utility
 * 
 */

#ifndef DREAMZDASH_FILE_LOADER_HPP
#define DREAMZDASH_FILE_LOADER_HPP

#include <fstream>

namespace dzdash{

const int buffer_size_default = 2048;

class FileLoader{
    private:
        std::ifstream file;
        char * buffer;
        int buffer_size;
        const int max_buffer_size;
    
    public:
        FileLoader(int max_buffer_size = buffer_size_default);
        FileLoader(const char *, int max_buffer_size = buffer_size_default);
        virtual ~FileLoader();
        virtual const char* load();
        virtual const char* get_buffer();
        virtual int get_buffer_size();
        virtual int get_count();
        virtual void open(const char *);

};

};



#endif