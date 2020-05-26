#include "PID.h"
#include <limits>
#include <cmath>
#include <iostream>
using namespace std;

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;
    
    p_error=0.0;
    i_error=0.0;
    d_error=0.0;

    prev_cte = 0.0;

    // Twiddle Parameter
    twiddle_IsApplied = false;

    p = { Kp , Ki , Kd };
    dp = { 0.1*Kp , 0.1*Ki , 0.1*Kd };
    dp_index = 0;

    total_error = 0.0;
    best_error = std::numeric_limits<double>::max(); // limits header
    step_iter= 0;
    step_total = 100; // Carry out twiddle algorithm every 300 times 
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */

    /*if (step_num == 0) {
		prev_cte = cte;
	}*/

    p_error = cte;
    i_error += cte;
    d_error = cte - prev_cte;
    prev_cte = cte;  

    //step_iter++;

}

double PID::TotalError() {
    /**
     * TODO: Calculate and return the total error
     */
    double steer = -Kp * p_error - Kd * d_error - Ki * i_error;
    // Calculate steering value here, remember the steering value is[-1, 1].
    if (steer > 1.0)
    {
        steer = 1.0;
    }
    else if (steer < -1.0)
    {
        steer = -1.0;
    }
    
  std::cout << "Errors---> P_Error: " << p_error << " , D_Error:  " << d_error << " ,  I_Error:" << i_error << std::endl;

  return steer;  // TODO: Add your total error calc here!
}

// ========== Twiddle Algorithm for PID Gains ===========//
void PID::Twiddle(double cte)
{
    twiddle_IsApplied = true;
    total_error += pow(cte, 2); // Total cross track error

    // Run Twiddle Algorithm every other 'step_total' times
    if ((step_iter % step_total) == 0)
    {
        if (total_error < best_error)
        {
            flag_improved = true;
            flag_stepback = false;
            best_error = total_error;
            dp[dp_index] *= 1.1;
            std::cout << "In improved" << dp[dp_index] << std::endl;
            std::cout << "Best Error Reset" << best_error << std::endl;


        }
        else  // not improved
        {
            //best_error keep the same;
            flag_improved = false;
            flag_stepback = true;
        }
        // Post-Processing
        // case 1. Pure Improvement
        if (flag_improved && (!flag_stepback))         // improved:true && step_back:false
        {
            std::cout << "In flags" << flag_improved << std::endl;
            Update_Kpid(dp_index, dp[dp_index]);
            flag_improved = false;//reset for next step
        }
        // case 2. Not Improved, take a step back
        else if ((!flag_improved) && (flag_stepback))   // improved:false && step_back:true
        {
            Update_Kpid(dp_index, (-2.0)*dp[dp_index]);
            dp[dp_index] *= 1.1;
            flag_stepback = false;//reset for next step
        }
        // Other cases    // improved:true && step_back:true  // improved:false && step_back:false
        else
        {
            Update_Kpid(dp_index, dp[dp_index]);
            dp[dp_index] *= 0.9;
            flag_improved = true;
            flag_stepback = false;
            // let's try other index
            dp_index = (dp_index + 1) % 3;
        }
        total_error = 0.0;//reset total_error
    }
    step_iter++; 
    std::cout << "Best Error :" << best_error << " :  " << Kp << "   , " << Ki << " , " << Kd << std::endl;
    std::cout << "step_iter :" << step_iter << std::endl;
    std::cout << "Mod :" << (step_iter % step_total) << std::endl;
    std::cout << "Total Error :" << total_error << std::endl;
    std::cout << "=====================" << std::endl;

}



// Update PID values based on which case the Twiddle Algorithm determines
void PID::Update_Kpid(int case_id, double value)
{
    switch (case_id)
    {
    case 0:
        Kp += value;
        std::cout << "Kp is updated to --->"<<Kp << std::endl;
    case 1:
        Ki += value;
        std::cout << "Ki is updated to --->" << Ki << std::endl;
    case 2:
        Kd += value;
        std::cout << "Kd is updated to --->" << Kd << std::endl;
    }
}
