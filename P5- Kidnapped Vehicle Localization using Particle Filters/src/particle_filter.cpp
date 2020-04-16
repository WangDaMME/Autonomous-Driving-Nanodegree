/**
 * particle_filter.cpp
 *
 * Created on: Dec 12, 2016
 * Author: Tiffany Huang
 */

#include "particle_filter.h"

#include <math.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "helper_functions.h"

using std::string;
using std::vector;
using std::normal_distribution;


void ParticleFilter::init(double x, double y, double theta, double std[]) {
    /**
     * TODO: Set the number of particles. Initialize all particles to
     *   first position (based on estimates of x, y, theta and their uncertainties
     *   from GPS) and all weights to 1.
     * TODO: Add random Gaussian noise to each particle.
     * NOTE: Consult particle_filter.h for more information about this method
     *   (and others in this file).
     */

    num_particles = 120;  // TODO: Set the number of particles

    // This line creates a normal (Gaussian) distribution for x,y, theta
    normal_distribution<double> dist_x(x, std[0]);
    normal_distribution<double> dist_y(y, std[1]);
    normal_distribution<double> dist_theta(theta, std[2]);

    std::default_random_engine gen;


    for (int i = 0; i < num_particles; i++)
    {
        Particle p;
        p.id = i;
        p.x = dist_x(gen); //  where "gen" is the random engine initialized earlier.
        p.y = dist_y(gen);
        p.theta = dist_theta(gen);
        p.weight = 1.0;

        particles.push_back(p); //  std::vector<double> 
    }
    // Update initializer, done.
    is_initialized = true;
    //std::cout<<"Initialization called"<<std::endl;
}

void ParticleFilter::prediction(double delta_t, double std_pos[],
    double velocity, double yaw_rate) {
    /**
     * TODO: Add measurements to each particle and add random Gaussian noise.
     * NOTE: When adding noise you may find std::normal_distribution
     *   and std::default_random_engine useful.
     *  http://en.cppreference.com/w/cpp/numeric/random/normal_distribution
     *  http://www.cplusplus.com/reference/random/default_random_engine/
     */

     // Gaussian Noises
    normal_distribution<double> noise_x(0, std_pos[0]);
    normal_distribution<double> noise_y(0, std_pos[1]);
    normal_distribution<double> noise_theta(0, std_pos[2]);

    std::default_random_engine gen;

    // Add measurements to each particle
    for (int i = 0; i < num_particles; i++)
    {
        // Check division by zero; ie. yawrate=0
        if (fabs(yaw_rate) < 0.00001)
        {
            //xf=x0+v*cos(theta)*dt
            //yf=x0+v*sin(theta)*dt
            particles[i].x += velocity * cos(particles[i].theta) * delta_t;
            particles[i].y += velocity * sin(particles[i].theta) * delta_t;
            // theta unchanged 
        }
        else
        {
            //xf=x0+v/yaw_rate*(sin(theta0+yawrate*dt)-sin(theta0))
            //yf=y0+v/yaw_rate*(cos(theta0)-sin(theta0+yawrate*dt))
            //xf=x0+yawrate*dt
            particles[i].x += (velocity / yaw_rate) * (sin(particles[i].theta + yaw_rate * delta_t) - sin(particles[i].theta));
            particles[i].y += (velocity / yaw_rate) * (cos(particles[i].theta) - cos(particles[i].theta + yaw_rate * delta_t));
            particles[i].theta += yaw_rate * delta_t;

        }

        // Add noise
        particles[i].x += noise_x(gen);
        particles[i].y += noise_y(gen);
        particles[i].theta += noise_theta(gen);
    }

}

void ParticleFilter::dataAssociation(vector<LandmarkObs> predicted,
    vector<LandmarkObs>& observations) {
    /**
     * TODO: Find the predicted measurement that is closest to each
     *   observed measurement and assign the observed measurement to this
     *   particular landmark.
     * NOTE: this method will NOT be called by the grading code. But you will
     *   probably find it useful to implement this method and use it as a helper
     *   during the updateWeights phase.
     */

     //landmarks: id,x,y

    for (unsigned int i = 0; i < observations.size(); i++)
    {
        double min_dist = std::numeric_limits<double>::max(); //initialize the minimum distance with a large number
        int map_id = -1;

        // compare each predicted to observation
        for (unsigned int j = 0; j < predicted.size(); j++)
        {
            // distance btw observation to predicted
            double distance = dist(observations[i].x, observations[i].y, predicted[j].x, predicted[j].y);

            if (distance < min_dist)
            {
                min_dist = distance;
                //observations[i].id  = predicted[j].id;
                map_id = predicted[j].id;
            }
        }
        // update observations to the nearest neighbor from predicted  
        observations[i].id = map_id;

    }
}

