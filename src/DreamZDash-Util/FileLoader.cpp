/* 
 * Tristan Hilbert
 * 1/15/2020
 * DreamZDash FileLoader Utility
 * 
 */

#include "FileLoader.hpp"
#include <fstream>
#include <algorithm>

namespace dzdash{


FileLoader::FileLoader(int max_buffer_size):
    buffer_size(0),
    max_buffer_size(max_buffer_size)
{
    this->buffer = new char[this->max_buffer_size];
    this->buffer_size = 0;
}

FileLoader::FileLoader(const char * filename, int max_buffer_size): 
    buffer(new char[max_buffer_size]), 
    buffer_size(0),
    max_buffer_size(max_buffer_size)
{
    this->file.open(filename);
}

FileLoader::~FileLoader(){
    delete [] this->buffer;
    file.close();
}

const char* FileLoader::load(){
    int count = this->file.gcount();
    count = std::min(count, this->max_buffer_size);
    this->file.read(this->buffer, count);
    this->buffer_size = count;
    return this->buffer;
}

const char* FileLoader::get_buffer(){
    return this->buffer;
}

int FileLoader::get_buffer_size(){
    return this->buffer_size;
}

int FileLoader::get_count(){
    return this->file.gcount();
}

void FileLoader::open(const char * filename){
    this->file.open(filename);
}

};
