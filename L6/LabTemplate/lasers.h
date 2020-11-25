#ifndef LASERS_H
#define LASERS_H

// struct
struct laser {
	char name[20];			// system name
	int ECL;						// Energy Class Level
	int POP;						// Peak Output Power
	float ORP;					// Optical Replacement Percentage
};

// functions
void populateLasers(struct laser* default_table);
void checkUpgrade(struct laser x);

#endif
