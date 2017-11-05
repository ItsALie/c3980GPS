#include "dcgps.h"
#include "gpsprint.h"
#include <errno.h>
#include <string.h>

#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)

bool reading = TRUE;

/*
read loop function here
*/
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

/*
error checking function here
*/

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

/*void clearReadData(struct satellite_data* sat)
{
    memset(sat->timebuffer, 0, sizeof(timebuffer));
    memset(sat->elevation, 0, sizeof(elevation));
}*/
