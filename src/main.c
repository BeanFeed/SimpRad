/*
 *--------------------------------------
 * Program Name:
 * Author:
 * License:
 * Description:
 *--------------------------------------
*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/getkey.h>
#include <math.h>
#include <debug.h>
#include <stdbool.h>


bool Equality(float a, float b, float epsilon)
{
    return fabsf(a - b) < epsilon;
}
float smartRound(float x) {
    if(Equality(x, roundf(x),1e-4)) return roundf(x);
    return x;
}
int main(void)
{
    os_ClrLCDFull();
    os_SetCursorPos(0,0);
    char strNum[5] = "";
    os_GetStringInput("Number To Simplify: ", strNum, 5);
    os_SetCursorPos(1,0);
    char strIndex[5] = "";
    os_GetStringInput("Radical Index: ", strIndex, 5);
    os_SetCursorPos(2,0);
    int num = -1;
    int index = -1;
    num = (int)strtod(strNum, NULL);
    index = (int)strtod(strIndex, NULL);
    if(num == -1 || index == -1) {
        os_ClrLCDFull();
        os_PutStrFull("Invalid Inputs. Press Key To Exit...");
        while(!os_GetCSC());
        return 0;
    }
    dbg_printf("Num: %d, Index: %d\n", num, index);
    char out[50] = "";
    for(double i = 2; i < ceil((double)num / 2); i++) {
        dbg_printf("Remainder of i = %d, %d\n", (int)i, (int)fmod(num, i));
        if(fmod(num, i) == 0) {
            dbg_printf("Num / I: %f\n", num / i);
            dbg_printf("Pow1: %f\n", smartRound(pow(num / i, 1.0 / (double)index)));
            dbg_printf("Mod1: %f\n", fmod(smartRound(pow(num / i, 1.0 / index)), 1));
            //dbg_printf()
            //dbg_printf("Pow2: %f\n", pow(i, 1.0 / (double)index));
            if(Equality(fmod(smartRound(pow(num / i, 1.0 / index)), 1.0), 0.0, 1e-4)) {
                dbg_printf("This one: %f\n", i);
                sprintf(out, "%d rad(%d)", (int)smartRound(pow(num/i, 1.0 / (double)index)), (int)i);
                i = ceil((double)num / 2);
            }else if(Equality(fmod(smartRound(pow(i, 1.0 / index)), 1.0), 0.0, 1e-4)) {
                sprintf(out, "%d rad(%d)", (int)smartRound(pow(i, 1.0 / (double)index)), (int)num);
                i = ceil((double)num / 2);
            }
        }
    }
    os_PutStrLine(out);
    os_SetCursorPos(3,0);
    os_PutStrLine("Press Any Key To Exit...");
    while (!os_GetCSC());
    return 0;
}
