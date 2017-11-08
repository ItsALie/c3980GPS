/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: gps-utils.c - Reads and validates the gps data.
--
-- PROGRAM: dcgps
--
-- FUNCTIONS:
--      void readGPS(struct gps_data_t* gpsdata)
--      void validateData(struct gps_data_t* gpsdata)
--
-- DATE: November 8, 2017
--
-- REVISIONS: 
--
-- DESIGNER: Wilson Hu
--
-- PROGRAMMER: Haley Booker
--
-- NOTES:
--     If the program has read data it will call the print funtion.
--     The program performs error checking on
--     on the data and prints the information for visible satelites.
--
----------------------------------------------------------------------------------------------------------------------*/
#include "dcgps.h"
#include "gpsprint.h"
#include "gps-utils.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)

bool reading = TRUE;
//const char *str = (char *) malloc(sizeof(char) * 512);
char str[512];
char position[20];


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: readGPS
--
-- DATE: November 8, 2017
--
-- REVISIONS:
--
-- DESIGNER: Wilson Hu
--
-- PROGRAMMER: Haley Booker
--
-- INTERFACE: void readGPS(struct gps_data_t* gpsdata)
-- struct gps_data_t* gpsdata: the gps data
--
-- RETURNS: void.
--
-- NOTES:
--      This program will continuously check if there is input to be read. If
--      there is input it will try to read the data. If the data is read it will
--      be validated then printed.
--
----------------------------------------------------------------------------------------------------------------------*/
void readGPS(struct gps_data_t* gpsdata)
{
    while(reading)
    {
        fprintf(stderr, "STIL READING.\n");
        if(gps_waiting(gpsdata, 500000000))
        {
            //fprintf(stderr, "I made it past waiting!!!\n");
            errno = 0;
            if(gps_read(gpsdata) == -1)
            {
                //errors
                fprintf(stderr, "agps: socket error 4 \n");
                //Cleanup(errno == 0 ? GPS_GONE : GPS_ERROR);
            }
            else
            {
                //fprintf(stderr, "I read something\n");
                if(gpsdata->set)
                {
                    //check for errors first
                    //display, call print here
                    YourPrintDataFunction(gpsdata);
                }
            }
        }
    }
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: validateData
--
-- DATE: November 8, 2017
--
-- REVISIONS:
--
-- DESIGNER: Wilson Hu
--
-- PROGRAMMER: Haley Booker
--
-- INTERFACE: char* validateData(struct gps_data_t* gpsdata)
-- struct gps_data_t* gpsdata: the gps data
--
-- RETURNS: char* of the valid data to be printed
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/
char* validateData(struct gps_data_t* gpsdata)
{
    memset(str, 0, sizeof(str));
    char timebuffer[64];
    
    char longBuff[100];
    char longChar = ((gpsdata->fix.longitude < 0) ? 'W' : 'E');
    char longCharStr[2];
    longCharStr[0] = longChar;
    longCharStr[1] = '\0';
    
    char latBuff[100];
    char latChar = ((gpsdata->fix.latitude < 0) ? 'S' : 'N');
    char latCharStr[2];
    latCharStr[0] = latChar;
    latCharStr[1] = '\0';
    
    fprintf(stderr, "before time\n");
    memset(timebuffer, 0, sizeof(timebuffer));
    fprintf(stderr, "%s", timebuffer);
    (void)unix_to_iso8601(gpsdata->fix.time, timebuffer, sizeof(timebuffer));
    strcpy(str, "Time: ");
    strcat(str, timebuffer);
    
    strcat(str, "\nLongitude: ");
    if (isnan(gpsdata->fix.longitude) == 0)
        snprintf(longBuff, sizeof(longBuff), "%s", convertLatLong(fabsf(gpsdata->fix.longitude)));
        
    else
        snprintf(longBuff, sizeof(longBuff), "n/a");
    strcat(str, longBuff);
    strcat(str, longCharStr);
    
    strcat(str, "\nLatitude: ");
    if(isnan(gpsdata->fix.latitude) == 0)
        snprintf(latBuff, sizeof(latBuff), "%s", convertLatLong(fabsf(gpsdata->fix.latitude)));
    else
        snprintf(latBuff, sizeof(latBuff), "n/a");
    strcat(str, latBuff);
    strcat(str, latCharStr);
    
    strcat(str, "\n");
    return &str[0];
}

char * convertLatLong(float number)
{
    int degrees;
    int minutes;
    int seconds;
    
    degrees = (int) number;
    minutes = (int)(60 * (number - degrees));
    seconds = (int)(3600 * (number - degrees) - (60 * minutes));
    
    sprintf(position, "%d° %d'%d\" ", degrees, minutes, seconds);
    return &position[0];
}