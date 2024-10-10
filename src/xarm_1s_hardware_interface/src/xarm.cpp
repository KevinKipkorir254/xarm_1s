#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>
#include <stdexcept>
#include <vector>
#include "xarm_1s_hardware_interface/xarm.hpp"
#include "rclcpp/rclcpp.hpp"

#ifdef _WIN32
#include <Windows.h>
#else
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#endif

void sleep_ms(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

//#include <hidapi/hidapi.h>

Controller::Controller() : device(nullptr) {
        int res = hid_init();
        unsigned char buf[65];
        wchar_t wstr[255];
        //hid_device *device;
        RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "hid_init result: %d\n", res);
        device = hid_open(0x0483, 0x5750, NULL);
        if (!device) {
            throw std::runtime_error("Failed to open XArm device");
        }
        
    // Read the Manufacturer String
    res = hid_get_manufacturer_string(device, wstr, 255);
    //printf("Manufacturer String: %ls\n", wstr);
    RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "Manufacturer String: %ls\n", wstr);

    // Read the Product String
    res = hid_get_product_string(device, wstr, 255);
    //printf("Product String: %ls\n", wstr);
    RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "Product String: %ls\n", wstr);

    // Read the Serial Number String
    res = hid_get_serial_number_string(device, wstr, 255);
    //printf("Serial Number String: %ls\n", wstr);
    RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "Serial Number String: %ls\n", wstr);

    // Set up the command
    memset(buf, 0, sizeof(buf));
    buf[0] = 0x00;  // Report ID
    buf[1] = SIGNATURE;  // Signature
    buf[2] = SIGNATURE;  // Signature
    buf[3] = 0x03;  // data size
    buf[4] = CMD_GET_SERVO_POSITION;  // Command
    buf[5] = 0x01;  // Number of servos
    buf[6] = 0x01;  // Servo ID (adjust if needed)

    // Send the command
    res = hid_write(device, buf, sizeof(buf));
    //printf("hid_write result: %d\n", res);
    RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "hid_write result: %d\n", res);
    // Print the sent command
    //printf("Sent command: ");

    for (int i = 0; i < 5; i++) {  // Print first 5 bytes
        //printf("%02x ", buf[i]);
        RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "Sent command byte: %02x", buf[i]);
    }
    //printf("\n");
    RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "Sent command");

    // Read the response
    res = hid_read_timeout(device, buf, sizeof(buf), 1000);
    //printf("hid_read_timeout result: %d\n", res);
    RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "hid_read_timeout result: %d\n", res);

    if (res > 0) {
        //printf("Received data: ");
        RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "Received data");
        for (int i = 0; i < res; i++) {
            //printf("%02x ", buf[i]);
            RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "Received data byte: %02x", buf[i]);
        }
        //printf("\n")
        RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "Received data");

        // Parse the response (adjust based on the expected response format)
        if (res >= 5 && buf[1] == SIGNATURE && buf[2] == CMD_GET_SERVO_POSITION) {
            int position = (buf[4] << 8) | buf[3];
            //printf("Servo position: %d\n", position);
            RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "Servo position: %d\n", position);
        } else {
            //printf("Unexpected response format\n");
            RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "Unexpected response format");
        }
    } else if (res == 0) {
        printf("No data received within timeout.\n");
    } else {
        //printf("Error reading data.\n");
        RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "Error reading data.");
    }

    RCLCPP_INFO(rclcpp::get_logger("hardware_interface_node"), "Device opened successfully");
}

Controller::~Controller() {
        if (device) {
            hid_close(device);
        }
        hid_exit();
}

void Controller::setPosition(int servo, int position, int duration, bool wait) {
    std::vector<uint8_t> data = {1, static_cast<uint8_t>(duration & 0xff), static_cast<uint8_t>((duration & 0xff00) >> 8)};
    
    if (position < 0 || position > 1000) {
        throw std::invalid_argument("Parameter 'position' must be between 0 and 1000.");
    }
    
    data.push_back(static_cast<uint8_t>(servo));
    data.push_back(static_cast<uint8_t>(position & 0xff));
    data.push_back(static_cast<uint8_t>((position & 0xff00) >> 8));
    
    send(CMD_SERVO_MOVE, data);
    
    if (wait) {
        sleep_ms(duration);
    }
}

void Controller::setPosition(const Servo& servo, int duration, bool wait) {
    setPosition(servo.servo_id, servo.position, duration, wait);
}

void Controller::setPosition(const std::vector<std::pair<int, int>>& servos, int duration, bool wait) {
    std::vector<uint8_t> data = {static_cast<uint8_t>(servos.size()), static_cast<uint8_t>(duration & 0xff), static_cast<uint8_t>((duration & 0xff00) >> 8)};
    
    for (const auto& servo : servos) {
        if (servo.second < 0 || servo.second > 1000) {
            throw std::invalid_argument("Parameter 'position' must be between 0 and 1000.");
        }
        data.push_back(static_cast<uint8_t>(servo.first));
        data.push_back(static_cast<uint8_t>(servo.second & 0xff));
        data.push_back(static_cast<uint8_t>((servo.second & 0xff00) >> 8));
    }
    
    send(CMD_SERVO_MOVE, data);
    
    if (wait) {
        sleep_ms(duration);
    }
}

