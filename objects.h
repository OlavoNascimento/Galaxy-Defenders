#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED


typedef struct{
    int ID;
    int x;
    int y;
    int lives;
    int speed;
    int score;
}spaceship;


typedef struct{
    int ID;
    int x;
    int y;
    int live;
    int speed;
}bullet;


typedef struct{
    float x;
    float y;
    float velx;
    float vely;
    int live;
    int totalframes;
    int currentframe;
    int framedelay;
    int framecounter;
    int framewidth;
    int frameheight;

}enemy;

#endif // OBJECTS_H_INCLUDED
