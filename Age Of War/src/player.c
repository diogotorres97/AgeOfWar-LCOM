#include "player.h"

/******************************************** Player functions *****************************************/

Player *InitPlayer(unsigned int side) {
    Player *p = (Player *) malloc(sizeof(Player));


    int counter = 0;


    while (counter < MAX_UNITS) {
        p->units[counter] = (Unit *) malloc(sizeof(Unit));
        p->units[counter] = NULL;
        counter++;
    }
    counter = 0;
    while (counter < MAX_DEFENSES) {
        p->defenses[counter] = (Defense *) malloc(sizeof(Defense));
        p->defenses[counter] = NULL;
        counter++;
    }

    counter = 0;
    while (counter < MAX_SLOTS) {
        p->slots_defenses[counter] = (Slot *) malloc(sizeof(Slot));
        p->slots_defenses[counter] = NULL;
        counter++;
    }

    p->side = side;
    p->experience = 0;
    p->money = INITIAL_MONEY;
    p->level = 1;
    p->slots_available = 1;
    p->income_per_level = INCOME_LEVEL1;
    p->defense_current_range = DEFENSE_RANGE1;


    return p;

}

void setLevel(Player *p, unsigned int level) {
    p->level = level;
}

void setMoney(Player *p, int newMoney) {
    p->money += newMoney;
}

void setIncome(Player *p, int income) {
    p->income_per_level = income;
}

void setExperience(Player *p, int newExp) {
    p->experience += newExp;
}

void setDefenseRange(Player *p, int newRange) {
    p->defense_current_range = newRange;
}

void deletePlayer(Player *p) {

    free(p);
}

void addUnits(Player *p, Unit *u) {

    p->units[newPosUnit(p)] = u;


}

int emptyUnits(Player *p) {
    int counter = 0;
    while (counter < MAX_UNITS) {
        if (p->units[counter] != NULL) {
            return 0;
        }
        counter++;
    }
    return 1;
}

int fullUnits(Player *p) {
    int counter = 0;
    while (counter < MAX_UNITS) {
        if (p->units[counter] == NULL) {
            return 0;
        }
        counter++;
    }
    return 1;
}

int countUnits(Player *p) {
    int counter = 0;
    int res = 0;
    while (counter < MAX_UNITS) {

        if (p->units[counter] != NULL) {
            res += 1;

        } else {

        }

        counter++;
    }

    return res;
}

int countDefenses(Player *p) {
    int counter = 0;
    int res = 0;
    while (counter < MAX_DEFENSES) {
        if (p->defenses[counter] != NULL) {
            res++;
        }
        counter++;
    }
    return res;
}

int countSlots(Player *p) {
    int counter = 1;
    int res = 0;
    while (counter < MAX_DEFENSES) {
        if (p->defenses[counter] != NULL) {
            res++;
        }
        counter++;
    }
    return res;
}

int newPosUnit(Player *p) {
    int counter = 0;
    while (counter < MAX_UNITS) {
        if (p->units[counter] == NULL)
            return counter;
        counter++;
    }
}

int newPosDefense(Player *p) {
    int counter = 0;
    while (counter < MAX_DEFENSES) {
        if (p->defenses[counter] == NULL)
            return counter;
        counter++;
    }
    return -1;
}

int newPosSlot(Player *p) {
    int counter = 0;
    while (counter < MAX_SLOTS) {
        if (p->slots_defenses[counter] == NULL)
            return counter;
        counter++;
    }
    return counter;
}

int emptyDefenses(Player *p) {
    int counter = 0;
    while (counter < MAX_DEFENSES) {
        if (p->defenses[counter] != NULL) {
            return 0;
        }
        counter++;
    }
    return 1;
}

int fullDefenses(Player *p) {
    int counter = 0;
    while (counter < MAX_DEFENSES) {
        if (p->defenses[counter] == NULL) {
            return 0;
        }
        counter++;
    }
    return 1;
}

int emptySlots(Player *p) {
    int counter = 1;
    while (counter < MAX_SLOTS) {
        if (p->slots_defenses[counter] != NULL) {
            return 0;
        }
        counter++;
    }
    return 1;
}

int fullSlots(Player *p) {
    int counter = 1;
    while (counter < MAX_SLOTS) {
        if (p->slots_defenses[counter] == NULL) {
            return 0;
        }
        counter++;
    }
    return 1;
}


void addSlots(Player *p, Slot *s) {
    p->slots_defenses[newPosSlot(p)] = s;
}

void addDefenses(Player *p, Defense *d) {
    p->defenses[newPosDefense(p)] = d;
}

int checkUnitCollisionSamePlayer(Unit *u1, Unit *u2, int player) {
    if (player == 1) {
        if ((u1->x + u1->width) >= u2->x) {
            return 1;
        }
    } else {
        if ((u1->x - u1->width) <= u2->x) {
            return 1;
        }
    }

    return 0;
}

int checkUnitsTowerCollision(Unit *u, Tower *t) {
    if (t->player == 1) {
        if (u->x - u->width <= t->x + t->width) {
            return 1;
        }
    } else {
        if (u->x + u->width >= t->x - t->width) {
            return 1;
        }
    }
    return 0;
}


int checkBulletsTowerCollision(Bullet *b, Tower *t) {

    if (t->player == 1) {

        if (b->x - b->width <= t->x + t->width) {
            return 1;
        }
    } else {
        if (b->x + b->width >= t->x - t->width) {
            return 1;
        }
    }
    return 0;
}

int checkUnitsDefenseRange(Unit *u, Defense *d) {
    if (d->player == 1) {

        if (u->x - u->width <= d->x + d->width + d->range) {
            return 1;
        }
    } else {
        if (u->x + u->width >= d->x - d->width - d->range) {
            return 1;
        }
    }
    return 0;
}

int checkUnitTowerRange(Unit *u, Tower *t) {

    if (t->player == 1) {

        if (u->x - u->width - u->range <= t->x + t->width) {
            return 1;
        }
    } else {
        if (u->x + u->width + u->range >= t->x - t->width) {
            return 1;
        }
    }
    return 0;
}

void removeUnit(Player *p) {
    int counter = 0;
    while (counter < MAX_UNITS) {

        if (counter != MAX_UNITS - 1) {
            if (p->units[counter] != NULL) {
                p->units[counter] = p->units[counter + 1];

            } else
                return;
        } else {
            p->units[counter] = NULL;
            return;
        }
        counter++;
    }
}

void removeDefense(Player *p) {
    int counter = 0;
    int array_ys[4];
    while (counter < MAX_DEFENSES) {
        if (p->defenses[counter] != NULL) {
            array_ys[counter] = p->defenses[counter]->y;
        }
        counter++;
    }


    counter = 0;
    while (counter < MAX_DEFENSES) {

        if (counter != MAX_DEFENSES - 1) {
            if (p->defenses[counter] != NULL) {
                if (p->defenses[counter + 1] != NULL) {

                    p->defenses[counter] = p->defenses[counter + 1];

                    p->defenses[counter]->y = array_ys[counter];
                } else {
                    p->defenses[counter] = p->defenses[counter + 1];
                }


            } else
                return;
        } else {
            p->defenses[counter] = NULL;
            return;
        }
        counter++;
    }
}

void removeSlot(Player *p) {
    int counter = 1;
    while (counter < MAX_SLOTS) {

        if (counter != MAX_SLOTS - 1) {
            if (p->slots_defenses[counter] != NULL) {

                p->slots_defenses[counter] = p->slots_defenses[counter + 1];

            } else
                return;
        } else {
            p->slots_defenses[counter] = NULL;
            return;
        }
        counter++;
    }
}
