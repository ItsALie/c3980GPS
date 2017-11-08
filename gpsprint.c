/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: gpsprint.c - The display portion of the application.
--
-- PROGRAM: dcgps
--
-- FUNCTIONS:
--      void YourPrintDataFunction(struct gps_data_t* gpsdata)
--
--
-- DATE: November 8, 2017
--
-- REVISIONS: 
--
-- DESIGNER: Wilson Hu
--
-- PROGRAMMER: Haley Booker, Wilson Hu
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
#include <string.h>
#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)


bool usedflags[MAXCHANNELS];

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: YourPrintDataFunction
--
-- DATE: November 8, 2017
--
-- REVISIONS:
--
-- DESIGNER: Wilson Hu
--
-- PROGRAMMER: Haley Booker, Wilson Hu
--
-- INTERFACE: void YourPrintDataFunction(struct gps_data_t* gpsdata)
-- struct gps_data_t* gpsdata: the gps data
--
-- RETURNS: void.
--
-- NOTES:
-- This function prints information about satelites including Timestamp (UTC),
-- Lat/Long, PRN, elevation, azimuth, SNR, and a  Used flag (y/n). 
----------------------------------------------------------------------------------------------------------------------*/
void YourPrintDataFunction(struct gps_data_t* gpsdata)
{
    char timebuffer[64];

    for (size_t i = 0; i < MAXCHANNELS; i++)
    {
        //fprintf(stderr, "Inside first for loop\n");
        usedflags[i] = false;
        for(size_t j = 0; j < gpsdata->satellites_used; j++)
        {
            //fprintf(stderr, "Inside the inside loop\n");
            if (gpsdata->used[j] == gpsdata->PRN[i])
            {
                usedflags[i] = true;
            }
        }
    }

    if (gpsdata->satellites_visible != 0)
    {
        char *validGPSData = validateData(gpsdata);
        fprintf(stdout, "%s", validGPSData);
        // memset(timebuffer, 0, sizeof(timebuffer));
        // fprintf(stderr, "%s", timebuffer);
        // (void)unix_to_iso8601(gpsdata->fix.time, timebuffer, sizeof(timebuffer));
        // fprintf(stdout, "Time: %s\n
                         // Longitude: %f %c\n
                         // Latitude: %f %c\n",
                         // timebuffer, gpsdata->fix.longitude, (gpsdata->fix.longitude < 0) ? 'W' : 'E',
                         // gpsdata->fix.latitude, (gpsdata->fix.latitude < 0) ? 'S' : 'N');
        for (size_t i = 0; i < MAX_POSSIBLE_SATS; i++)
        {
            if (i < gpsdata->satellites_visible)
            {
                fprintf(stdout,
				   "SatNo: %n\n PRN: %3d\n Elevation: %02d\n Azimuth: %03d\n SS: %02ddB\n    Used: %c\n",
                   i,
                   gpsdata->PRN[i],
				   gpsdata->elevation[i],
                   gpsdata->azimuth[i],
				   (int)gpsdata->ss[i],
                    usedflags[i] ? 'Y' : 'N');
                fprintf(stdout, "------------------------------------\n\n");
            }
        }
    }
}
