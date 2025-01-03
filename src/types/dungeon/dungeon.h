
#ifndef DUNGEON_H
#define DUNGEON_H

typedef struct Dungeon {
  int width;
  int height;
  char **grid;
  int initial_health;
  int start_x;       
  int start_y;       
  int end_x;        
  int end_y;          
} Dungeon;

#endif