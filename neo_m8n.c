#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

#include "neo_m8n.h"

void neom8n_get_gps_status(const uart_port_t uart_num, int buffer_size, neom8n_gps_status_t *neom8n_gps_status) {

	int length = 0;
	char sentence[buffer_size];


	while (1) {

		uart_get_buffered_data_len(uart_num, (size_t*)&length);

		if (length > 6) {

			uart_read_bytes(uart_num, sentence, length, 100 / portTICK_PERIOD_MS);

			sentence[6] = '\0';

			if (strcmp(sentence, "$GNRMC") == 0) {

				char *latitude_temp = NULL;
				char *longtitude_temp = NULL;

				for (int i = 7,j = 0 ; j < 6 ; i ++) {

					if (sentence[i-1] == '\0'){

						if (j == 1) {

							if (sentence[i] == 'A') {
								neom8n_gps_status->is_active = true;
							}

							else {
								neom8n_gps_status->is_active = false;
								neom8n_gps_status->latitude = 0;
								neom8n_gps_status->is_north = true;
								neom8n_gps_status->longtitude = 0;
								neom8n_gps_status->is_east = true;
								break;
							}
						}


						if (j == 2) {
							latitude_temp = (sentence + i);
						}

						if (j == 3) {
							neom8n_gps_status->is_north = (sentence[i] == 'N');
						}

						if (j == 4) {
								longtitude_temp = (sentence + i);
						}

						if (j == 5) {
							neom8n_gps_status->is_east = (sentence[i] == 'E');
						}

					}

					if (sentence[i] == ',') {
						sentence[i] = '\0';
						j++;
					}
				}

				if (sentence[7] != '\0') {
					sentence[13] = '\0';
					strcpy(neom8n_gps_status->time,(sentence+7));
				}

				else {
					strcpy(neom8n_gps_status->time,"0");
				}


				if (neom8n_gps_status->is_active && latitude_temp != NULL && longtitude_temp != NULL) {

					neom8n_gps_status->latitude = strtof(latitude_temp, NULL) / 100;
					neom8n_gps_status->longtitude = strtof(longtitude_temp, NULL) / 100;

				}

				break;
			}
		}

		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}
