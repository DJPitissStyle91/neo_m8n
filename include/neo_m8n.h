#ifndef NEO_M8N_H
#define NEO_M8N_H

typedef struct {

	char time[7];
	bool is_active;
	float latitude;
	bool is_north;
	float longtitude;
	bool is_east;

} neom8n_gps_status_t;

void neom8n_get_gps_status(const uart_port_t uart_num, int buffer_size, neom8n_gps_status_t *neom8n_gps_status);

#endif
