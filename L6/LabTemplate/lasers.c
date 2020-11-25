/*Include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lasers.h"

/* Populates laser array with 4 lasers and respective attributes */
void populateLasers(struct laser* default_table) {
	strcpy(default_table[0].name, "L1 - LNL");
	default_table[0].ECL = 3;
	default_table[0].POP = 289;
	default_table[0].ORP = .33;	
	
	strcpy(default_table[1].name, "L2 - ELI");
	default_table[1].ECL = 2;
	default_table[1].POP = 200;
	default_table[1].ORP = .25;	
	
	strcpy(default_table[2].name, "L3 - TNL");
	default_table[2].ECL = 4;
	default_table[2].POP = 170;
	default_table[2].ORP = .33;	
	
	strcpy(default_table[3].name, "L4 - NEL");
	default_table[3].ECL = 3;
	default_table[3].POP = 236;
	default_table[3].ORP = .4;	
}

/* Checks upgrade critera for given laser
		prints to terminal upgrade eligability */
void checkUpgrade(struct laser x) {
	if (x.ECL == 2 || x.ECL ==3) {
		if (x.POP < 275) {
			if (x.ORP < 0.35f) {
				printf("%s IS eligible for an upgrade\n\r", x.name);
				return;
			}
		}
	}
	printf("%s is NOT eligible for an upgrade\n\r", x.name);
}
