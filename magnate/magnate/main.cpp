//
//  main.m
//  magnate
//
//  Created by Andy Wallace on 6/21/15.
//  Copyright (c) 2015 Andy Wallace. All rights reserved.
//

#include "tools.h"



using namespace std;

void attemptMakemoney();
int getNumCoins();
void printTalk();
void printLook();
void printMan();


int main(int argc, const char * argv[]) {
    
    
    if (argc > 1){
        string arg = argv[1];
        
        if (arg == "-man"){
            printMan();
            return 0;
        }
        if (arg == "-make_money"){
            attemptMakemoney();
            return 0;
        }
        if (arg == "-talk"){
            printTalk();
            return 0;
        }
        if (arg == "-look"){
            printLook();
            return 0;
        }
    }
    
    
    showBadInputMessage();
    
    return 0;
}


void attemptMakemoney(){
    
    //if they have a coin near them, make a new coin
    int numCoins = getNumCoins();
    
    if (numCoins > 0){
        int idNum = numCoins;
        string newFileName = getProcessDir() + "/coin"+ to_string(idNum)+".money";
        
        //make sure this is not alreayd in use
        while ( pathLeadsToFile(newFileName) ){
            idNum++;
            newFileName = getProcessDir() + "/coin"+ to_string(idNum)+".money";
        }
        
        //once we have one write it!
        ofstream myfile ( newFileName );
        if (myfile.is_open())
        {
            //add some flavor
            for (int i=0; i<5; i++)  myfile << '$';
            myfile.close();
        }else{
            cout<<"something broke. Tell Andy."<<endl;
        }

    }
    
    //otherwise tell the player
    else{
        cout<<"The Magnate says:"<<endl<<"I need money to make money, and there is none here."<<endl;
    }
    
    
    
}


int getNumCoins(){
    //coins are any files fitting coin[#].money where [#] could not be present or is any integer.
    
    vector<string> fileNames = listFilesInDir( getProcessDir() );
    int total = 0;
    
    //check how much coin###.money there is there
    for (int i=0; i<fileNames.size(); i++){
        if (fileNames[i].size() >= 10){
            if (fileNames[i].substr(0,4) == "coin" && fileNames[i].substr(fileNames[i].size()-6,6) == ".money"){
                total ++;
            }
        }
    }
    return total;
}

void printTalk(){
    
    cout<<"The Magnate says:"<<endl;
    
    int numCoins = getNumCoins();
    
    if (numCoins == 0){
        cout<<"Where is all my money? This is a travesty! I am nothing when not surrounded by my wealth!"<<endl;
    }
    
    if (numCoins == 1){
        cout<<"Ah what a fine day to increase my fortune."<<endl;
    }
    
    if (numCoins == 2){
        cout<<"Already my profit has doubled!"<<endl;
    }
    
    if (numCoins >= 3 && numCoins < 10){
        cout<<"My wealth increases! Haha!"<<endl;
    }
    
    if (numCoins >= 10){
        cout<<"I AM RICH BEYOND MY WILDEST DREAMS!"<<endl;
    }
    
}

void printLook(){
    cout<<"The Magnate is a stodgy, but impeccably well dressed man sitting behind an ornate desk."<<endl;
}

void printMan(){
    cout<<endl;
    cout<<"The Magnate"<<endl<<endl;
    cout<<"A rich man who likes to get ricker"<<endl<<endl;
    cout<<"Usage:"<<endl;
    cout<<"magnate -make_money"<<endl<<"creates money"<<endl<<endl;
    cout<<"magnate -talk"<<endl<<"talk to the magnate"<<endl<<endl;
    cout<<"magnate -look"<<endl<<"look at the magnate"<<endl<<endl;
}