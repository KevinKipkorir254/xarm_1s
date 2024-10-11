import evdev
import time

def find_gamepad():
    devices = [evdev.InputDevice(path) for path in evdev.list_devices()]
    for device in devices:
        if "SHANWAN Android Gamepad" in device.name:
            return device
    return None

gamepad_device = find_gamepad()

if gamepad_device is None:
    print("Gamepad not found. Make sure it's connected and you have the necessary permissions.")
    exit(1)

print(f"Monitoring: {gamepad_device.name} at {gamepad_device.path}")

event_count = 0
start_time = time.time()
last_event_time = start_time

try:
    for event in gamepad_device.read_loop():
        if event.type == evdev.ecodes.EV_KEY:  # Only count key events
            event_count += 1
            current_time = time.time()
            elapsed_time = current_time - last_event_time
            
            # Print event details and rate
            print(f"Event: {evdev.categorize(event)}, Total Events: {event_count}, Time since last event: {elapsed_time:.4f} seconds")
            last_event_time = current_time
            
except KeyboardInterrupt:
    print(f"\nTotal events: {event_count}")
    print(f"Total runtime: {time.time() - start_time:.2f} seconds")
except Exception as e:
    print(f"An error occurred: {e}")