#include "dcgps.h"
#include "gpsprint.h"
#include <string.h>
#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)



bool usedflags[MAXCHANNELS];
char databuffer[256];


/*
print function here
prints:
    Timestamp (UTC)
    Lat/Long
    PRN
    elevation
    azimuth
    SNR
    Used flag (y/n)
*/
void YourPrintDataFunction(struct gps_data_t* gpsdata)
{
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
        fprintf(stderr, "I found a satellite!");
        for (size_t i = 0; i < MAX_POSSIBLE_SATS; i++)
        {
            if (i < gpsdata->satellites_visible)
            {
                //print things here
                //strcat onto buffer
                //timestamp
                fprintf(stdout,
				   " PRN: %3d\n  Elevation: %02d\n   Azimuth: %03d\n   SS: %02d\n     Used: %c\n",
				   gpsdata->PRN[i],
				   gpsdata->elevation[i], gpsdata->azimuth[i],
				   (int)gpsdata->ss[i],
				   usedflags[i] ? 'Y' : 'N');
                //strcat(databuffer, "Hello World\n");
                //fprintf(stdout, databuffer);
                //latitude
                /*strcat(databuffer, deg_to_str(deg_type
                    , fabs(gpsdata->fix.latitude))
                    , (gpsdata->fix.latitude<0) ? "S\n":"N\n");*/
            }
        }
    }
}
