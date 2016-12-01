#include "player.h"

Player* InitPlayer(unsigned int side)
{
	Player *p=(Player *) malloc(sizeof(Player));


	p->units=(gqueue_t *) new_gqueue_t(MAX_UNITS, sizeof(Unit));
	p->t=(Tower *) malloc(sizeof(Tower));
	/*p->s=(Special *) malloc(sizeof(Special));
	p->s=InitSpecial();
	p->d=(Defense *) malloc(sizeof(Defense));*/

	return p;

}

void updatePlayer(Player* p)
{
	//fazer isto
	gqueue_t *aux_units=p->units;
	Unit* u=(Unit*) malloc(sizeof(Unit));
	while(!is_empty_gqueue(p->units))
	{

		if(get_gqueue(p->units, u)!=0)
			return;
		//fazer -> updateUnit(u);
	}
	deleteUnit(u);
	p->units=aux_units;
}

void deletePlayer(Player* p)
{
	delete_gqueue_t(p->units);
	free(p);
}
void addUnits(Player* p, Unit* u)
{
	if(put_gqueue(p->units, u)!=0)
		return;

}
