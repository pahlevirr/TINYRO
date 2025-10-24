#include "system.h"
#include "io.h"
#include <alt_types.h>
#include "sys/alt_stdio.h"
#include "sys/alt_timestamp.h"


#define RESPONSE_BITS 16  // Collect 16 responses per challenge (128-bit response)
#define SAMPLE_SIZE 10  // Collect 10 samples per challenge
#define CHALLENGE_COUNT 10 // Total challenges to be sent

void update_challenge(alt_u8 *c0) {
    *c0 = *c0 + 0x01; // Spread first response over 32 bits
}

int main() {
    alt_u8 challenge_part0 = 0x00; // Initial seed

    alt_u8 response_buffer[RESPONSE_BITS];

    for (int challenge_count = 0; challenge_count < CHALLENGE_COUNT; challenge_count++) {
    	alt_printf("CHALLENGE: %x\n", challenge_part0);
        for (int sample_count = 0; sample_count < SAMPLE_SIZE; sample_count++) {
            int valid_responses = 0;
            while (valid_responses < RESPONSE_BITS) { // Ensure we collect 16 responses
                // Send Challenge
            	//alt_printf("Sending a Request to Active\n");
            	IOWR(REQUEST_BASE, 0, 0x1);

            	IOWR(ENA_BASE, 0, 0x0);

            	//alt_printf("Waiting\n");
				while (IORD (BUSY_BASE, 0) != 0);

				//alt_printf("Sending a Challenge\n");
				IOWR_8DIRECT(STREAM_0_BASE, 0, challenge_part0);

				//alt_printf("Waiting\n");
				while (IORD (BUSY_BASE, 0) != 0);

				//alt_printf("Sending a Enabler\n");
				IOWR(ENA_BASE, 0, 0x1);

				//alt_printf("Waiting\n");
				while (IORD (BUSY_BASE, 0) != 0);

				// Get Response
				//alt_printf("Get Response\n");
				alt_u8 response = IORD_8DIRECT(RESPONSE_BASE, 0);
				//alt_printf("%x", response);

				//alt_printf("Sending a Request to De-active\n");
            	IOWR(REQUEST_BASE, 0, 0x0);
            	IOWR(ENA_BASE, 0, 0x0);
                // Polling mechanism with timeout
                while (IORD (BUSY_BASE, 0) != 0);

                response_buffer[valid_responses++] = response;
                // Acknowledge reception
            }
            // Print the response

			for (int i = 0; i < RESPONSE_BITS; i++) {
				alt_printf("%x", response_buffer[i]);
			}
			alt_printf("\n");
        }



        alt_printf("OL");
        alt_printf("\n");

        update_challenge(&challenge_part0);
    }

    return 0;
}
