#define MAX_PLAYERS 4

#define MDC_WARRIORS 25
#define ED_WARRIORS 20
#define WA_WARRIORS 10

#define SAWMILLS 6
#define WORKSHOPS 6
#define RECRUITERS 6
#define ROOSTS 7
#define FOX_BASES 1
#define RABBIT_BASES 1
#define MOUSE_BASES 1

#define WOODS 8
#define SYMPATHIES 10
#define KEEPS 1

#define NO_POSITION -1

enum ERROR_TYPE {
    NO_ERROR,
    ILLEGAL_MOVE
};

enum TURN_PHASE {
    BIRDSONG,
    DAYLIGHT,
    EVENING
};

enum FACTION {
    MARQUISE_DE_CAT,
    EYRIE_DYNASTIES,
    WOODLAND_ALLIANCE,
    VAGABOND
};

enum SHARED_CARD_SUIT {
    FOX,
    RABBIT,
    MOUSE,
    BIRD
};

enum ITEM {
    COIN_STACK,
    TEA,
    HAMMER,
    LEATHER,
    CROSSBOW,
    SWORD
};

enum SLOT_TYPE {
    NONE,
    NORMAL,
    RUIN
};

enum BUILDING_TYPE {
    NO_BUILDING,
    // MDC
    SAWMILL,
    WORKSHOP,
    RECRUITER,
    // ED
    ROOST,
    // WA
    FOX_BASE,
    RABBIT_BASE,
    MOUSE_BASE
};

typedef struct building_t {
    enum BUILDING_TYPE type;
    // a -1 position means its in the respective inventory
    int position;
    // slot in the clearing
    unsigned int slot;
} building;

enum TOKEN_TYPE {
    WOOD, // 8
    SYMPATHY, // 10
    KEEP // 1
};

enum WARRIOR_TYPE {
    MDC_WARRIOR, // 25
    ED_WARRIOR, // 20
    WA_WARRIOR // 10
};

typedef struct clearing_t {
    unsigned int slots;
    unsigned int neighbours[4];
} clearing;

typedef struct warrior_t {
    enum WARRIOR_TYPE type;
    int position;
} warrior;

typedef struct token_t {
    enum TOKEN_TYPE type;
    int position;
} token;

typedef struct map_t {
    clearing clearings[12];
    warrior warriors[MDC_WARRIORS + ED_WARRIORS + WA_WARRIORS];
    building buildings[SAWMILLS + WORKSHOPS + RECRUITERS + ROOSTS + FOX_BASES + RABBIT_BASES + MOUSE_BASES];
    token tokens[WOODS + SYMPATHIES + KEEPS];
} map;

