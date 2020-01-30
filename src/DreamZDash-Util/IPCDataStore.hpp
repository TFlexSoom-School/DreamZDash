#pragma once

/*
 * Tristan Hilbert
 * 1/29/2020
 * Data Store IPC Object
 * 
 * This object acts as the communication method between two processes. The processes
 * will be started from DreamZKernel. These objects then make up the composition of
 * each process in some form. The process will then store information via a JSON or
 * shared container.
 * 
 */

#ifndef DREAMZDASH_IPC_DATA_STORE_HPP
#define DREAMZDASH_IPC_DATA_STORE_HPP

namespace dzdash{

class IPC_DataStore{
    private:

    public:
};

};


#endif