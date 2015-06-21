//
//  main.m
//  arument_test
//
//  Created by Andy Wallace on 6/14/15.
//  Copyright (c) 2015 Andy Wallace. All rights reserved.
//

#include "tools.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

string reverse(string orig);
char * reverse(const char * orig, int length);

void readFile(string filePath);


int main(int argc, const char * argv[]) {
    
    //cout<<"hello "<<argc<<endl;
    
    
    if (argc >= 2){
        
        readFile(string(argv[1]));
        
    }
    
    return 0;
}

void readFile(string filePath){
    streampos size;
    char * memblock;
    
    
    ifstream file (filePath, ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();
        
        //reverse it
        char * reverseMem = reverse(memblock, size);
        
        //get the path
        cout<<endl<<getFileNameFromFullPath(filePath)<<endl<<getDirectoryFromFullPath(filePath)<<endl;
        string newFilePath = getDirectoryFromFullPath(filePath) + reverse(getFileNameFromFullPath(filePath));
        
        //save that shit
        ofstream myfile (newFilePath);
        if (myfile.is_open())
        {
            for (int i=0; i<size; i++){
                myfile << reverseMem[i];
                //cout<< (int)reverseMem[i] <<",";
            }
            myfile.close();
        }
        
        delete[] reverseMem;
        delete[] memblock;
    }
    else cout << "Unable to open file";
}


string reverse(string orig){
    string returnVal = "";
    
    for (int i=orig.size()-1; i>=0; i--){
        returnVal += orig[i];
    }
    
    return returnVal;
}

char * reverse(const char * orig, int length){
    
    if (length == 0){
        string orig_as_string = string(orig);
        length = orig_as_string.length();
    }
    
    
    char * returnVal = new char[length];
    
    
    for (int i=length-1; i>=0; i--){
        returnVal[length-i-1] = orig[i];
    }
    return returnVal;
    
}



