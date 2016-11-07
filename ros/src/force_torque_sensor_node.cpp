/****************************************************************
 *
 * Copyright 2016 Intelligent Industrial Robotics (IIROB) Group,
 * Institute for Anthropomatics and Robotics (IAR) -
 * Intelligent Process Control and Robotics (IPR),
 * Karlsruhe Institute of Technology
 *
 * Maintainers: Denis Štogl, email: denis.stogl@kit.edu
 *                     Florian Heller
 *                     Vanessa Streuer
 *
 * Date of update: 2014-2016
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * Copyright (c) 2010
 *
 * Fraunhofer Institute for Manufacturing Engineering
 * and Automation (IPA)
 *
 * Author: Alexander Bubeck, email:alexander.bubeck@ipa.fhg.de
 * Supervised by: Alexander Bubeck, email:alexander.bubeck@ipa.fhg.de
 *
 * Date of creation: June 2010
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License LGPL as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License LGPL for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License LGPL along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************/
#include <ati_force_torque/force_torque_sensor.h>

class ForceTorqueSensorNode : public ForceTorqueSensor
{
public:
    ForceTorqueSensorNode(ros::NodeHandle &nh);

    void updateFTData(const ros::TimerEvent &event);


private:
    ros::Timer ftUpdateTimer_;

    tf2_ros::TransformListener *p_tfListener;
    tf2::Transform transform_ee_base;
};

ForceTorqueSensorNode::ForceTorqueSensorNode(ros::NodeHandle &nh) : ForceTorqueSensor(nh)
{
    nh_.param<std::string>("Node/sensor_frame", sensor_frame_, "fts_reference_link");
    nh_.param<std::string>("Node/transform_frame", transform_frame_, "fts_base_link");
}

void ForceTorqueSensorNode::updateFTData(const ros::TimerEvent &event)
{
    filterFTData();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "forcetorque_node");
    ros::NodeHandle nh("/fts");

    ForceTorqueSensorNode ftn(nh);

    ROS_INFO("ForceTorque Sensor Node running.");

    ros::spin();

    return 0;
}

