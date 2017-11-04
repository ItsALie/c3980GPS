#include "dcgps.h"
#include "gpsprint.h"
#include <string.h>
#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)
static enum deg_str_type deg_type = deg_dd;


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
                fprintf(stdout,
				   " Time: %f    PRN: %3d\n  Elevation: %02d\n   Azimuth: %03d\n   SS: %02d\n    Longitude: %s %c    Latidtude: %s %c     Used: %c\n",
				   gpsdata->fix.time,
                   gpsdata->PRN[i],
				   gpsdata->elevation[i],
                   gpsdata->azimuth[i],
				   (int)gpsdata->ss[i],
                     deg_to_str(deg_type, fabs(gpsdata->fix.longitude)),
                    (gpsdata->fix.longitude < 0) ? 'W' : 'E' ,
                    deg_to_str(deg_type, fabs(gpsdata->fix.latitude)),
                    (gpsdata->fix.latitude < 0) ? 'S' : 'N',
                    usedflags[i] ? 'Y' : 'N');
            }
        }
    }
}
