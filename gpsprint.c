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
-- PROGRAMMER: Wilson Hu
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
-- PROGRAMMER: Wilson Hu
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
    //char timebuffer[64];

    for (int i = 0; i < MAXCHANNELS; i++)
    {
        usedflags[i] = false;
        for(int j = 0; j < gpsdata->satellites_used; j++)
        {
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

        for (int i = 0; i < MAX_POSSIBLE_SATS; i++)
        {
            if (i < gpsdata->satellites_visible)
            {
                fprintf(stdout,
				   "SatNo: %d |  PRN: %3d\t Elevation: %02d\t Azimuth: %03d\t SS: %02ddB\t    Used: %c\n",
                   i,
                   gpsdata->PRN[i],
				   gpsdata->elevation[i],
                   gpsdata->azimuth[i],
				   (int)gpsdata->ss[i],
                    usedflags[i] ? 'Y' : 'N');
                fprintf(stdout, "-------------------------------------------------------------------------\n\n");
            }
        }
    }
}
