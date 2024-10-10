#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <unistd.h>
#include <hidapi/hidapi.h>
#include <time.h>

#define MAX_STR 255
#define REPORT_SIZE 65
#define SIGNATURE 0x55
#define CMD_GET_SERVO_POSITION 0x15

// Function to get current time in milliseconds
long long current_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

int main(int argc, char* argv[])
{
    int res;
    unsigned char buf[REPORT_SIZE];
    hid_device *handle;
    wchar_t wstr[MAX_STR];

    // Initialize the hidapi library
    res = hid_init();
    printf("hid_init result: %d\n", res);

    // Open the device using the VID, PID
    handle = hid_open(0x0483, 0x5750, NULL);
    if (!handle) {
        printf("Unable to open device\n");
        return 1;
    }

    // Read the Manufacturer String
    res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
    printf("Manufacturer String: %ls\n", wstr);

    // Read the Product String
    res = hid_get_product_string(handle, wstr, MAX_STR);
    printf("Product String: %ls\n", wstr);

    // Read the Serial Number String
    res = hid_get_serial_number_string(handle, wstr, MAX_STR);
    printf("Serial Number String: %ls\n", wstr);

    const int iterations = 10000;
    const long long interval_ms = 10; // 10ms for 100Hz

    for (int i = 0; i < iterations; ++i) {
        long long start_time = current_time_ms();

        printf("Iteration %3d - Positions: ", i + 1);

        for (int servo = 1; servo <= 6; ++servo) {
            // Set up the command
            memset(buf, 0, sizeof(buf));
            buf[0] = 0x00;  // Report ID
            buf[1] = SIGNATURE;
            buf[2] = SIGNATURE;
            buf[3] = 0x04;  // data size
            buf[4] = CMD_GET_SERVO_POSITION;
            buf[5] = 0x01;  // Number of servos
            buf[6] = servo; // Servo ID

            // Send the command
            res = hid_write(handle, buf, sizeof(buf));
            if (res < 0) {
                printf("Error writing to device.\n");
                hid_close(handle);
                hid_exit();
                return 1;
            }

            // Read the response
            res = hid_read_timeout(handle, buf, sizeof(buf), 100);
            if (res > 0) {
                if (res >= 10 && buf[1] == SIGNATURE && buf[3] == CMD_GET_SERVO_POSITION) {
                    //int position1 = (buf[8] << 8) | buf[9];
                    //int position2 = (buf[6] << 8) | buf[7];
                    int position3 = (buf[7] << 8) | buf[6];
                    //int position4 = (buf[4] << 8) | buf[5];
                    //printf("1: %5d ", position1);
                    //printf("2: %5d ", position2);
                    printf("%5d ", position3);
                    // Debug output
                    printf("(Raw: %02x %02x) ", buf[5], buf[6]);
                } else {
                    printf("ERROR ");
                }
            } else if (res == 0) {
                printf("TIMEOUT ");
            } else {
                printf("ERROR ");
            }
        }
        printf("\n");

        long long end_time = current_time_ms();
        long long duration = end_time - start_time;

        if (duration < interval_ms) {
            usleep((interval_ms - duration) * 1000);
        }
    }

    // Close the device
    hid_close(handle);

    // Finalize the hidapi library
    res = hid_exit();

    printf("Press Enter to exit...");
    getchar();

    return 0;
}