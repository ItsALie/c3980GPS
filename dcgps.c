#include <gps.h>
#include "gpsprint.h"
#include "gps-utils.h"
#include "dcgps.h"
#include <stdlib.h>


static struct fixsource_t source;

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


    //gps_stream(gpsdata, WATCH_DISABLE, NULL);
    //fprintf(stderr, "Exited after gps_stream()\n");

    readGPS(gpsdata);
    fprintf(stderr, "Exited after readGPS()\n");

    gps_close(gpsdata);
    fprintf(stderr, "Exited after gps_close()\n");

    free(gpsdata);
    fprintf(stderr, "Exited after free()\n");
    return 0;
}


bool validateSatellite(struct gps_data_t* gpsdata) {
    return false;
}
