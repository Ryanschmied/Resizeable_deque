//
//  test.cpp
//  Project_2
//
//  Created by Indraj Kang on 2018-01-28.
//  Copyright © 2018 Indraj Kang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Resizable_deque.h"

int amain() {
    
    Resizable_deque<int> cue_1(16);
    
    std::cout << "list should be empty (1)" << cue_1.empty() <<std::endl;
    std::cout << "capacity should (16)" << cue_1.capacity() << std::endl;
    
    cue_1.push_back(1);
    cue_1.push_front(2);
    cue_1.push_front(3);
    cue_1.push_front(4);
    cue_1.push_front(5);
    cue_1.push_front(6);
    cue_1.push_front(7);
    cue_1.push_front(8);
    cue_1.push_front(9);
    cue_1.push_front(10);
    cue_1.push_front(11);
    cue_1.push_front(12);
    cue_1.push_front(13);
    cue_1.push_front(14);
    cue_1.push_front(15);
    cue_1.push_front(16);
    std::cout << "value at front is (16):" << cue_1.front() << std::endl;
    std:: cout << "value at back is  1: " << cue_1.back() << std::endl;
    
    cue_1.push_front(17);
    
    std::cout << "value at front is (17):" << cue_1.front() << std::endl;
    std:: cout << "value at back is  1: " << cue_1.back() << std::endl;
    
    return 0;
    
}



