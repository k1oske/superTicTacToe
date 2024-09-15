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
    void miniTTT(int xOffset, int yOffset);
    void drawShape(int xOffset, int yOffset, int shape[3][3]);
    void initDisp();
    
    unsigned int key;
    int input;
    int x,y;
    
    int numpad[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
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

    Bdisp_AllClr_DDVRAM();
    
    initDisp();
    Bdisp_PutDisp_DD();
     
//    x = ((numpad[input+3%3][input-1%3]-1%3)+1*6)+4;
//    y = ((input-1%3)+1*6)+4;
//    drawShape(x, y, cross);
//    Bdisp_PutDisp_DD();

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