void build_neighbours(map* this_map) {
    /*
     * 0 ---- 1 --- \
     * | \---2 ----- 3
     * |   /         |
     * 4-5 -- 6 ---- 7
     * | \     \--\  |
     * |   ---\    \ |
     * 8 - 9 - 10 - 11
    */
    // slots
    // 0 1 2 3 4 5 6 7 8 9 10 11
    // 1 2 2 2 2 2 3 2 1 2  2  1

    this_map->clearings[0].neighbours[0] = 1;
    this_map->clearings[0].neighbours[1] = 2;
    this_map->clearings[0].neighbours[2] = 4;
    this_map->clearings[0].slots = 1;

    this_map->clearings[1].neighbours[0] = 0;
    this_map->clearings[1].neighbours[1] = 3;
    this_map->clearings[1].slots = 2;

    this_map->clearings[2].neighbours[0] = 0;
    this_map->clearings[2].neighbours[1] = 3;
    this_map->clearings[2].neighbours[2] = 5;
    this_map->clearings[2].slots = 2;

    this_map->clearings[3].neighbours[0] = 1;
    this_map->clearings[3].neighbours[1] = 2;
    this_map->clearings[3].neighbours[2] = 7;
    this_map->clearings[3].slots = 2;

    this_map->clearings[4].neighbours[0] = 0;
    this_map->clearings[4].neighbours[1] = 5;
    this_map->clearings[4].neighbours[2] = 8;
    this_map->clearings[4].slots = 2;

    this_map->clearings[5].neighbours[0] = 2;
    this_map->clearings[5].neighbours[1] = 4;
    this_map->clearings[5].neighbours[2] = 10;
    this_map->clearings[5].slots = 2;

    this_map->clearings[6].neighbours[0] = 5;
    this_map->clearings[6].neighbours[1] = 7;
    this_map->clearings[6].neighbours[2] = 11;
    this_map->clearings[6].slots = 3;

    this_map->clearings[7].neighbours[0] = 3;
    this_map->clearings[7].neighbours[1] = 6;
    this_map->clearings[7].neighbours[2] = 11;
    this_map->clearings[7].slots = 2;

    this_map->clearings[8].neighbours[0] = 4;
    this_map->clearings[8].neighbours[1] = 9;
    this_map->clearings[8].slots = 1;

    this_map->clearings[9].neighbours[0] = 8;
    this_map->clearings[9].neighbours[1] = 10;
    this_map->clearings[9].slots = 2;

    this_map->clearings[10].neighbours[0] = 5;
    this_map->clearings[10].neighbours[1] = 9;
    this_map->clearings[10].neighbours[2] = 11;
    this_map->clearings[10].slots = 2;

    this_map->clearings[11].neighbours[0] = 6;
    this_map->clearings[11].neighbours[1] = 7;
    this_map->clearings[11].neighbours[2] = 10;
    this_map->clearings[11].slots = 1;
}

void setup_warriors(map* this_map) {
    unsigned int min = 0;
    unsigned int max = MDC_WARRIORS;
    for(unsigned int i = min; i < max; i++)
        this_map->warriors[i].type = MDC_WARRIOR;
    min = max;
    max += ED_WARRIORS;
    for(unsigned int i = min; i < max; i++)
        this_map->warriors[i].type = ED_WARRIOR;
    min = max;
    max += WA_WARRIORS;
    for(unsigned int i = min; i < max; i++)
        this_map->warriors[i].type = WA_WARRIOR;

    for(unsigned int i = 0; i < MDC_WARRIORS + ED_WARRIORS + WA_WARRIORS; i++)
        this_map->warriors[i].position = NO_POSITION;
}

void setup_buildings(map* this_map) {
    unsigned int min = 0;
    unsigned int max = SAWMILLS;
    for(unsigned int i = min; i < max; i++)
        this_map->buildings[i].type = SAWMILLS;
    min = max;
    max += WORKSHOPS;
    for(unsigned int i = min; i < max; i++)
        this_map->buildings[i].type = WORKSHOP;
    min = max;
    max += RECRUITERS;
    for(unsigned int i = min; i < max; i++)
        this_map->buildings[i].type = RECRUITERS;
    min = max;
    max += ROOSTS;
    for(unsigned int i = min; i < max; i++)
        this_map->buildings[i].type = ROOST;
    min = max;
    max += FOX_BASES;
    for(unsigned int i = min; i < max; i++)
        this_map->buildings[i].type = FOX_BASE;
    min = max;
    max += RABBIT_BASES;
    for(unsigned int i = min; i < max; i++)
        this_map->buildings[i].type = RABBIT_BASE;
    min = max;
    max += MOUSE_BASES;
    for(unsigned int i = min; i < max; i++)
        this_map->buildings[i].type = MOUSE_BASES;

    for(unsigned int i = 0; i < max; i++) 
        this_map->buildings[i].position = NO_POSITION;
}

void setup_tokens(map* this_map) {
    unsigned int min = 0;
    unsigned int max = WOODS;
 
    for(unsigned int i = min; i < max; i++)
        this_map->tokens[i].type = WOOD;
    min = max;
    max += SYMPATHIES;
 
    for(unsigned int i = min; i < max; i++)
        this_map->tokens[i].type = SYMPATHY;
    min = max;
    max += KEEPS;
 
    for(unsigned int i = min; i < max; i++)
        this_map->tokens[i].type = KEEP;

    for(unsigned int i = 0; i < max; i++) 
        this_map->tokens[i].position = NO_POSITION;  
}

