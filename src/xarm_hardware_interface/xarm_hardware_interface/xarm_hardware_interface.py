import sys
import xarm
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from sensor_msgs.msg import JointState
import math

try:
    arm = xarm.Controller("USB", debug=True)
except OSError as e:
    print("Failed to connect to Robot", e)
    sys.exit(1)


servos = {
    "shoulder_pan": xarm.Servo(6, 0.0),
    "shoulder_lift": xarm.Servo(5, 0.0),
    "elbow": xarm.Servo(4, 0.0),
    "wrist_flex": xarm.Servo(3, 0.0),
    "wrist_roll": xarm.Servo(2, 0.0),
    "grip_right": xarm.Servo(1, -90.25),  # Flipped in URDF (open is close)
}



class XarmHardwareInterface(Node):
    def __init__(self):
        super().__init__("xarm_hardware_node")
        self.joints_sub = self.create_subscription(JointState, '/joint_states', self.message_handler, 10)
        

    def message_handler(self, msg):
        changed = False

        
        for name, position in zip(msg.name, msg.position):
            servo = servos.get(name, None)
            if not servo:
                continue

            value = self.interpreter(position)
            # self.get_logger().info(f'{value}')

            if servo.angle != value:
                servo.angle = value
                changed = True

        if changed:
            arm.setPosition(list(servos.values()), duration = 2)
            self.get_logger().info(f'{servos.values()}')
        # self.get_logger().info(f'{msg}')


    def interpreter(self, position):
        position = math.degrees(position) 
        position = round(position*4)
        position = position/4
        self.get_logger().info(f'{position}')
        return position
        # self.get_logger().info(f'{position}')

def main(args=None):
    rclpy.init()
    xarm_hardware_node = XarmHardwareInterface()
    
    rclpy.spin(xarm_hardware_node)
    xarm_hardware_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()