#include <iostream>
#include <ctime>

/*
Basic 0 player game

Conway's Game of Life

Author: Dylan Clarke
*/
using namespace std;


//global constants
const int MAXGEN = 3;   //max number of generations
const int n = 5;       //number of rows
const int m = 5;       //number of columns

//function called by entering 'm' in main, loops through until the user has entered nm 1s and 0s
void initialize(int grid[n][m]){
    int input;
    cout << "Indicate with a sequence of 0 and 1 the state of the cells: " << endl;
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            cin >> input;
            grid[i][j] = input;
        }
    }
}
//function called by entering 'r' in main, initializes array based on the given density
void initialize2 (int grid[n][m],int density){
    srand(time(0));
    int r;
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            r = rand() % 100+1;
            if (r<=density){
                grid[i][j] = 1;
            }else{
                grid[i][j] = 0;
            }
        }
    }
}

//counts the number of live neighbors in a given cell, excludes coordinates out of bounds when counting
int countNeighbors(int grid[n][m],int x,int y){
    int neighbors = 0;
    for (int i=x-1; i<x+2; i++){
        for (int j=y-1; j<y+2; j++){
            if (i >=0 && j >=0 && (i != x || j != y) && (i < n && j < m)){
                neighbors+= grid[i][j];

        }
    }
}
    return neighbors;
}

//checks if population is dead, if loop encounters a live cell, breaks and returns false bool value
bool allDead(int grid[n][m]){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if (grid[i][j]==1)
            return false;
            break;
        }
    }
    return true;
}

//function to produce a new generation of cells by mapping changes onto another array
void reproduce(int grid[n][m]){
    int live;
    int grid2[n][m];
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            grid2[i][j] = grid[i][j];
        }
    }


    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            live = countNeighbors(grid,i,j);   //pass i and j from for loop as parameters
            if (live <2 && grid[i][j] == 1){
                grid2[i][j] = 0;     //fewer than 2 dies, underpopulation, rule 1
            }else if (live>3 && grid[i][j]==1){
                grid2[i][j]=0;   //greater than 3 dies, overpopulation, rule 2
            }else if ((live == 2 || live == 3) && grid[i][j]==1){
                grid2[i][j]=1;   //exactly 2 or 3 live lives, rule 3
            }else if (live ==3 && grid[i][j]==0){
                grid2[i][j]=1;   //dead cell 3 live lives, reproduction, rule 4
            }
    }
    }
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            grid[i][j] = grid2[i][j];
        }
    }
}

//prints the current generation of cells in an nxm grid pattern, nicely formatted
void print(int grid[n][m]){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

//main function to request user input and execute function calls, running the game of life
int main(){
    int grid[n][m];
    char input;
    int density;
    cout << "How would you like to initialize the grid?" << endl;
    cout << "Enter 'm' to manually enter it, or 'r' to randomly generate it." << endl;
    cin >> input;
    if (input == 'm'){
        initialize(grid);
    } else if (input == 'r'){
        do{
            cout << "Enter a number between 0 and 100 for the density of the cell population: " << endl;
            cin >> density;
        }while (density > 100 || density < 0);
        initialize2(grid,density);
    }
    cout << "Initial population = " << endl;
    print(grid);
    cout << endl;
    int gen = 1;
    while (gen <=MAXGEN && !allDead(grid)){
        cout << endl;
        cout << "gen = " << gen << endl;
        reproduce(grid);
        print(grid);
        gen++;
    }
        return 0;
}