void init_map(map* this_map) {
    for(unsigned int i = 0; i < 12; i++) 
        this_map->clearings[i] = (clearing){}; 

    build_neighbours(this_map);
    setup_warriors(this_map);
    setup_buildings(this_map);
    setup_tokens(this_map);
}

typedef struct player_t {
    enum FACTION faction;
} player;

typedef struct game_t {
    player players[MAX_PLAYERS];
    map map;
} game;

// Marquise de Cat = MDC
// Eyrie Dynasties = ED
// Woodland Alliance = WA
// Vagabond = VGB
unsigned int corner_clearings[] = {0, 3, 8, 11};

int get_opposite_corner(unsigned int a) {
    switch (a) {
        case 0:
            return 11;
        case 3:
            return 8;
        case 8:
            return 3;
        case 11:
            return 0;
    }
    return NO_POSITION;
}

int get_next_unused_warrior(enum FACTION f, map* m) {
    switch (f) {
        case MARQUISE_DE_CAT:
            for(unsigned int i = 0; i < MDC_WARRIORS; i++) 
                if(m->warriors[i].position == -1)
                    return i;
            break;
        case EYRIE_DYNASTIES:
            for(unsigned int i = MDC_WARRIORS; i < MDC_WARRIORS + ED_WARRIORS; i++) 
                if(m->warriors[i].position == -1)
                    return i;
            break;
         case WOODLAND_ALLIANCE:
            for(unsigned int i = MDC_WARRIORS + ED_WARRIORS; i < MDC_WARRIORS + ED_WARRIORS + WA_WARRIORS; i++) 
                if(m->warriors[i].position == -1)
                    return i;
            break;
        default:
            break;
    }
    return NO_POSITION;
}

typedef struct mdc_setup_params_t {
    // corner of the map relating to corner_clearings (between 0-3 inclusively)
    unsigned int keep_corner;
    unsigned int sawmill_position;
    unsigned int workshop_position;
    unsigned int recruiter_position;
} mdc_setup_params;

enum ERROR_TYPE check_mdc_setup_params(mdc_setup_params* p, game* g) {
    if(p->keep_corner >= 4)
        return ILLEGAL_MOVE;
    unsigned char ok_sawmill = 0;
    unsigned char ok_workshop = 0;
    unsigned char ok_recruiter = 0;
    if(corner_clearings[p->keep_corner] == p->sawmill_position)
        ok_sawmill = 1;
    if(corner_clearings[p->keep_corner] == p->workshop_position)
        ok_workshop = 1;
    if(corner_clearings[p->keep_corner] == p->recruiter_position)
        ok_recruiter = 1;

    for(unsigned int i = 0; i < 4; i++) {
        unsigned int nei = g->map.clearings[corner_clearings[p->keep_corner]].neighbours[i];
        if(nei == p->sawmill_position)
            ok_sawmill = 1;
        if(nei == p->workshop_position)
            ok_workshop = 1;
        if(nei == p->recruiter_position)
            ok_recruiter = 1;
    }
    if(!(ok_sawmill && ok_workshop && ok_recruiter))
        return ILLEGAL_MOVE;

    return NO_ERROR;
}

enum ERROR_TYPE mdc_setup(player* p, game* g, mdc_setup_params params) {
    enum ERROR_TYPE err = check_mdc_setup_params(&params, g);
    if (err)
        return err; 
    int corner = corner_clearings[params.keep_corner];
    int opposite_corner = get_opposite_corner(corner_clearings[params.keep_corner]);

    for(unsigned int i = 0; i < 12; i++) {
        if(i == opposite_corner)
            continue;
        g->map.warriors[get_next_unused_warrior(MARQUISE_DE_CAT, &g->map)].position = i;
    }
    return NO_ERROR;
}

typedef struct ed_setup_params_t {
    unsigned int leader;
} ed_setup_params; 

enum ERROR_TYPE ed_setup(player* p, game* g, ed_setup_params params) {
    return NO_ERROR;
}

int main(int argc, char** argv){
}

