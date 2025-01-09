
#ifndef DUNGEON_H
#define DUNGEON_H

typedef struct {
  int width;
  int height;
  int **grid;
  int initial_health;
  int start_x;       
  int start_y;       
  int end_x;        
  int end_y;          
} Dungeon;

typedef struct {
    int health;  
    int from_x;   
    int from_y;   
} Cell;

#endif