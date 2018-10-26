typedef struct _ent {
	const char *name;
	int8_t x;
	int8_t y;
} Entity;

typedef struct _ents {
	Entity *ents[256];
	uint8_t size;
} Entities;

uint8_t num_items = 0;
Entities Ents;

uint8_t add_ent(Entity *e)
{
	Ents.ents[num_items] = e;
	num_items++;
	Ents.size = Ents.size + 1;
	return 1;
}