/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"


//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************

int AddIn_main(int isAppli, unsigned short OptionNum)
{
    int getInput();
    void nextXY(int numpad[9], int numY[3], int nXY[2]);
    void miniTTT(int xOffset, int yOffset);
    void drawShape(int xOffset, int yOffset, int shape[3][3]);
    void initDisp();
    void drawOutline(int XY[2]);
    void eraseOutline(int XY[2]);
    void memorize(int memory[3][3][3][3], int XY1[2], int XY2[2], int player);
    void nextMove(int memory[3][3][3][3], int nXY[2], int numpad[9], int numY[3], int XY[2]);
    
    unsigned int key;
    int c = 0;
    
    int numpad[9] = {
    7, 8, 9,
    4, 5, 6,
    1, 2, 3};
    
    int memory[3][3][3][3] = {
    {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}},
    
    {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
   
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}},
    
    {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}
    };
    
    
    
    int numY[3] = {0, 1, 2};
    
    int XY1[2] = {0, 0};
    int XY2[2] = {0, 0};
    int nXY[2] = {0, 0};

    int circle[3][3] = {  
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };
    
    int cross[3][3] = { 
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}
    };

    int* shape;

    Bdisp_AllClr_DDVRAM();
    initDisp();
    Bdisp_PutDisp_DD();
    
    while(1){
        //if (c%2){
            //shape = circle;
        //}
        //else{
            //shape = cross;
        //}
        
        nextMove(memory, nXY, numpad, numY, XY2);
        XY1[0] = XY2[0];
        XY1[1] = XY2[1];
        XY2[0] = nXY[0];
        XY2[1] = nXY[1];
        
        memorize(memory, XY1, XY2, (c%2)+1);
        
        drawShape(XY2[0]*6+4+XY1[0]*20, XY2[1]*6+4+XY1[1]*20, circle);   
        Bdisp_PutDisp_DD();
        
        c++;
    }
    

    GetKey(&key);
    return 1;
}

int getInput(){
    unsigned int key;
    GetKey(&key);
    
    while (key < 49 || key > 57){
        GetKey(&key);
    }
    return(key-48);
}

void nextXY(int numpad[9], int numY[3], int XY[2]){
    int inp = getInput(); 
    inp = numpad[inp-1];
    
    XY[0] = (inp-1)%3;
    XY[1] = numY[(inp-1)/3];
}

void miniTTT(int xOffset, int yOffset){
    int i;
    
    for (i=6; i<18; i+=6){
    Bdisp_DrawLineVRAM(i+xOffset, 1+yOffset, i+xOffset, 17+yOffset);  //vertikal
    Bdisp_DrawLineVRAM(1+xOffset, i+yOffset, 17+xOffset, i+yOffset);  //horizontal
    }
}

void drawShape(int xOffset, int yOffset, int shape[3][3]){
    int x;
    int y;
    
    for (y=0; y<3; y++){
        for (x=0; x<3; x++){  
            Bdisp_SetPoint_VRAM(x+xOffset, y+yOffset, shape[y][x]);
        }
    }
}

void drawOutline(int XY[2]){
    Bdisp_DrawLineVRAM(2+XY[0]*20, 2+XY[1]*20, 2+XY[0]*20, 20+XY[1]*20);
    Bdisp_DrawLineVRAM(2+XY[0]*20, 20+XY[1]*20, 20+XY[0]*20, 20+XY[1]*20);
    Bdisp_DrawLineVRAM(20+XY[0]*20, 20+XY[1]*20, 20+XY[0]*20, 2+XY[1]*20);
    Bdisp_DrawLineVRAM(20+XY[0]*20, 2+XY[1]*20, 2+XY[0]*20, 2+XY[1]*20);
}

void eraseOutline(int XY[2]){
    Bdisp_ClearLineVRAM(2+XY[0]*20, 2+XY[1]*20, 2+XY[0]*20, 20+XY[1]*20);
    Bdisp_ClearLineVRAM(2+XY[0]*20, 20+XY[1]*20, 20+XY[0]*20, 20+XY[1]*20);
    Bdisp_ClearLineVRAM(20+XY[0]*20, 20+XY[1]*20, 20+XY[0]*20, 2+XY[1]*20);
    Bdisp_ClearLineVRAM(20+XY[0]*20, 2+XY[1]*20, 2+XY[0]*20, 2+XY[1]*20);
}

void memorize(int memory[3][3][3][3], int XY1[2], int XY2[2], int player){
    memory[XY1[1]][XY1[0]][XY2[1]][XY2[0]] = player;
} 

void nextMove(int memory[3][3][3][3], int nXY[2], int numpad[9], int numY[3], int XY[2]){
    while (memory[XY[1]][XY[0]][nXY[1]][nXY[0]] != 0){
        nextXY(numpad, numY, XY);
    }
}

void initDisp(){
    int i;
    int x;
    int y;

    for (i=21; i<60; i+=20){ //große Linien
        Bdisp_DrawLineVRAM(i, 2, i, 60);  //vertikal
        Bdisp_DrawLineVRAM(2, i, 60, i);  //horizontal
    }
    
    for (y=0; y<3; y++){
        for (x=0; x<3; x++){
            miniTTT(x*20+2, y*20+2); //kleine Linien
        }
    }
}



//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

