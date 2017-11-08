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
char str[512];          //char buffer that holds validated fix data
char position[20];      //char buffer that holds converted lat/long data


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
        if(gps_waiting(gpsdata, 500000))
        {
            errno = 0;
            if(gps_read(gpsdata) == -1)
            {
                //errors
                fprintf(stderr, "agps: socket error 4 \n");
                //Cleanup(errno == 0 ? GPS_GONE : GPS_ERROR);
            }
            else
            {
                if(gpsdata->set)
                {
                    //check for errors first
                    //display, call print here
                    YourPrintDataFunction(gpsdata);
                }
            }
        }
        fprintf(stderr, "timeout\n");
        break;
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
-- PROGRAMMER: Haley Booker, Wilson Hu
--
-- INTERFACE: char* validateData(struct gps_data_t* gpsdata)
-- struct gps_data_t* gpsdata: the gps data
--
-- RETURNS: char* of the valid data to be printed
--
-- NOTES:
--  Validate the time, longitude and latitude. The function returns the string
-- to be printed.
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

    //Converts unix timestamp to ISO 8601 datetime and adds it to output string
    memset(timebuffer, 0, sizeof(timebuffer));
    fprintf(stderr, "%s", timebuffer);
    (void)unix_to_iso8601(gpsdata->fix.time, timebuffer, sizeof(timebuffer));
    strcpy(str, "Time: ");
    strcat(str, timebuffer);

    //Validates longitude, converts to deg/min/sec or "n/a" if invalid longitude
    strcat(str, "\nLongitude: ");
    if (isnan(gpsdata->fix.longitude) == 0)
    {
        snprintf(longBuff, sizeof(longBuff), "%s", convertLatLong(fabsf(gpsdata->fix.longitude)));
    }
    else
    {
        snprintf(longBuff, sizeof(longBuff), "n/a");
        longCharStr[0] = ' ';
    }
    strcat(str, longBuff);
    strcat(str, longCharStr);

    //Validates latitude, converts to deg/min/sec or "n/a" if invalid latitude
    strcat(str, "\nLatitude: ");
    if(isnan(gpsdata->fix.latitude) == 0)
    {
        snprintf(latBuff, sizeof(latBuff), "%s", convertLatLong(fabsf(gpsdata->fix.latitude)));
    }
    else
    {
        snprintf(latBuff, sizeof(latBuff), "n/a");
        latCharStr[0] = ' ';
    }
    strcat(str, latBuff);
    strcat(str, latCharStr);

    strcat(str, "\n");
    return &str[0];
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: convertLatLong
--
-- DATE: November 8, 2017
--
-- REVISIONS:
--
-- DESIGNER: Wilson Hu
--
-- PROGRAMMER: Haley Booker
--
-- INTERFACE: char * convertLatLong(float number)
-- float number: the decimal number to be converted
--
-- RETURNS: char* of the valid latitude or longitude to be printed
--
-- NOTES:
--  Takes a decimal latitude or longitude as a float and converts it. The
--  output string is the latitude or longitutde in degrees, minutes, and seconds.
--
----------------------------------------------------------------------------------------------------------------------*/

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
