/* Copyright (c) 2017, United States Government, as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 *
 * All rights reserved.
 *
 * The Astrobee platform is licensed under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with the
 * License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#include <localization_analysis/new_controller_tester.h>
#include <localization_common/logger.h>
#include <localization_common/utilities.h>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <ff_msgs/FamCommand.h>
#include <ff_msgs/ControlCommand.h>
#include <ff_util/ff_names.h>
#include <stddef.h>
#include <stdio.h>                     // This ert_main.c example uses printf/fflush 
#include <ros/ros.h>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH



int main(int argc, char** argv) {

  ros::init(argc, argv, "ctl");
  ros::NodeHandle nh1("gnc");
  ros::NodeHandle nh2(nh1 ,"ctl");
  
  rosbag::Bag bag;
    bag.open("test.bag", rosbag::bagmode::Read);

    std::vector<std::string> topics;
    topics.push_back(std::string("/gnc/ctl/command"));
    //topics.push_back(std::string("numbers"));

    rosbag::View view(bag, rosbag::TopicQuery(topics));


    foreach(rosbag::MessageInstance const m, view)
    {
      nh2.advertise<ff_msgs::ControlCommand>("/gnc/ctl/control", 1000, false);
        // //from the rosbag
        // ff_msgs::FamCommand::ConstPtr i = m.instantiate<ff_msgs::FamCommand>();
        // if (i != NULL)
        //     std::cout << i->control_mode << std::endl;
      
    }



    bag.close();
}
