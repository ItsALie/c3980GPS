/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: dcgps.c - An application that will scan an array
--                        array of satelites and print out
--                        information about visible satelites.
--
-- PROGRAM: dcgps
--
-- FUNCTIONS:
--      int main(void)
--
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
--      The program will use a GPS dongle to moniter an array of satelites. When a satelite becomes visible
--      the program will print out information about the gps fix and each satellite that it reads.
--
----------------------------------------------------------------------------------------------------------------------*/

#include <gps.h>
#include "gpsprint.h"
#include "gps-utils.h"
#include "dcgps.h"
#include <stdlib.h>
#include <pthread.h>


static struct fixsource_t source;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: main
--
-- DATE: November 8, 2017
--
-- REVISIONS:
--
-- DESIGNER: Wilson Hu
--
-- PROGRAMMER: Haley Booker
--
-- INTERFACE: int main(void)
--
-- RETURNS: void.
--
-- NOTES:
--      The start of the program. In main, structures memory are allocated and freed. The program
--      will try to connect to the GPS daemon. If the program can connect to the GPS hardware it
--      will start attempting to see satelites.
----------------------------------------------------------------------------------------------------------------------*/
int main(void)
{
    struct gps_data_t *gpsdata = malloc(sizeof(struct gps_data_t));

    //Establish connection to gpsd daemon
    if (gps_open(source.server, source.port, gpsdata) != 0)
    {
        fprintf(stderr, "Unable to open GPS\n");
        free(gpsdata);
        return -1;
    }

    //Set watch policy to read for JSON objects
    gps_stream(gpsdata, WATCH_ENABLE | WATCH_JSON, NULL);

    readGPS(gpsdata);

    gps_close(gpsdata);

    free(gpsdata);
    fprintf(stderr, "Exited program.\n");
    return 0;
}
