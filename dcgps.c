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
--      the program will print out information about the program.
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
    fprintf(stdout, "Starting Program!");
    struct gps_data_t *gpsdata = malloc(sizeof(struct gps_data_t));
    if (gps_open(source.server, source.port, gpsdata) == -1)
    {
        fprintf(stderr, "Exited at gps_open()\n");
        //errors
        //fprintf(stderr, "%s\n", gps_errstr(err));
    }

    gps_stream(gpsdata, WATCH_ENABLE | WATCH_JSON, NULL);
    fprintf(stderr, "Exited after gps_stream()\n");

    readGPS(gpsdata);
    fprintf(stderr, "Exited after readGPS()\n");

    gps_close(gpsdata);
    fprintf(stderr, "Exited after gps_close()\n");

    free(gpsdata);
    fprintf(stderr, "Exited after free()\n");
    return 0;
}
