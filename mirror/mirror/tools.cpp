//
//  tools.cpp
//  mirror
//
//  Created by Andy Wallace on 6/21/15.
//  Copyright (c) 2015 Andy Wallace. All rights reserved.
//

#include "tools.h"


string getFileNameFromFullPath(string fullPath){
    for (int i=fullPath.size()-1; i>=0; i--){
        if (fullPath[i] == '/'){
            return fullPath.substr(i+1);
        }
    }
    cout<<"probably a fuk up: getFileNameFromFullPath"<<endl;
    return "";
}

string getDirectoryFromFullPath(string fullPath){
    for (int i=fullPath.size()-1; i>=0; i--){
        if (fullPath[i] == '/'){
            return fullPath.substr(0,i+1);
        }
    }
    cout<<"probably a fuk up: getDirectoryFromFullPath"<<endl;
    return "";
}


bool pathLeadsToFile(){
    
}