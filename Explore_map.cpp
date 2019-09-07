#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cctype>

using namespace std; // bad practice amirite

/*
========================================================
Struct      : Data
Data        : string for biome name(human), char for Biome(to print)
Description : is used mainly for the printing of the map, Print_Map uses Biome_L as what it actually prints 
========================================================
*/
struct Data{ // a struct to contain the boime name and a char to know at a glance the biome
    string Biome;
    char Biome_L;
};
/*
========================================================
Struct      : Player
Data        : an x and a y cord int
Description : is used to keep track of where the player is on the grid 
========================================================
*/
struct Player{
    int x;
    int y;
};

vector<Data> Biome_Maker();
vector<vector<Data> > Map_Gen(vector<Data>);
Player Starting_point_rand();
void Print_map(vector<vector<Data> >, Player);
Player Player_choice(Player);
void ClearScreen();
void Print_tips(Player);
void Normalize(string&);

int main() // main
{
    ClearScreen();
    srand(time(NULL));

    vector<Data> Biome_Types; // a vector to store the different types of biomes
    vector<vector<Data> > Map; // the biome map
    vector<int> temp;
    Player player;

    cout << "Initializing Biomes...\n";
    Biome_Types = Biome_Maker();
    cout << "Finished Initializing Biomes\n";

    cout << "Placing Player...\n";
    player = Starting_point_rand();
    cout << "Player location has been decided\n";

    cout << "Generating Map...\n";
    Map = Map_Gen(Biome_Types);
    cout << "Map Generation Complete\n";

    while(1){ // loop where "game" actually happens
        Print_map(Map, player);
        player = Player_choice(player);
        ClearScreen();
    }

    return 0;
}

/*
======================================================================================================================================
Function    : Biome_Maker
Parameters  : N/A
Return      : returns a vector of n length 
Description : pushes back a list of different possible biomes for the map generator to choose from 
======================================================================================================================================
*/
vector<Data> Biome_Maker(){
    Data temp;
    vector<Data> Biome_Types;

    // 0
    temp.Biome = "Mountain";
    temp.Biome_L = 'M';
    Biome_Types.push_back(temp);

    // 1
    temp.Biome = "Forest";
    temp.Biome_L = 'F';
    Biome_Types.push_back(temp);

    // 2
    temp.Biome = "Swamp";
    temp.Biome_L = 'S';
    Biome_Types.push_back(temp);

    // 3
    temp.Biome = "Grassland";
    temp.Biome_L = 'G';
    Biome_Types.push_back(temp);

    // 4
    temp.Biome = "Desert";
    temp.Biome_L = 'D';
    Biome_Types.push_back(temp);

    return Biome_Types;
}

/*
======================================================================================================================================
Function    : Map_Gen
Parameters  : a vector of a Data struct
Return      : a 2D vector of Data
Description : using the different biomes it generates a random map of different biomes
======================================================================================================================================
*/
vector<vector<Data> > Map_Gen(vector<Data> Biome_Types){

    vector<Data> temp;
    vector<vector<Data> > to_return;
    int rando = 0;

    for(int i=0;i<10;i++){

        for(int j=0;j<10;j++){
    
            if(i == 0 || i == 9 || j == 0 || j == 9){
                temp.push_back(Biome_Types[0]);
            }

            else{
                rando = rand() % 5;
                temp.push_back(Biome_Types[rando]);
            }
        }

        to_return.push_back(temp);
        temp.clear();
    }
    return to_return;
}

/*
======================================================================================================================================
Function    : Starting_point_rand
Parameters  : N/A
Return      : a player object with a randomized x and y cord
Description : initializes a players position by two random numbers on the grid
======================================================================================================================================
*/
Player Starting_point_rand(){

    Player temp_p;

    temp_p.x = rand() % 8 + 1;
    temp_p.y = rand() % 8 + 1;

    return temp_p;
}

