#include <stdio.h>
#include <string.h>
#include <time.h>
#include "rpg.h"
#include "names.c"

#define PLAYER_NAME_MAX 32
#define EVENT_NAME_MAX 32

Player player_init(char *name)
{
    Player p;
    p.hp = 100;
    p.damage = 10;
    p.xp = 0;
    p.level = 1;
    strncpy(p.name, name, PLAYER_NAME_MAX - 1);
    p.name[PLAYER_NAME_MAX - 1] = '\0';
    return p;
}

void player_greet(Player *p)
{
    printf("Welcome to the game, %s!\n", p->name);
}

void player_level_up(Player *player)
{
    player->level += player->xp / 100;
    player->xp %= 100;
    printf("%s is now level %d!", player->name, player->level);
}
void player_add_xp_combat(Player *attacker, Player *target)
{
    int xp = target->level * 10;
    attacker->xp += xp;
    printf("%s gained %d for defeating %s!", attacker->name, xp, target->name);
    if (attacker->xp >= 100)
    {
        player_level_up(attacker);
    }
}
void player_attack(Player *attacker, Player *target)
{
    target->hp -= attacker->damage;
    printf("%s attacks %s for %d damage!\n", attacker->name, target->name, attacker->damage);
    if (target->hp <= 0)
    {
        player_add_xp_combat(attacker, target);
    }
}

void player_add_xp_event(Player *player, Event *event)
{
    player->xp += event->xp;
}

void player_info(Player *player)
{
    printf("Name: %s;\nHP: %d;\nDMG: %d;\nXP: %d;\nLVL: %d.\n", player->name, player->hp, player->damage, player->xp, player->level);
}

void player_welcome(Player *player)
{
    player_greet(player);
    player_info(player);
}

int main(void)
{
    srand(time(NULL));
    names_init("adjectivelist.txt", "nounlist.txt");

    char name[PLAYER_NAME_MAX];
    while (1)
    {
        printf("Enter your name: ");
        fflush(stdout);

        if (!fgets(name, sizeof(name), stdin))
        {
            return 1;
        }

        size_t len = strlen(name);

        if (len > 0 && name[len - 1] != '\n')
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("Name is too long (max %d characters).\n", PLAYER_NAME_MAX - 1);
            continue;
        }

        if (len > 0 && name[len - 1] == '\n')
        {
            name[len - 1] = '\0';
        }

        if (strlen(name) == 0)
        {
            printf("Name can't be empty.\n");
            continue;
        }

        break;
    }

    Player player = player_init(name);
    player_welcome(&player);

    generate_name(name, sizeof(name));

    return 0;
}