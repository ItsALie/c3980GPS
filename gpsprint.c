<<<<<<< HEAD
#include "dcgps.h"
#include "gpsprint.h"
#include <string.h>
#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)



bool usedflags[MAXCHANNELS];
char databuffer[256];

=======
>>>>>>> 2e67e37290d3864d31a60e578e72af166343cb14

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
<<<<<<< HEAD
    for (size_t i = 0; i < MAXCHANNELS; i++)
    {
        //fprintf(stderr, "Inside first for loop\n");
        usedflags[i] = false;
        for(size_t j = 0; j < gpsdata->satellites_used; j++)
        {
            fprintf(stderr, "Inside the inside loop\n");
            if (gpsdata->skyview[j].used == gpsdata->skyview[i].PRN)
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
                //strcat(databuffer, unix_to_iso8601(
                //    gpsdata->skyview_time, databuffer, 20));
                strcat(databuffer, "Hello World\n");
                fprintf(stdout, databuffer);
                //latitude
                /*strcat(databuffer, deg_to_str(deg_type
                    , fabs(gpsdata->fix.latitude))
                    , (gpsdata->fix.latitude<0) ? "S\n":"N\n");*/
            }
        }
    }

=======
>>>>>>> 2e67e37290d3864d31a60e578e72af166343cb14

}