int Controller::getPosition(int servo, bool degrees) {
        std::vector<uint8_t> data = {1, static_cast<uint8_t>(servo)};
        send(CMD_GET_SERVO_POSITION, data);
        
        auto recv_data = recv(CMD_GET_SERVO_POSITION);
        if (recv_data.size() >= 4) {
            int position = (recv_data[3] << 8) | recv_data[2];
            return degrees ? Util::positionToAngle(position) : position;
        } else {
            std::stringstream ss;
            ss << "Function 'getPosition' recv error. Received data size: " << recv_data.size();
            if (!recv_data.empty()) {
                ss << " Data: ";
                for (auto byte : recv_data) {
                    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
                }
            }
            throw std::runtime_error(ss.str());
        }
}

int Controller::getPosition(const Servo& servo, bool degrees) {
        return getPosition(servo.servo_id, degrees);
}

void Controller::getPosition(std::vector<Servo>& servos, bool degrees) {
        std::vector<uint8_t> data = {static_cast<uint8_t>(servos.size())};
        for (const auto& servo : servos) {
            data.push_back(servo.servo_id);
        }
            
            RCLCPP_ERROR(rclcpp::get_logger("XArmHardwareInterface"), "Data pushed back");
        send(CMD_GET_SERVO_POSITION, data);
            RCLCPP_ERROR(rclcpp::get_logger("XArmHardwareInterface"), "Datasent");
        
        auto recv_data = recv(CMD_GET_SERVO_POSITION);
            RCLCPP_ERROR(rclcpp::get_logger("XArmHardwareInterface"), "Data received");
        if (!recv_data.empty()) {
            for (size_t i = 0; i < recv_data[0]; ++i) {
                int position = (recv_data[i*3+3] << 8) | recv_data[i*3+2];
                servos[i].position = degrees ? Util::positionToAngle(position) : position;
            }
        } else {
            throw std::runtime_error("Function 'getPosition' recv error.");
    }
}

void Controller::servoOff(int servo) {
    send(CMD_SERVO_STOP, {1, static_cast<uint8_t>(servo)});
}

void Controller::servoOff(const Servo& servo) {
    servoOff(servo.servo_id);
}

void Controller::servoOff(const std::vector<int>& servos) {
    std::vector<uint8_t> data = {static_cast<uint8_t>(servos.size())};
    for (int servo : servos) {
        data.push_back(static_cast<uint8_t>(servo));
    }
    send(CMD_SERVO_STOP, data);
}

void Controller::servoOff() {
    send(CMD_SERVO_STOP, {6, 1, 2, 3, 4, 5, 6});
}

float Controller::getBatteryVoltage() {
    send(CMD_GET_BATTERY_VOLTAGE);
    auto data = recv(CMD_GET_BATTERY_VOLTAGE);
    if (!data.empty()) {
        return ((data[1] << 8) | data[0]) / 1000.0f;
    }
    return 0.0f;
}

bool Controller::send(uint8_t cmd, const std::vector<uint8_t>& data) {
        std::vector<uint8_t> buffer(65, 0);  // HID reports are 65 bytes, first byte is report number
        buffer[0] = 0x00;  // Report ID
        buffer[1] = SIGNATURE;  // First signature byte
        buffer[2] = SIGNATURE;  // Second signature byte
        buffer[3] = static_cast<uint8_t>(data.size() + 2);  // Data size (including command byte)
        buffer[4] = cmd;  // Command
        std::copy(data.begin(), data.end(), buffer.begin() + 2);

RCLCPP_INFO(rclcpp::get_logger("XArmHardwareInterface"), "Data initialized and copied ready to send");

RCLCPP_INFO(rclcpp::get_logger("XArmHardwareInterface"), "Attempting to write %zu bytes", buffer.size());

// Print the data being sent
std::stringstream ss;
for (size_t i = 0; i < buffer.size(); ++i) {
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]) << " ";
}
//RCLCPP_INFO(rclcpp::get_logger("XArmHardwareInterface"), "Data: %s", ss.str().c_str());

int res = hid_write(device, buffer.data(), buffer.size());

RCLCPP_INFO(rclcpp::get_logger("XArmHardwareInterface"), "hid_write returned: %d", res);

if (res < 0) {
    const wchar_t* error_message = hid_error(device);
    if (error_message) {
        char error_message_narrow[256];
        wcstombs(error_message_narrow, error_message, sizeof(error_message_narrow));
        RCLCPP_ERROR(rclcpp::get_logger("XArmHardwareInterface"), "Failed to send data: %s", error_message_narrow);
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("XArmHardwareInterface"), "Failed to send data: Unknown error");
    }
    return false;
}

RCLCPP_INFO(rclcpp::get_logger("XArmHardwareInterface"), "Data sent successfully");
        return true;
}

std::vector<uint8_t> Controller::recv(uint8_t cmd) {
        std::vector<uint8_t> buffer(65);
        RCLCPP_INFO(rclcpp::get_logger("XArmHardwareInterface"), "Before hid_read_timeout");
        int res = hid_read_timeout(device, buffer.data(), buffer.size(), 1000);
        RCLCPP_INFO(rclcpp::get_logger("XArmHardwareInterface"), "after hid_read_timeout");
        if (res < 0) {
            throw std::runtime_error("Error reading from device");
        } else if (res == 0) {
            throw std::runtime_error("Timeout reading from device");
        }
        return std::vector<uint8_t>(buffer.begin(), buffer.begin() + res);
}

void Controller::usbEventHandler(const std::vector<uint8_t>& data, int event_type) {
    input_report = data;
    usb_recv_event = true;
    if (debug) {
        std::cout << "USB Recv Data: ";
        for (uint8_t byte : data) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
        }
        std::cout << std::dec << std::endl;
    }
}