void ParticleFilter::updateWeights(double sensor_range, double std_landmark[],
    const vector<LandmarkObs>& observations,
    const Map& map_landmarks)
{
    /**
     * TODO: Update the weights of each particle using a mult-variate Gaussian
     *   distribution. You can read more about this distribution here:
     *   https://en.wikipedia.org/wiki/Multivariate_normal_distribution
     * NOTE: The observations are given in the VEHICLE'S coordinate system.
     *   Your particles are located according to the MAP'S coordinate system.
     *   You will need to transform between the two systems. Keep in mind that
     *   this transformation requires both rotation AND translation (but no scaling).
     *   The following is a good resource for the theory:
     *   https://www.willamette.edu/~gorr/classes/GeneralGraphics/Transforms/transforms2d.htm
     *   and the following is a good resource for the actual equation to implement
     *   (look at equation 3.33) http://planning.cs.uiuc.edu/node99.html
     */
    double sig_x = std_landmark[0];
    double sig_y = std_landmark[1];
    double gauss_norm = 1 / (2 * M_PI * sig_x * sig_y);
    //1. Obtain the predicted landmarks which are in the range of sensor

    for (int i = 0; i < num_particles; i++)
    {
        // Info of each particle
        double p_x = particles[i].x;
        double p_y = particles[i].y;
        double p_theta = particles[i].theta;

        vector<LandmarkObs> predicted_landmark; // to store predicted in-range landmarks

        for (unsigned int j = 0; j < map_landmarks.landmark_list.size(); j++)
        {
            int landmark_id = map_landmarks.landmark_list[j].id_i;
            float landmark_x = map_landmarks.landmark_list[j].x_f; // global coordinate
            float landmark_y = map_landmarks.landmark_list[j].y_f; // global coordinate

            if (dist(p_x, p_y, landmark_x, landmark_y) <= sensor_range)
            {
                predicted_landmark.push_back(LandmarkObs{ landmark_id ,landmark_x ,landmark_y }); // landmarkObs struct
            }
        }

        // 2. Coordinate Transformation
        // observation: Vehicle coord  ---transform---> particles: in Map coord
        //Observations in the car coordinate system can be transformed into map coordinates 

        vector<LandmarkObs> obs_in_mapCoordinate; // to store observation in map coord, which were detected in car Coord  
        for (unsigned int k = 0; k < observations.size(); k++)
        {
            double map_obs_x = p_x + (cos(p_theta) * observations[k].x) - (sin(p_theta) * observations[k].y);
            double map_obs_y = p_y + (sin(p_theta) * observations[k].x) + (cos(p_theta) * observations[k].y);

            obs_in_mapCoordinate.push_back(LandmarkObs{ observations[k].id,map_obs_x,map_obs_y }); // LandmarkObs struct
        }

        // 3. Data Asscociation: to associate each transformed observation with a land mark identifier. 
        dataAssociation(predicted_landmark, obs_in_mapCoordinate);

        // 4. Weight Calculation
        // The particles final weight will be calculated as the product of each measurement's Multivariate-Gaussian probability density.

        // reset particle weights
        particles[i].weight = 1.0;

        //double exponent = (pow(x_obs - mu_x, 2) / (2 * pow(sig_x, 2)))
        // + (pow(y_obs - mu_y, 2) / (2 * pow(sig_y, 2)));
        for (unsigned int j = 0; j < obs_in_mapCoordinate.size(); j++)
        {
            for (unsigned int k = 0; k < predicted_landmark.size(); k++)
            {
                if (obs_in_mapCoordinate[j].id == predicted_landmark[k].id)
                {
                    double mu_x = predicted_landmark[k].x;
                    double mu_y = predicted_landmark[k].y;

                    double exponent = (pow(obs_in_mapCoordinate[j].x - mu_x, 2) / (2 * pow(sig_x, 2))) + (pow(obs_in_mapCoordinate[j].y - mu_y, 2) / (2 * pow(sig_y, 2)));

                    particles[i].weight *= gauss_norm * exp(-exponent);
                }


            }
        }

    } // End of Num_particles

}


void ParticleFilter::resample() {
    /**
     * TODO: Resample particles with replacement with probability proportional
     *   to their weight.
     * NOTE: You may find std::discrete_distribution helpful here.
     *   http://en.cppreference.com/w/cpp/numeric/random/discrete_distribution
     */

    vector<Particle> resampled_particles;
    double beta = 0.0;
    double w_max = 0.0;

    // Get the maximum Weight
    for (int i = 0; i < num_particles; i++)
    {   
        if (particles[i].weight > w_max)
        {
            w_max = particles[i].weight;
        }
    }

    std::default_random_engine gen;
    std::uniform_int_distribution<int> index_range(0, num_particles - 1);  // arbitary index from 0~num_particles
    int particle_index = index_range(gen);

    std::uniform_real_distribution<double> weight_range(0.0, w_max);  // arbitary weight from 0~num_particles

    for (int i = 0; i < num_particles; i++)
    {
        beta += weight_range(gen) * 2.0;

        while (beta > particles[particle_index].weight)
        {
            beta -= particles[particle_index].weight;
            particle_index = (particle_index + 1) % num_particles;
        }

        resampled_particles.push_back(particles[particle_index]);
    }
    particles.clear();
    for (int i = 0; i < num_particles; i++)
    {
        particles.push_back(resampled_particles[i]);
    }

}

void ParticleFilter::SetAssociations(Particle& particle,
    const vector<int>& associations,
    const vector<double>& sense_x,
    const vector<double>& sense_y) {
    // particle: the particle to which assign each listed association, 
    //   and association's (x,y) world coordinates mapping
    // associations: The landmark id that goes along with each listed association
    // sense_x: the associations x mapping already converted to world coordinates
    // sense_y: the associations y mapping already converted to world coordinates
    particle.associations = associations;
    particle.sense_x = sense_x;
    particle.sense_y = sense_y;
}

string ParticleFilter::getAssociations(Particle best) {
    vector<int> v = best.associations;
    std::stringstream ss;
    copy(v.begin(), v.end(), std::ostream_iterator<int>(ss, " "));
    string s = ss.str();
    s = s.substr(0, s.length() - 1);  // get rid of the trailing space
    return s;
}

string ParticleFilter::getSenseCoord(Particle best, string coord) {
    vector<double> v;

    if (coord == "X") {
        v = best.sense_x;
    }
    else {
        v = best.sense_y;
    }

    std::stringstream ss;
    copy(v.begin(), v.end(), std::ostream_iterator<float>(ss, " "));
    string s = ss.str();
    s = s.substr(0, s.length() - 1);  // get rid of the trailing space
    return s;
}
