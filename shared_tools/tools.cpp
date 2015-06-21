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
    //cout<<"probably a fuk up: getFileNameFromFullPath"<<endl;
    return fullPath;
}

string getDirectoryFromFullPath(string fullPath){
    for (int i=fullPath.size()-1; i>=0; i--){
        if (fullPath[i] == '/'){
            return fullPath.substr(0,i+1);
        }
    }
    //cout<<"probably a fuk up: getDirectoryFromFullPath"<<endl;
    return "./";
}


bool pathLeadsToFile(char * fullPath){
   return pathLeadsToFile(string(fullPath));
}

bool pathLeadsToFile(string fullPath){
    ifstream f(fullPath.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}


string getWorkingDir(){
    char workingDirBuf[PROC_PIDPATHINFO_MAXSIZE];
    getcwd(workingDirBuf, PROC_PIDPATHINFO_MAXSIZE);
    return workingDirBuf;
}
string getProcessDir(){
    pid_t pid;
    char pathBuf[PROC_PIDPATHINFO_MAXSIZE];
    pid = getpid();
    proc_pidpath (pid, pathBuf, sizeof(pathBuf));
    
    string returnVal = string(pathBuf);
    
    //cut off the process name
    for (int i=returnVal.size()-1; i>=0; i-- ){
        if (returnVal[i] == '/'){
            returnVal = returnVal.substr(0,i);
            break;
        }
    }
    
    return returnVal;

}

vector<string> listFilesInDir(string path){
    DIR *dp;
    struct dirent *ep;
    dp = opendir (path.c_str());
    
    vector<string> fileNames;
    
    if (dp != NULL)
    {
        while (ep = readdir (dp)){
            string thisFile = string(ep->d_name);
            if (thisFile != "." && thisFile != ".."){
                fileNames.push_back( thisFile ) ;
            }
        }
        (void) closedir (dp);
    }else{
        cout<<"not a directory"<<endl;
    }
    
    
    return fileNames;
    
}


void showBadInputMessage(){
    cout<<"I don't know what you mean."<<endl<<"Try using -man to leanr how to use this"<<endl<<endl;
}