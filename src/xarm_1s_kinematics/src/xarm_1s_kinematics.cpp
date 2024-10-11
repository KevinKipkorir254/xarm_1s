#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <kdl_parser/kdl_parser.hpp>
#include "std_msgs/msg/string.hpp"
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <urdf_parser/urdf_parser.h>
#include <kdl/frames_io.hpp>
#include <kdl/kinfam_io.hpp>
#include <geometry_msgs/msg/point.h>

#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/chainidsolver_recursive_newton_euler.hpp>
#include <kdl/chainiksolverpos_lma.hpp>
// C++program to demonstrate cout
#include <iostream>
#include <typeinfo>

using std::placeholders::_1;


class XArm1SKinematics : public rclcpp::Node
{
public:
    XArm1SKinematics()
    : Node("xarm_1s_kinematics"), count_(0)
    {
        RCLCPP_INFO(this->get_logger(), "Initializing XArm1SKinematics");
        this->build_tree();
        publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/robotic_arm_joint_trajectory_controller/commands", 10);
        subscription_ = this->create_subscription<geometry_msgs::msg::Point>("/current_positions", 10, std::bind(&XArm1SKinematics::compute_ik_and_publish, this, _1));

    }
private:
    void build_tree()
    {
        // Specify the name of the ROS package you want to find
        std::string package_name = "xarm_1s_description";

        // Use rospkg's getPrefix() function to get the package path
        std::string package_path = ament_index_cpp::get_package_share_directory(package_name);
        package_path.append("/urdf/xarm_1s.urdf");

        //print the file path
        RCLCPP_INFO(this->get_logger(), "Package path: %s", package_path.c_str());

        //use the code for the path
        using namespace std::chrono_literals;
        KDL::Tree my_tree;
        urdf::ModelInterfaceSharedPtr my_urdf_model = urdf::parseURDFFile(package_path);

        //Add comment to each of the following lines
        //Check if the URDF model is valid
        if(my_urdf_model)
        {
                //Print the number of joints and links in the URDF model
                std::cout << "Number of joints: "<< my_urdf_model->joints_.size() <<std::endl;
                std::cout << "Number of links: " << my_urdf_model->links_.size() <<std::endl; 
        }

        //Create a URDF model from the URDF model pointer
        urdf::ModelInterface model = *my_urdf_model;

        //Create a tree from the URDF model
        RCLCPP_INFO(this->get_logger(), "Start creating tree");
        if ( !kdl_parser::treeFromUrdfModel( model, my_tree))
        {
          RCLCPP_INFO(this->get_logger(), "failed to parse urdf robot model");
        }
        else
        {
          RCLCPP_INFO(this->get_logger(), "Tree created succesfully");
        }

        //Get the chain from the tree
        if (!my_tree.getChain("base_link", "finger_right_link", kdl_chain))
        {
            RCLCPP_INFO(this->get_logger(), "Failed to get a chain");
        }
        else 
        {
            RCLCPP_INFO(this->get_logger(), "Now we have a chain");
        }

        //Print the number of joints and segments in the chain
        RCLCPP_INFO(this->get_logger(), "Number of joints: %d", kdl_chain.getNrOfJoints());
        RCLCPP_INFO(this->get_logger(), "Number of segments: %d", kdl_chain.getNrOfSegments());

        //Initialize the joint arrays
        KDL::JntArray q(kdl_chain.getNrOfJoints());
        KDL::JntArray qdot(kdl_chain.getNrOfJoints());
        KDL::JntArray qdotdot(kdl_chain.getNrOfJoints());
        KDL::JntArray tau(kdl_chain.getNrOfJoints());
        KDL::Wrenches f(kdl_chain.getNrOfSegments());

        KDL::ChainFkSolverPos_recursive fksolver(kdl_chain);
        KDL::Frame T;

         //what does this do?
         //This calculates the forward kinematics for the given joint array q and stores the result in T
        fksolver.JntToCart(q, T);

        std::cout << "q init:" << q <<std::endl;
        std::cout << "Pose: "<< T <<std::endl;


        KDL::ChainIkSolverPos_LMA solver(kdl_chain);

        //Get the number of joints in the chain
	    int n = kdl_chain.getNrOfJoints();
        //Initialize the joint arrays
        KDL::JntArray q_(n);
        KDL::JntArray q_init(n);
        KDL::JntArray q_sol(n);


        //Set the joint array to a random value
        q_.data.setRandom();
        //Calculate the forward kinematics
        fksolver.JntToCart(q_, pos_goal);

        //Print the joint array
        std::cout << "q:" << q_<<std::endl;
        std::cout << "Pose: "<< pos_goal <<std::endl;

    }

    void compute_ik_and_publish(const geometry_msgs::msg::Point &point)
    {
	    int n = kdl_chain.getNrOfJoints();
        auto msg = std_msgs::msg::Float64MultiArray();
        retval;
        KDL::ChainIkSolverPos_LMA solver(kdl_chain);
        KDL::JntArray q_(n);
        KDL::JntArray q_init(n);
        KDL::JntArray q_sol(n);

        pos_goal.M = KDL::Rotation::RPY( 0.0, 0.0, 0.0);
        pos_goal.p = KDL::Vector( point.x, point.y, point.z);
        retval = solver.CartToJnt(q_init, pos_goal,q_sol);
        msg.data = { (float)q_sol(0), (float)q_sol(1), (float)q_sol(2), (float)q_sol(3), (float)q_sol(4), (float)q_sol(5)};
        publisher_->publish(msg);
          RCLCPP_INFO(this->get_logger(), "Done");   
    }

            
        int retval;
        KDL::Chain kdl_chain;
        rclcpp::TimerBase::SharedPtr timer_;
        KDL::Frame pos_goal;
        rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_;
        rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr subscription_;
        size_t count_;
};

//Driver code
int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<XArm1SKinematics>());
    rclcpp::shutdown();
    return 0;
}