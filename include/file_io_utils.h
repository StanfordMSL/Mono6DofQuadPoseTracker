#pragma once

// GTSAM Includes
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>

// ROS Includes
#include <rosbag/bag.h>
#include <rosbag/view.h>
// #include <std_msgs/Int32.h>
#include <geometry_msgs/Pose.h> 
#include <geometry_msgs/PoseStamped.h> 
// #include <sensor_msgs/CameraInfo.h> // geometry_msgs/PoseStamped sensor_msgs/CameraInfo sensor_msgs/Image tf/tfMessage 

#include <msl_raptor/AngledBbox.h>
#include <msl_raptor/AngledBbox.h>
#include <msl_raptor/TrackedObject.h>
#include <msl_raptor/TrackedObjects.h>

#include "math_utils.h"
#include "shared_imports.h"

namespace rslam_utils {
    void load_rosbag(vector<tuple<double, gtsam::Pose3, gtsam::Pose3, map<string, pair<gtsam::Pose3, gtsam::Pose3> > > > &raptor_data, int &num_ado_objs,
                    std::string rosbag_fn, std::string ego_ns, std::map<std::string, obj_param_t> obj_param_map, double dt_thresh, bool b_nocs_data);

    void process_raptor_estimates(msl_raptor::TrackedObjects::ConstPtr & raptor_msg, map<string, object_data_vec_t> & ado_data_est, const map<string, geometry_msgs::Pose> & last_gt_pose);
                    
    void convert_data_to_static_obstacles(vector<tuple<double, gtsam::Pose3, gtsam::Pose3, map<string, pair<gtsam::Pose3, gtsam::Pose3> > > > &raptor_data, int num_ado_objs);

    int get_tf_w_ado_for_all_objects(const vector<tuple<double, gtsam::Pose3, gtsam::Pose3, map<string, pair<gtsam::Pose3, gtsam::Pose3> > > > &raptor_data, 
                                       map<string, gtsam::Pose3> &tf_w_ado0_gt, map<string, gtsam::Pose3> &tf_w_ado0_est, int num_ado_objs);

    void group_ado_measurements_by_time(vector<pair<double, map<string, pair<gtsam::Pose3, gtsam::Pose3>>>> &ado_data_grouped,
                                        const map<string, object_est_gt_data_vec_t> &ado_data, double dt_thresh);

    void zip_data_by_ego(vector<tuple<double, gtsam::Pose3, gtsam::Pose3, map<string, pair<gtsam::Pose3, gtsam::Pose3> > > > &raptor_data, 
                            object_est_gt_data_vec_t ego_data, const vector<pair<double, map<string, pair<gtsam::Pose3, gtsam::Pose3>>>> &ado_data_grouped, 
                            double dt_thresh);

    gtsam::Pose3 ros_geo_pose_to_gtsam(geometry_msgs::Pose ros_pose);

    void sync_est_and_gt(object_data_vec_t data_est, object_data_vec_t data_gt, object_est_gt_data_vec_t& data, obj_param_t params, double dt_thresh);

    void write_batch_slam_inputs_csv(string fn, vector<tuple<double, gtsam::Pose3, gtsam::Pose3, map<string, pair<gtsam::Pose3, gtsam::Pose3> > > > &raptor_data, 
                                    map<string, obj_param_t> obj_param_map);
                                    
    void write_all_traj_csv(string fn, const vector<tuple<double, gtsam::Pose3, gtsam::Pose3, map<string, pair<gtsam::Pose3, gtsam::Pose3> > > > &raptor_data,
                            map<gtsam::Symbol, map<double, pair<gtsam::Pose3, gtsam::Pose3> > > & all_trajs,
                            map<string, obj_param_t> &obj_param_map, int num_ado_objs);

    void write_results_csv(string fn, const vector<tuple<double, gtsam::Pose3, gtsam::Pose3, map<string, pair<gtsam::Pose3, gtsam::Pose3> > > > &raptor_data, 
                            map<gtsam::Symbol, gtsam::Pose3> &tf_w_est_preslam_map, 
                            map<gtsam::Symbol, gtsam::Pose3> &tf_w_est_postslam_map, 
                            map<gtsam::Symbol, map<gtsam::Symbol, pair<gtsam::Pose3, gtsam::Pose3> > > &tf_ego_ado_maps,
                            map<string, obj_param_t> &obj_param_map);

    string pose_to_string_line(gtsam::Pose3 p);

    void trim_data_range(vector<tuple<double, gtsam::Pose3, gtsam::Pose3, map<string, pair<gtsam::Pose3, gtsam::Pose3> > > > &raptor_data, int start_ind, int end_ind);
}