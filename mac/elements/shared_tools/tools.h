//
//  tools.h
//  mirror
//
//  Created by Andy Wallace on 6/21/15.
//  Copyright (c) 2015 Andy Wallace. All rights reserved.
//

#ifndef __mirror__tools__
#define __mirror__tools__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <libproc.h>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <sstream>
using namespace std;


string getFileNameFromFullPath(string fullPath);
string getDirectoryFromFullPath(string fullPath);

bool pathLeadsToFile(char * fullPath);
bool pathLeadsToFile(string fullPath);

string getWorkingDir();
string getProcessDir();

vector<string> listFilesInDir(string path);

string getFileExtension(string file);

string convertFileToIntList(string filePath, bool printFileSize);
char * convertIntListToBytes(string intList);

void makeFileFromIntList(string intList, int fileSize, string outputFile);

void deleteSelf();


void showBadInputMessage();

#endif /* defined(__mirror__tools__) */
