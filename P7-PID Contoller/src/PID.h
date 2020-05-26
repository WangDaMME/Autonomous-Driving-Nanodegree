#ifndef PID_H
#define PID_H

#include<vector>

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;
  double prev_cte; // the cte from the last time //total_cte


  /**
   * PID Coefficientsb 
   */ 
  double Kp;
  double Ki;
  double Kd;

  //twiddle Algorithm
public:
  bool twiddle_IsApplied;
  std::vector<double> p;
  std::vector<double> dp;
  int dp_index;
  int step_iter;
  int step_total;
  double total_error;
  double best_error;
  // twiddle operation indicators
  bool flag_improved;
  bool flag_stepback;

public:
    void Twiddle(double cte);
    void Update_Kpid(int case_id, double value);


};
#endif  // PID_H