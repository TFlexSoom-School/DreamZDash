/* 
 * Tristan Hilbert
 * 1/15/2020
 * DreamZDash Loader Utility
 * 
 */

#include "Loader.hpp"
#include <fstream>
#include <algorithm>

namespace dzdash{


Loader::Loader(int max_buffer_size):
    buffer_size(0),
    max_buffer_size(max_buffer_size)
{
    this->buffer = new char[this->max_buffer_size];
    this->buffer_size = 0;
}

Loader::Loader(const char * filename, int max_buffer_size): 
    buffer(new char[max_buffer_size]), 
    buffer_size(0),
    max_buffer_size(max_buffer_size)
{
    this->file.open(filename);
}

Loader::~Loader(){
    delete [] this->buffer;
    file.close();
}

const char* Loader::load(){
    int count = this->file.gcount();
    count = std::min(count, this->max_buffer_size);
    this->file.read(this->buffer, count);
    this->buffer_size = count;
    return this->buffer;
}

const char* Loader::get_buffer(){
    return this->buffer;
}

int Loader::get_buffer_size(){
    return this->buffer_size;
}

int Loader::get_count(){
    return this->file.gcount();
}

};
