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
        //cout<<"not a directory"<<endl;
    }
    
    
    return fileNames;
    
}


string convertFileToIntList(string filePath, bool printFileSize){
    streampos size;
    char * memblock;
    
    string output="";
    
    ifstream file (filePath, ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        if (printFileSize){
            cout<<"size "<<size<<endl;
        }
        memblock = new char [size];
        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();
        
        for (int i=0; i<size; i++){
            int thisVal = (int)memblock[i];
            output += to_string(thisVal)+",";
        }
        
        delete[] memblock;
    }else{
        cout<<"bad file. not there"<<endl;
    }
    
    return output;
}



std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
char * convertIntListToBytes(string intList){
    
    vector<string> items = split(intList, ',');;
    
    char * bytes = new char [items.size()];
    
    for (int i=0; i<items.size(); i++){
        std::string::size_type sz;   // alias of size_t
        int numVal = std::stoi (items[i],&sz);
        bytes[i] = (char)numVal;
    }
    
    return bytes;
}

void makeFileFromIntList(string intList, int fileSize, string outputFile){
    char * bytes = convertIntListToBytes( intList );
    ofstream myfile (outputFile);
    if (myfile.is_open())
    {
        for (int i=0; i<fileSize; i++){
            myfile << bytes[i];
        }
        myfile.close();
    }
    delete[] bytes;
}

string getFileExtension(string file){
    
    for (int i=file.size(); i>=0; i--){
        if (file[i] == '.'){
            return file.substr(i+1);
        }
    }
    
    return "unkown";
    
}

void deleteSelf(){
    pid_t pid;
    char pathBuf[PROC_PIDPATHINFO_MAXSIZE];
    pid = getpid();
    proc_pidpath (pid, pathBuf, sizeof(pathBuf));
    
    string command = "rm " + string(pathBuf);
    system(command.c_str());
}

void showBadInputMessage(){
    cout<<"I don't know what you mean."<<endl<<"Try using -man to learn how to use this"<<endl<<endl;
}