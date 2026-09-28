#ifndef RPG_H
#define RPG_H

#define PLAYER_NAME_MAX 32
#define EVENT_NAME_MAX 32

typedef struct
{
    char name[PLAYER_NAME_MAX];
    int hp;
    int damage;
    int xp;
    int level;
} Player;

typedef struct
{
    char name[EVENT_NAME_MAX];
    char description[100];
    int xp;
} Event;

Player player_init(char *name);
void player_greet(Player *p);
void player_level_up(Player *player);
void player_add_xp_combat(Player *attacker, Player *target);
void player_attack(Player *attacker, Player *target);
void player_add_xp_event(Player *player, Event *event);
void player_info(Player *player);
void player_welcome(Player *player);

#endif