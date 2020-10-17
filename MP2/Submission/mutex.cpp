//
//  mutex.cpp
//  muuu
//
//  Created by Joshua Jumper on 9/28/20.
//  Copyright © 2020 Joshua Jumper. All rights reserved.
//

#include "mutex.hpp"


void Mutex::Lock(){
    int rc = pthread_mutex_lock(&m);
    if(rc){
        pthread_exit(NULL);
    }
};
void Mutex::Unlock(){
    int rc = pthread_mutex_unlock(&m);
    if(rc){
        pthread_exit(NULL);
    };
};
