//
//  main.m
//  convert_file_to_ints
//
//  Created by Andy Wallace on 6/21/15.
//  Copyright (c) 2015 Andy Wallace. All rights reserved.
//

#include "tools.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//code for these tow functions from: http://www.alecjacobson.com/weblog/?p=2376
string copy(const char * new_clipboard);
string exec(const char* cmd);


int main (int argc, char* argv[])
{
    
    if (argc < 3){
        cout<<"you need to give me a damn file, dude"<<endl;
        cout<<"-c to copy, -o to output to file"<<endl;
        cout<<"invert_file_to_ints -c/-i [file to convert] [output file if doing that]"<<endl;
        return 0;
    }
    
    string command = argv[1];
    string filePath = argv[2];
    
    if ( pathLeadsToFile(filePath) ){
        string intString = convertFileToIntList(filePath, true);
        
        
        if (command == "-c"){
            cout<<"copied to clipboard"<<endl;
            copy(intString.c_str());
        }
        
        else if (command == "-o"){
            string outputPath = filePath+".txt";
            if (argc >= 4){
                outputPath = argv[3];
            }
            
            cout<<"I'll try to save to "<<outputPath<<endl;
            
            ofstream myfile (outputPath);
            if (myfile.is_open())
            {
                for (int i=0; i<intString.size(); i++){
                    myfile << intString[i];
                }
                myfile.close();
            }
        }
        
        else{
            cout<<"give me a real command"<<endl;
        }
        
        
    }else{
        cout<<"dude your file sucks. It's not real."<<endl;
    }
    
    
    
    return 0;
}

string copy(const char * new_clipboard)
{
    std::stringstream cmd;
    cmd << "echo \"" << new_clipboard << "\" | pbcopy";
    return exec(cmd.str().c_str());
}

string exec(const char* cmd)
{
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe))
    {
        if(fgets(buffer, 128, pipe) != NULL)
        {
            result += buffer;
        }
    }
    pclose(pipe);
    return result;
}






