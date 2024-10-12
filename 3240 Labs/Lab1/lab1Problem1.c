#include <stdio.h>
/***********************************************************************************
Programmer: Karigan Stewart
Date : 08-27-24
Purpose : This program is to take input from the user regarding the temperatures
orginal scale, the scale the temperature is to be converted to, and the temperature 
being converted. The program will then convert the given value to the correct 
temperature scale and display the converted value

***********************************************************************************/
int main(){
    char startTempScale;         //Hold starting temp scale
    char targetTempScale;        //Holds targer Temp scale
    double originalTemp;         //Holds original temperature
    double convertedTemp;        //Holds converted temperature after calculations 

    //Asks user for starting temp Scale and ending temperature scale
        printf("Enter starting temperature scale (K/C/F)");
            scanf(" %c", &startTempScale);
    
        printf("Enter target temperature scale (K/C/F)");
            scanf(" %c", &targetTempScale);
    
    //Gets the original temperature from the user
        printf("Please enter a temperature: ");
            scanf("%lf", &originalTemp);
    
    //If else branches convert the start to the target Scale ***********************************
    if (startTempScale == 'F' && targetTempScale == 'C'){                                     //Converts Fahrenheit To Celsius
        convertedTemp = (originalTemp - 32) * (5.0 /9.0);
        printf(" %.2lf° degrees is equivalent to %.2lf° " , originalTemp, convertedTemp);
    }
    else if (startTempScale == 'C' && targetTempScale == 'F'){                                //Converts Celsius to Fahrenheit
        convertedTemp = (originalTemp * 1.8) + 32;
        printf(" %.2lf° degrees is equivalent to %.2lf° " , originalTemp, convertedTemp);
    }
    else if (startTempScale == 'C' && targetTempScale == 'K'){                               //Converts Celsius to Kelvin
        convertedTemp = originalTemp + 273.15;
       printf(" %.2lf° degrees is equivalent to %.2lf° " , originalTemp, convertedTemp);
    }
    else if (startTempScale == 'K' && targetTempScale == 'C'){                               //Converts Kelvin to Celsius
        convertedTemp = originalTemp - 273.15;  
        printf(" %.2lf° degrees is equivalent to %.2lf° " , originalTemp, convertedTemp);
    }
    else if (startTempScale == 'F' && targetTempScale == 'K'){                               //Converts Fahrenheit to Kelvin
        convertedTemp = (originalTemp - 32) * (5/9) + 273.15; 
        printf(" %.2lf° degrees is equivalent to %.2lf° " , originalTemp, convertedTemp);
    }
    else if (startTempScale == 'K' && targetTempScale == 'F'){                               //Converts Kelvin to Fahrenheit
        convertedTemp = (originalTemp - 273.15) * 1.8 + 32;
        printf(" %.2lf° degrees is equivalent to %.2lf° " , originalTemp, convertedTemp);
    }    
    else{                                                                                    //Input Validation
        printf("Please enter a valid choice and try again");
    }
}