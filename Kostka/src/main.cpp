
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <vector>
#include <string.h>
#include <stdio.h>

class Kostka {
public:
    Kostka();
    virtual ~Kostka();
    virtual uint8_t roll(){
        struct timespec t;
        timespec_get(&t, TIME_UTC);
        return (1 + sin(t.tv_nsec) * 3);
    }
};
Kostka::Kostka(){
    
}
Kostka::~Kostka(){
    
}
class ZlobivaKostka : public Kostka{
public:
    using Kostka::Kostka;
    uint8_t roll() override{
        puts("Hop");
        struct timespec t;
        timespec_get(&t, TIME_UTC);
        uint8_t res = (1 + sin(t.tv_nsec) * 4);
        if(res > 6){
            res = 1; 
        }
        return res;
    }
};


class Player {
public:
    char* name;
    uint32_t points;
    std::vector<Kostka*> kostky;
    Player(const char* name = NULL);
    ~Player();
    void roll(){
        size_t l = this->kostky.size();
        uint8_t prevres = -1;
        uint8_t rolls[l];
        for(size_t i = 0; i < l; i++){
            uint8_t res = this->kostky[i]->roll();
            if(res == 1){
                return; //No points added
            }
            if(prevres != -1){
                if(prevres == 1){
                    //Two ones, reseting points
                    this->resetPoints();
                    return;
                }
            }
            rolls[i] = res;
        }
        //All rolled and checked
        for(size_t i = 0; i < l; i++){
            this->addPoints(rolls[i]);
        }
    }
    inline void resetPoints(){
        puts("Two ones, your points are reset.");
        this->points = 0;
    }
    inline void addPoints(int32_t n){
        printf("Player %s got %d points!!\n", this->name, n);
        this->points += n;
    }
    inline void addKostka(Kostka* k){
        this->kostky.push_back(k);
    }
    inline bool didReachFinalScore(){
        return this->points >= 100;
    }
    
};

Player::Player(const char* name){
    this->points = 0;
    this->name = name ? strdup(name) : NULL;
}
Player::~Player(){
    size_t l = this->kostky.size();
    while(l--){
        delete this->kostky[l];
    }
    if(this->name){
        free(this->name);
    }
}

class Hra {
public:
    std::vector<Player*> players;
    inline Player* addPlayer(const char* name){
        Player* p = new Player(strdup(name));
        players.push_back(p);
        return p;
    }
    void play();
};
void Hra::play(){
    size_t np = this->players.size();
    while(1){
        for(size_t i = 0; i < np; i++){
            printf("Hrac %d hazi kostkou. (Stisknete enter pro hod)\n >> ", i);
            fflush(stdout);
            char trash[16];
            fgets(trash, sizeof(trash), stdin);
            Player* p = players[i];
            p->roll();
            if(p->didReachFinalScore()){
                printf("Player %d won!!!\n", i);
                return;
            }else{
                printf("Player %d has %d points (Remaining: %d)\n\n", i, p->points, 100 - p->points);
            }
        }
    }
}
int main(int argc, char** argv){
    if((argc < 2) || (strcmp(argv[1], "--help") == 0)){
        puts("kostky [pocetHracu]");
        return 1;
    }
    Hra g;
    size_t np = atoi(argv[1]);
    
    for(size_t i = 0; i < np; i++){
        char buf[1024];
        printf("Player %d, what's your name?\n >> ", i);
        fflush(stdout);
        fgets(buf, sizeof(buf), stdin);
        //Cut out \n
        char* nl = strchr(buf, '\n');
        if(nl){
            *nl = '\0';
        }
        
        Player* p = g.addPlayer(buf);
        printf("Player %d, chcete zlobivou kostku (Y/n)\n >> ", i);
        fgets(buf, sizeof(buf), stdin);
        p->addKostka((*buf != 'n') ? new ZlobivaKostka() : new Kostka());
    }
    g.play();
    puts("Game finished");
    return 0;
    //Main program starts here

}


