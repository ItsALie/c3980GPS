#include "dcgps.h"
#include "gpsprint.h"
#include <string.h>
#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)


bool usedflags[MAXCHANNELS];

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
    char* timebuffer[64];
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
                memset(timebuffer, 0, sizeof(timebuffer));
                (void)unix_to_iso8601(gpsdata->fix.time, timebuffer, sizeof(timebuffer));
                fprintf(stdout,
				   " Time: %s    PRN: %3d\n  Elevation: %02d\n   Azimuth: %03d\n   SS: %02d\n    Longitude: %f %c    Latidtude: %f %c     Used: %c\n",
				   timebuffer,
                   gpsdata->PRN[i],
				   gpsdata->elevation[i],
                   gpsdata->azimuth[i],
				   (int)gpsdata->ss[i],
                   gpsdata->fix.longitude,
                   (gpsdata->fix.longitude < 0) ? 'W' : 'E' ,
                   gpsdata->fix.latitude,
                   (gpsdata->fix.latitude < 0) ? 'S' : 'N',
                    usedflags[i] ? 'Y' : 'N');
            }
        }
    }
}
