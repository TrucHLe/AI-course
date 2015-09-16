//
//  Search.cpp
//  Eight-Puzzle
//
//  Created by Truc Le on 9/15/15.
//  Copyright (c) 2015 Truc Le. All rights reserved.
//


#include <iostream>
#include <string>   //string
#include <iostream> //cin, cout
#include "Search.h"

using namespace std;



//===----------------------------------------------------------------------===//
// Print Introduction
//===----------------------------------------------------------------------===//
void introduce()
{
    cout << endl;
    cout << "---------- Cracking the Eight-Puzzle ----------" << endl;
    cout << "This program will solve the eight-puzzle problem using either an uninformed or an informed search algorithm. Please enter a file path of a text file that contains an eight-puzzle, along with a search algorithm's number that you'd like to use." << endl;
    
    cout << endl;
    cout << "Search Algorithms:" << endl;
    cout << "   1. Breadth-First Seach" << endl;
    cout << "   2. Depth-First Search" << endl;
    cout << "   3. Iterative Deepening Depth First Search" << endl;
    cout << "   4. Best-First Search" << endl;
    cout << "   5. A* Search" << endl;
    
    cout << endl;
}



//===----------------------------------------------------------------------===//
// Main
//===----------------------------------------------------------------------===//
int main(int argc, const char * argv[])
{
    
    //--------------------------------------------------
    // User Input
    //
    ifstream inputFile;
    string filePath;
    int algorithmNum;
    int DFSdepth;
    
    
    introduce();
    
    
    cout << "File Path: ";
    cin >> filePath;
    inputFile.open( filePath );
    
    while ( inputFile.fail() )
    {
        cout << "(!) Cannot find " << filePath << ", try again." << endl;
        cout << "File Path: ";
        cin >> filePath;
        inputFile.open( filePath );
    }
    
    
    
    cout << "Algorithm Number: ";
    cin >> algorithmNum;
    
    while ( algorithmNum < 1 || algorithmNum > 5 )
    {
        cout << "(!) Invalid algorithm number, try again." << endl;
        cout << "Algorithm Number: ";
        cin >> algorithmNum;
    }
    
    if ( algorithmNum == 2 )
    {
        cout << "Depth limit for Depth-First Search: ";
        cin >> DFSdepth;
    }
    //
    // !User Input
    //--------------------------------------------------




    
    

    
    
    
    
//    switch ( algorithmNum )
//    {
//        case 1:
//            <#statements#>
//            break;
//            
//        default:
//            break;
//    }
    
    return 0;
    
    
    
    /*
     // Construction: Make sure user enters a digit w/o delay glitch
     while ( !( cin >> algorithmNum ) )
     {
     cin.clear();
     cin.ignore( numeric_limits<streamsize>::max(), '\n' );
     cout << "(!) Invalid algorithm number, try again." << endl;
     cout << "Algorithm Number: ";
     }
     //! Construction
     */
}