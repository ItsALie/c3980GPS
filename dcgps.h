#include <gps.h>

#define TRUE 1
#define FALSE 0

struct fixsource_t
{
    char *spec;
    char *server;
    char *port;
    char *device;
};

bool validateSatellite(struct gps_data_t* gpsdata);