/*
======================================================================================================================================
Function    : Print_map
Parameters  : a vector of vector of the data struct, and a player obj for player position
Return      : N/A
Description : Given the data 2D vector and the players position it pronts out the current map
======================================================================================================================================
*/
void Print_map(vector<vector<Data> > Map, Player player){
    for(int i=0;i<Map.size();i++){
        for(int j=0;j<Map[i].size();j++){

            if(j == player.x && i == player.y){ // if the player is on that "square"
                cout << "\033[1;31m" << " P " << "\033[0m";
            }
            else{ // otherwise prints the Letter of the Biome 
                if(Map[i][j].Biome_L == 'G'){ // grassland
                    cout << " " << "\033[1;92m" << Map[i][j].Biome_L << "\033[0m" << " ";
                }
                if(Map[i][j].Biome_L == 'M'){ // mountain
                    cout << " " << "\033[1;37m" << Map[i][j].Biome_L << "\033[0m" << " ";
                }
                if(Map[i][j].Biome_L == 'S'){ // swamp
                    cout << " " << "\033[32m" << Map[i][j].Biome_L << "\033[0m" << " ";
                }
                if(Map[i][j].Biome_L == 'F'){ // forest
                    cout << " " << "\033[1;32m" << Map[i][j].Biome_L << "\033[0m" << " ";
                }
                if(Map[i][j].Biome_L == 'D'){ // desert
                    cout << " " << "\033[1;33m" << Map[i][j].Biome_L << "\033[0m" << " ";
                }
                if(j == Map[i].size()-1){
                    cout  << endl;
                }
            }
        }
    }
}

/*
======================================================================================================================================
Function    : Player_choice
Parameters  : Player struct
Return      : returns a player struct 
Description : takes in a player struct and returns the same player after letting the player choose what they wanted to do
======================================================================================================================================
*/
Player Player_choice(Player player){

    string choice;
    stringstream input;
    string temp;

    cout << "What would you like to do?" << endl;
    
    do
    {   
        cout << "For help on different commands type help" << endl;
        cout << "-----------" << endl;
        
        getline(cin, choice);
        input.str(choice);

        getline(input, temp, ' ');
        Normalize(temp);
 
        if(temp == "help"){
            Print_tips(player);
        }
        else if(temp == "travel"){

            getline(input, temp, ' ');
            Normalize(temp);
          
            if(temp == "north" && player.y != 1){
                player.y--;
            }
            else if(temp == "south" && player.y != 8){
                player.y++;
            }
            else if(temp == "west" && player.x != 1){
                player.x--;
            }
            else if(temp == "east" && player.x != 8){
                player.x++;
            }

            else{
                cout << "I'm sorry that direction is not valid." << endl;
                choice = "F";
                input.clear();
            }
        }
        else if(temp == "exit" || temp == "quit" || temp == "leave"){
            exit(1);
        }
        else{
            cout << "I'm sorry thats didn't quite work, can you re-type that please." << endl;
            choice = "F";
            input.clear();
        }

    }while(choice == "F");

    return player;
}

/*clears the screen, no paramaters, trash code tbh*/
void ClearScreen(){cout << string( 100, '\n' );}

/*
======================================================================================================================================
Function    : Print_tips
Parameters  : Player struct
Return      : N/A
Description : prints out the different commands a player can choose
======================================================================================================================================
*/
void Print_tips(Player player){
    int num_space = 0;
    string q;
    ClearScreen();
    cout << "--------TIPS--------" << endl;
    if(player.y != 1){
        cout << "Travel North" << endl;
    }
    else{
        num_space++;
    }
    if(player.y != 8){
        cout << "Travel South" << endl;    
    }
    else{
        num_space++;
    }
    if(player.x != 1){
        cout << "Travel West" << endl;    
    }
    else{
        num_space++;
    }
    if(player.x != 8){
        cout << "Travel East" << endl;    
    }
    else{
        num_space++;
    }
    for(int i=0;i<num_space;i++){
        cout << endl;
    }
    cout << "To exit tip menu type q" << endl;
    getline(cin, q);
    while(q != "q"){
        cout << "... boi" << endl;
        getline(cin, q);
    }
}

/*
======================================================================================================================================
Function    : Normalize
Parameters  : string
Return      : string
Description : takes in a string and converts it all to lower case for steralizing input
======================================================================================================================================
*/
void Normalize(string& raw){transform(raw.begin(), raw.end(), raw.begin(), ::tolower);}
