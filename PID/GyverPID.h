#ifndef _GyverPID_h
#define _GyverPID_h
#include <Arduino.h> //https://github.com/GyverLibs/GyverPID/blob/main/examples/thermocouplepid/thermocouplepid.ino

#if defined(PID_INTEGER)
typedef int16_t pidtype;
#else
typedef float pidtype;
#endif

#define NORMAL 0
#define REVERSE 1
#define ON_ERROR 0
#define ON_RATE 1

// typedef enum PID_DIRECTION
// {
//   DIRECT,
//   REVERSE
// }PID_DIRECTION;

typedef enum ERROR_PROPORTIONAL
{
    P_ON_M,
    P_ON_E
} ERROR_PROPORTIONAL;

typedef enum PID_MODE
{
    MANUAL,
    AUTOMATIC
} PID_MODE;

typedef struct
{
    float kp; // (P)roportional Tuning Parameter
    float ki; // (I)ntegral Tuning Parameter
    float kd; // (D)erivative Tuning Parameter
} PID_TUNINGS;

class GyverPID
{
public:
    GyverPID() {}

    GyverPID(PID_TUNINGS new_tunings, uint32_t new_dt = 100)
    {
        GyverPID(new_tunings.kp, new_tunings.ki, new_tunings.kd, new_dt);
    }

    GyverPID(float new_kp, float new_ki, float new_kd, uint32_t new_dt = 100)
    {
        setDt(new_dt);
        tunings.kp = new_kp;
        tunings.ki = new_ki;
        tunings.kd = new_kd;
    }

    // Direction of regulation: NORMAL (0) or REVERSE (1)
    void setDirection(bool direction)
    {
        _direction = direction;
    }

    // Mode: operation based on input error ON_ERROR (0) or on change ON_RATE (1)
    void setMode(bool mode)
    {
        _mode = mode;
    }

    // Limit of the output value (for example, for PWM we set 0-255)
    void setLimits(int16_t min_output, int16_t max_output)
    {
        _minOut = min_output;
        _maxOut = max_output;
    }

    // Setting the discretization time (for getResultTimer)
    void setDt(uint32_t new_dt)
    {
        _dt_s = new_dt / 1000.0f;
        _dt = new_dt;
    }

    pidtype setpoint = 0; // The setpoint value that the controller should maintain
    pidtype input = 0;    // Signal from the sensor (e.g., the temperature we are regulating)
    pidtype output = 0;   // Output from the controller to the control device (e.g., PWM value or servo angle)

    PID_TUNINGS tunings{};

    float integral = 0.0; // Integral sum

    // Returns a new value when called (if we use our timer with period dt!)
    pidtype getResult()
    {
        pidtype error = setpoint - input;        // Regulation error
        pidtype delta_input = prevInput - input; // Change in input signal over dt
        prevInput = input;                       // Remember the previous input
        if (_direction)
        {
            error = -error;
            delta_input = -delta_input;
        }
        output = _mode ? 0 : (error * tunings.kp);  // Proportional component
        output += delta_input * tunings.kd / _dt_s; // Derivative component

#if (PID_INTEGRAL_WINDOW > 0)
        // EXPERIMENTAL INTEGRAL WINDOW MODE
        if (++t >= PID_INTEGRAL_WINDOW)
            t = 0;                      // wrap around t if it exceeds the integral window size
        integral -= errors[t];          // subtract the old error value
        errors[t] = error * Ki * _dt_s; // store the new error value in the array
        integral += errors[t];          // add the new error value to the integral
#else
        integral += error * tunings.ki * _dt_s; // regular summation of the integral term
#endif

#ifdef PID_OPTIMIZED_I
        // EXPERIMENTAL MODE FOR LIMITING THE INTEGRAL SUM
        output = constrain(output, _minOut, _maxOut);
        if (Ki != 0)
            integral = constrain(integral, (_minOut - output) / (Ki * _dt_s), (_maxOut - output) / (Ki * _dt_s));
#endif

        if (_mode)
            integral += delta_input * tunings.kp;         // proportional to speed mode
        integral = constrain(integral, _minOut, _maxOut); // constrain the integral sum
        output += integral;                               // add the integral term to the output
        output = constrain(output, _minOut, _maxOut);     // constrain the final output
        return output;
    }

    // returns a new value no earlier than after dt milliseconds (built-in timer with a period of dt)
    pidtype getResultTimer()
    {
        if (millis() - pidTimer >= _dt)
        {
            pidTimer = millis();
            getResult();
        }
        return output;
    }

    // calculates the output based on the actual elapsed time between function calls
    pidtype getResultNow()
    {
        setDt(millis() - pidTimer);
        pidTimer = millis();
        return getResult();
    }

private:
    uint32_t _dt = 100; // iteration time in milliseconds
    float _dt_s = 0.1;  // iteration time in seconds
    bool _mode = 0, _direction = 0;
    int16_t _minOut = 0;
    int16_t _maxOut = UINT_LEAST8_MAX;
    pidtype prevInput = 0;
    uint32_t pidTimer = 0;
#if (PID_INTEGRAL_WINDOW > 0)
    pidtype errors[PID_INTEGRAL_WINDOW];
    uint16_t t = 0;
#endif
};
#endif