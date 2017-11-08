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
#include <errno.h>
#include <string.h>

#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)

bool reading = TRUE;

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
-- INTERFACE: void validateData(struct gps_data_t* gpsdata)
-- struct gps_data_t* gpsdata: the gps data
--
-- RETURNS: void.
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/
void validateData(struct gps_data_t* gpsdata)
{
    /*struct read_data read;

    for (size_t i = 0; i < MAXCHANNELS; i++)
    {
        usedflags[i] = false;
        for (size_t j = 0; j < gps_data->satellites_used; j++)
        {
            if (gpsdata->used[j] == gpsdata->PRN[i])
            {
                usedflags[i] = true;
            }
        }
    }

    if (gpsdata->satellites_visible != 0)
    {

    }*/
}
