This is a very simple and probably very bugy implementation of 'ublox neo m8n' gps module on esp idf. Feel free to contribute and use on your own risk. You should create a neom8n_gps_status_t structure as defined in 'neo_m8n.h' and pass its reference to 'neom8n_get_gps_status(const uart_port_t uart_num, int buffer_size, neom8n_gps_status_t *neom8n_gps_status)'. It will return the current time in hhmmss, if the GPS is actively receiving data as boolean, latitude as float, if the coordinates are in north, longtitude in float, if the coordinates are in east.
