# RUNNING THIS PROJECT

1. Go to 
```bash
xarm_1s
```

2. Run command
```bash
source install/setup.bash
```

3. Run command
```bash
ros2 launch xarm_1s_description xarm_1s_ros2_control.launch.py
```

4. Run command
```bash
ros2 run xarm_1s_kinematics geometry_publisher
```

5. Run command
```bash
xarm_1s_kinematics kinematics_solver
```

NB add a since launch file for the 2.

6. Run command
```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```