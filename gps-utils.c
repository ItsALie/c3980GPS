#include "dcgps.h"
<<<<<<< HEAD
#include "gpsprint.h"
#include <errno.h>

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
                    //fprintf(stderr, "something was set, a mask or something\n");
                    //check for errors first
                    //display, call print here
                    YourPrintDataFunction(gpsdata);
                }
            }
        }
    }
}
=======

/*
read loop function here
*/
>>>>>>> 2e67e37290d3864d31a60e578e72af166343cb14

/*
error checking function here
*/
<<<<<<< HEAD
bool validateData(struct gps_data_t* gpsdata)
{
    return false;
}
=======
>>>>>>> 2e67e37290d3864d31a60e578e72af166343cb14
