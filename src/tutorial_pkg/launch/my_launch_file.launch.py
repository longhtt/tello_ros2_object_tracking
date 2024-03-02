from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

   my_node = Node(
      package="tutorial_pkg",
      executable="my_first_node",
      name="my_node",
      remappings=[("/image", "image_raw")],
      parameters=[{"timer_period_s": 2}]
   )

   image_saver = Node(
      package="image_view",
      executable="image_saver",
      name="image_saver",
      remappings=[("/image", "/image_raw"), ("/camera_info_n2", "/your/camera/camera_info_n2")],
      parameters=[{"save_all_image": False}]
   )

   return LaunchDescription([my_node, image_saver])