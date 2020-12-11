#!/usr/bin/env python  
import rospy
from geometry_msgs.msg import PoseStamped
import geometry_msgs.msg
# Because of transformations
import tf_conversions
import tf2_ros


def callback(data):
    br = tf2_ros.TransformBroadcaster()
    t = geometry_msgs.msg.TransformStamped()

    t.header.stamp = data.header.stamp
    t.header.frame_id = data.header.frame_id
    t.child_frame_id = "fixed"
    t.transform.translation.x = data.pose.position.x
    t.transform.translation.y = data.pose.position.y
    t.transform.translation.z =data.pose.position.z
    
    t.transform.rotation.x = data.pose.orientation.x
    t.transform.rotation.y = data.pose.orientation.y
    t.transform.rotation.z = data.pose.orientation.z
    t.transform.rotation.w = data.pose.orientation.w

    br.sendTransform(t)
def listener():


    rospy.init_node('pose_stamped_to_tf', anonymous=True)
    rospy.Subscriber("/myo_raw/pose", PoseStamped, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
