/* case.h */

#ifndef __case__
#define __case__


    typedef struct {
        int x;
        int y;
    } Case;

    typedef struct cases {
        Case c;
        struct cases* next_case;
    } Cases;

    typedef enum {
        Nord,
        Est, 
        Sud,
        Ouest
    } Direction;

    Case creer_case(int x, int y);
    Cases* empile_case(Cases* liste, Case c);



#endif
