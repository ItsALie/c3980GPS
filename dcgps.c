#include <gps.h>
#include "gpsprint.h"
#include "gps-utils.h"
#define TRUE 1
#define FALSE 0




bool reading = TRUE;

int main(void)
{
    struct gps_data_t gpsdata = malloc(sizeof(struct gps_data_t);

    if (gps_open(server, DEFAULT_GPSD_PORT, &gpsdata) == -1)
    {
        //errors
        fprintf(stderr, "%s\n", gps_errstr(err));
    }
    gps_stream(&gpsdata, WATCH_ENABLE | WATCH_JSON, NULL);

    while(reading)
    {
        if(gps_waiting(&gpsdata, 500))
        {
            errno = 0;
            if(gps_read(&gps_data) == -1)
            {
                //errors
                fprintf(stderr, "agps: socket error 4 \n");
                Cleanup(errno == 0 ? GPS_GONE : GPS_ERROR);
            }
            else
            {
                if(gps_data.set)
                {
                    //display
                }
            }
        }
    }
    gps_stream(&gps_data, WATCH_DISABLE, NULL);
    gps_close(&gps_data);
    free(gps_data);

}
