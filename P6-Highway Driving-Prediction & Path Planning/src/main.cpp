#include <uWS/uWS.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Eigen-3.3/Eigen/Core"
#include "Eigen-3.3/Eigen/QR"
#include "helpers.h"
#include "json.hpp"
#include "spline.h"

// for convenience
using nlohmann::json;
using std::string;
using std::vector;

int main() {
    uWS::Hub h;

    // Load up map values for waypoint's x,y,s and d normalized normal vectors
    vector<double> map_waypoints_x;
    vector<double> map_waypoints_y;
    vector<double> map_waypoints_s;
    vector<double> map_waypoints_dx;
    vector<double> map_waypoints_dy;

    // Waypoint map to read from
    // Track: 181 points (784.6001 1135.571 0 -0.02359831 -0.9997216) : (x,y,s,dx,dy)
    string map_file_ = "../data/highway_map.csv";
    // The max s value before wrapping around the track back to 0
    double max_s = 6945.554; //m


    std::ifstream in_map_(map_file_.c_str(), std::ifstream::in);

    string line;
    while (getline(in_map_, line)) {
        std::istringstream iss(line);
        double x;
        double y;
        float s;
        float d_x;
        float d_y;
        iss >> x;
        iss >> y;
        iss >> s;
        iss >> d_x;
        iss >> d_y;
        map_waypoints_x.push_back(x);
        map_waypoints_y.push_back(y);
        map_waypoints_s.push_back(s);
        map_waypoints_dx.push_back(d_x);
        map_waypoints_dy.push_back(d_y);
    }

    int ego_lane = 1; //ego starts @ middle lane
    double ref_speed = 0.0; // reference speed to target; mph
    double max_speed = 49.5; // mph
    double ref_acc = 0.224; // 1m/s = 2.237 mph
    double safety_cushion = 30.0; // [m] S=v^2/(2*a)=(25m/s--56mph)^2/(2*10 tot acc)


    h.onMessage([&map_waypoints_x, &map_waypoints_y, &map_waypoints_s,
        &map_waypoints_dx, &map_waypoints_dy, &ego_lane, &ref_speed, &max_speed, &ref_acc,&safety_cushion]
        (uWS::WebSocket<uWS::SERVER> ws, char* data, size_t length,
            uWS::OpCode opCode) {
                // "42" at the start of the message means there's a websocket message event.
                // The 4 signifies a websocket message
                // The 2 signifies a websocket event
                if (length && length > 2 && data[0] == '4' && data[1] == '2') {

                    auto s = hasData(data);

                    if (s != "") {
                        auto j = json::parse(s);

                        string event = j[0].get<string>();

                        if (event == "telemetry") {
                            // j[1] is the data JSON object

                            // Main car's localization Data
                            double car_x = j[1]["x"];
                            double car_y = j[1]["y"];
                            double car_s = j[1]["s"];
                            double car_d = j[1]["d"];
                            double car_yaw = j[1]["yaw"];
                            double car_speed = j[1]["speed"];

                            // Previous path data given to the Planner
                            auto previous_path_x = j[1]["previous_path_x"];
                            auto previous_path_y = j[1]["previous_path_y"];
                            // Previous path's end s and d values 
                            double end_path_s = j[1]["end_path_s"];
                            double end_path_d = j[1]["end_path_d"];

                            // Sensor Fusion Data, a list of all other cars on the same side 
                            //   of the road.
                            auto sensor_fusion = j[1]["sensor_fusion"];

                            json msgJson;

                            // next_x_vals.push_back(car_x + (dist_inc * i) * cos(deg2rad(car_yaw)));


                            /**
                             * TODO: define a path made up of (x,y) points that the car will visit
                             *   sequentially every .02 seconds
                            */

                            vector<double> next_x_vals;
                            vector<double> next_y_vals;

                            int prev_path_size = previous_path_x.size();  // prev path size the ego car was following before starts this run
                            double delta_t = 0.02;
                            //std::cout << "Prev_path_size:"<<prev_path_size <<std::endl;
                            //constexpr double cov_mph2meterpsec = 0.447;
                            //double decceleration ; 

                            if (prev_path_size > 0)
                            {
                                // Previous path left s_position 
                                car_s = end_path_s;
                                //std::cout << "car_s:" << car_s << std::endl;
                            }

                            bool car_ahead = false;
                            bool car_left = false;  // has the car@ left
                            bool car_right = false; // has the car@ right
                            bool is_other_intheway = false;  // default: no cars in the way


                            //find ref_speed to use
                            for (int i = 0; i < sensor_fusion.size(); i++)
                            {
                                // Info for other car; sensor_fusion[i];  [ id, x, y, vx, vy, s, d]
                                //int other_car_id = sensor_fusion[i][0];
                                //double other_car_x = sensor_fusion[i][1];
                                //double other_car_y = sensor_fusion[i][2];

                                float other_car_d = sensor_fusion[i][6];
                                // Get other_car lane
                                int other_car_lane = -1;

                                if (other_car_d >= 0 && other_car_d < 4) {
                                    other_car_lane = 0;
                                }
                                else if (other_car_d >= 4 && other_car_d < 8) {
                                    other_car_lane = 1;
                                }
                                else if (other_car_d >= 8 && other_car_d < 12) {
                                    other_car_lane = 2;
                                }
                                if (other_car_lane == -1)
                                {
                                    continue;
                                }


                                // !! Car Unit miles mph
                                double other_car_vx = sensor_fusion[i][3];
                                double other_car_vy = sensor_fusion[i][4];
                                double other_car_s = sensor_fusion[i][5];
                                double other_car_speed = sqrt(other_car_vx * other_car_vx + other_car_vy * other_car_vy); // mph


                                // Estimate the next s state of the other car; assumed in linear motion
                                other_car_s += ((double)prev_path_size * delta_t * other_car_speed);

                                // Check if the ego-vehicle has the Space cushion, ie. no other vehicle in the way, to change lane
                                is_other_intheway = ((other_car_s > (car_s)) && ((other_car_s - car_s) < safety_cushion)); // ---> *** true
                                //is_other_intheway = ((other_car_speed > (car_s - safety_cushion)) && ((other_car_s - car_s) < safety_cushion)); // ---> *** true

                                // ego_car and the other car is in the same lane
                                if (ego_lane == other_car_lane)
                                {
                                    if (is_other_intheway)
                                    {
                                        car_ahead = true;
                                    }
                                }

                                // Check if the car can change the lane
                                if (ego_lane > 0)
                                {
                                    if (ego_lane - other_car_lane == 1)
                                    {
                                        float diff = abs(other_car_s - car_s);
                                        if (diff < 30)
                                        {
                                            car_left = true; // left has a car and distance less than 30; too close.
                                        }

                                    }

                                }
                                if (ego_lane < 2)
                                {
                                    if (ego_lane - other_car_lane == -1)
                                    {
                                        float diff = abs(other_car_s - car_s);
                                        if (diff < 30)
                                        {
                                            car_right = true;// right has a car and distance less than 30; too close.
                                        }

                                    }
                                }
                            }// End: for sensor_fusion

                            if (car_ahead)
                            {
                                //car_speed -=0.1*ref_acc;
                                ref_speed -= ref_acc;
                                // car in the way, By pass from left
                                if (ego_lane > 0 && (!car_left)) // car_left=false: no car/left space avalaible; ego_lane>0: not in the left lane
                                {
                                    ego_lane -= 1;
                                }
                                // Check if we can pass from the Right side
                                else if (ego_lane < 2 && (!car_right))
                                {
                                    ego_lane += 1;
                                }
                               
                            }
                            else // if other car is not ahead
                            {
                                if (ref_speed < max_speed)
                                {
                                    ref_speed += ref_acc;
                                }
                                //std::cout << "ref_speed:" << ref_speed << std::endl; //good

                            }



                            // Interpolate and spline the known points to plot
                            // Create a list of widely spaced (x,y) waypoints, evenly spaced 
                            vector<double> x_points;
                            vector<double> y_points;

                            //  reference ego car(x,y,yaw) state:
                            //  c1. either reference the starting point as the car is or c2.at the previous paths end point
                            double ref_ego_x = car_x;
                            double ref_ego_y = car_y;
                            double ref_ego_yaw = deg2rad(car_yaw);

                            // c1.if Previous path is almost empty, use the car as starting reference
                            if (prev_path_size < 2)
                            {
                                // Use 2 points that make the path tangent to the angle of car
                                double prev_car_x = car_x - cos(car_yaw);
                                double prev_car_y = car_y - sin(car_yaw);

                                x_points.push_back(prev_car_x);
                                x_points.push_back(car_x);
                                y_points.push_back(prev_car_y);
                                y_points.push_back(car_y);
                            }
                            // c2.use previous paths end point as start references

                            else
                            {
                                ref_ego_x = previous_path_x[prev_path_size - 1];
                                ref_ego_y = previous_path_y[prev_path_size - 1];

                                double prev_car_x2 = previous_path_x[prev_path_size - 2];
                                double prev_car_y2 = previous_path_y[prev_path_size - 2];
                                ref_ego_yaw = atan2(ref_ego_y - prev_car_y2, ref_ego_x - prev_car_x2);

                                // Use 2 points that make the path tangent to the previos path's end point

                                x_points.push_back(prev_car_x2);
                                x_points.push_back(ref_ego_x);

                                y_points.push_back(prev_car_y2);
                                y_points.push_back(ref_ego_y);

                            }

                            // Add 3 evenly-distributed refernece points ahead of the starting point
                            /*
                            for ( int j = 0; j < 3; j++)
                            {
                                vector<double> next_waypoint = getXY(car_s + safety_cushion*(1+j), (2 + 4 * ego_lane), map_waypoints_s, map_waypoints_x, map_waypoints_y);

                                x_points.push_back(next_waypoint[0]);
                                y_points.push_back(next_waypoint[1]);
                                std::cout << "Next way point: " << next_waypoint[0] << std::endl;

                            }
                            */

                            // In Frenet add evenly 30m spaced points ahead of the starting refereence
                            vector<double> next_wp0 = getXY(car_s + 30, (2 + 4 * ego_lane), map_waypoints_s, map_waypoints_x, map_waypoints_y);
                            vector<double> next_wp1 = getXY(car_s + 60, (2 + 4 * ego_lane), map_waypoints_s, map_waypoints_x, map_waypoints_y);
                            vector<double> next_wp2 = getXY(car_s + 90, (2 + 4 * ego_lane), map_waypoints_s, map_waypoints_x, map_waypoints_y);

                            x_points.push_back(next_wp0[0]);
                            x_points.push_back(next_wp1[0]);
                            x_points.push_back(next_wp2[0]);

                            y_points.push_back(next_wp0[1]);
                            y_points.push_back(next_wp1[1]);
                            y_points.push_back(next_wp2[1]);


                            // std::cout << "X points : ## " << x_points.size() << std::endl;  // 8points

                            // Shift the reference points angle to the ego_vehicle coordiante
                            for (int j = 0; j < x_points.size(); j++)
                            {
                                // shift car reference angle to 0 degrees
                                double x_shift = x_points[j] - ref_ego_x;
                                double y_shift = y_points[j] - ref_ego_y;

                                x_points[j] = x_shift * cos(0 - ref_ego_yaw) - y_shift * sin(0 - ref_ego_yaw);
                                y_points[j] = x_shift * sin(0 - ref_ego_yaw) + y_shift * cos(0 - ref_ego_yaw);

                                //std::cout << "EGO X_point : ########### " << x_points[j] << std::endl;  // 8points
                                //std::cout << "EGO Y_point : ########### " << y_points[j] << std::endl;  // 8points


                            }

                            // Spline Object: piece-wise polynomial func; guaranteed to go thru all the points

                            tk::spline s;

                            s.set_points(x_points, y_points);

                            // Staet with all of the previous path points from last time to help Transition 
                            for (int j = 0; j < previous_path_x.size(); j++)
                            {
                                next_x_vals.push_back(previous_path_x[j]);
                                next_y_vals.push_back(previous_path_y[j]);

                            }

                            // Calculate how to beak up spline points so that we trabel at desired reference speed
                            double target_x = safety_cushion;
                            double target_y = s(target_x);
                            double target_dist = sqrt(target_x * target_x + target_y * target_y);
                            //std::cout << "**** Target Distance : ########### " << target_dist << std::endl; 

                            //std::cout << "Target Distance : " << target_dist << std::endl; // 31.266


                            double x_add_on = 0; //dist_inc

                            // Append the new waypoints after previous points to build a 50-point path
                            for (int j = 1; j <= 50 - previous_path_x.size(); j++)
                            {
                                // split the distance btw current point to desired target into N pieces;
                                // N*0.02(s visit the next point)*velocity = target_distance
                                double N = (target_dist / (0.02 * ref_speed / 2.24));// /2.24 --> convert to m/s
                                // get XY coordiantes along the spline
                                double x_point = x_add_on + (target_x) / N;
                                double y_point = s(x_point);

                                //std::cout << "N : ########### " << N<< "X_POINT"<<x_point << std::endl; previous paths end point

                                x_add_on = x_point;

                                double x_ref = x_point;
                                double y_ref = y_point;

                                // Convert back to global coordiante
                                x_point = x_ref * cos(ref_ego_yaw) - y_ref * sin(ref_ego_yaw);
                                y_point = x_ref * sin(ref_ego_yaw) + y_ref * cos(ref_ego_yaw);

                                x_point += ref_ego_x;
                                y_point += ref_ego_y;

                                //std::cout << "next_x_val size : " << next_x_vals.size() << std::endl;
                                //std::cout << "x_point : " << x_point << std::endl;
                                //std::cout << "y_point : " << y_point << std::endl;

                                next_x_vals.push_back(x_point);
                                next_y_vals.push_back(y_point);

                            }

                            //***********************//
                            msgJson["next_x"] = next_x_vals;
                            msgJson["next_y"] = next_y_vals;

                            auto msg = "42[\"control\"," + msgJson.dump() + "]";

                            ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
                        }  // end "telemetry" if
                    }
                    else {
                        // Manual driving
                        std::string msg = "42[\"manual\",{}]";
                        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
                    }
                }  // end websocket if
        }); // end h.onMessage

    h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
        std::cout << "Connected!!!" << std::endl;
        });

    h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code,
        char* message, size_t length) {
            ws.close();
            std::cout << "Disconnected" << std::endl;
        });

    int port = 4567;
    if (h.listen(port)) {
        std::cout << "Listening to port " << port << std::endl;
    }
    else {
        std::cerr << "Failed to listen to port" << std::endl;
        return -1;
    }

    h.run();
}