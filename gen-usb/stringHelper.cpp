//
//  stringHelper.cpp
//  adalina-usb
//
//  Created by Luis Alejandro Vieira on 18/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#include "stringHelper.h"

std::vector<std::string> split(std::string work, char delim, int rep)
{
    std::vector<std::string> output;
    std::string buf = "";
    
    for (int i = 0; i != work.length(); ++i)
    {
        if (work[i] != delim)
            buf += work[i];
        else if (rep == 1) {
            output.push_back(buf);
            buf = "";
        } else if (buf.length() > 0) {
            output.push_back(buf);
            buf = "";
        }
    }
    
    if (!buf.empty())
        output.push_back(buf);
    
    return output;
}
