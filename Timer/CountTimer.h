#pragma once

#ifndef COUNTIMER_H
#define COUNTIMER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "../mDef.h"
#include "timeLogic.h"

class Countimer
{
public:
    friend class Relay;

    Countimer();
    ~Countimer();

    enum CountType
    {
        COUNT_NONE = 0,
        COUNT_UP = 1,
        COUNT_DOWN = 2
    };

    // Set up counter time(hours, minutes, seconds), count mode and function to execute if count is completed.
    void setCounter(uint16_t hours, uint8_t minutes, uint8_t seconds, CountType countType, funcVoid_p onComplete);

    // Set up counter time(hours, minutes, seconds) for existing timer.
    void setCounter(uint16_t hours, uint8_t minutes, uint8_t seconds);

    // Returns timer's current hours.
    uint16_t getCurrentHours();

    // Returns timer's current minutes.
    uint8_t getCurrentMinutes();

    // Returns timer's current seconds.
    uint8_t getCurrentSeconds();

    void setInterval(funcVoid_p callback, clock_t interval);

    // Returns current timer as formatted string HH:MM:SS
    char *getCurrentTime();

    // Returns true if counter is completed, otherwise returns false.
    bool isCounterCompleted();

    // Returns true if counter is still running, otherwise returns false.
    bool isCounterRunning();

    // Returns true if timer is stopped, otherwise returns false.
    bool isStopped();

    // Run timer. This is main method.
    // If you want to start timer after run, you have to invoke start() method.
    void run();

    // Starting timer.
    void start();

    // Stopping timer.
    void stop();

    // Pausing timer.
    void pause();

    // Restart timer.
    void restart();

private:
    // Counting down timer.
    void countDown();

    void callback();
    void complete();

    // Counting up timer.
    void countUp();

    clock_t _interval = 1;
    clock_t _previousMillis;

    // Stores current counter value in milliseconds.
    clock_t _currentCountTime;
    clock_t _startCountTime;

    // Stores cached user's time.
    clock_t _countTime;

    // Function to execute.
    funcVoid_p _callback;

    // Function to execute when timer is complete.
    funcVoid_p _onComplete;
    bool _isCounterCompleted;
    bool _isStopped;
    char _formatted_time[10];
    CountType _countType;
};

Countimer::Countimer()
{
    _previousMillis = 0;
    _currentCountTime = 0;
    _countTime = 0;
    _isCounterCompleted = false;
    _isStopped = true;
    _countType = COUNT_NONE;
    _startCountTime = 0;
}



void Countimer::setCounter(uint16_t hours, uint8_t minutes, uint8_t seconds, CountType countType, funcVoid_p onComplete)
{
    _onComplete = onComplete;
    _countType = countType;
    setCounter(hours, minutes, seconds);
}

void Countimer::setCounter(uint16_t hours, uint8_t minutes, uint8_t seconds)
{
    if (hours > COUNTIMER_MAX_HOURS)
    {
        hours = COUNTIMER_MAX_HOURS;
    }

    if (minutes > COUNTIMER_MAX_MINUTES_SECONDS)
    {
        minutes = COUNTIMER_MAX_MINUTES_SECONDS;
    }

    if (seconds > COUNTIMER_MAX_MINUTES_SECONDS)
    {
        seconds = COUNTIMER_MAX_MINUTES_SECONDS;
    }

    _currentCountTime = ((hours * IN_HOURS) + (minutes * IN_MINUTES) + seconds) * IN_SECONDS;
    _countTime = _currentCountTime;

    if (_countType == COUNT_UP)
    {
        // if is count up mode, we have to start from 00:00:00;
        _currentCountTime = 0;
    }

    _startCountTime = _currentCountTime;
}

void Countimer::setInterval(funcVoid_p callback, clock_t interval)
{
    _interval = interval;
    _callback = callback;
}

uint16_t Countimer::getCurrentHours()
{
    return _currentCountTime / 1000ul / 3600ul;
}

uint8_t Countimer::getCurrentMinutes()
{
    return _currentCountTime / 1000ul % 3600ul / 60ul;
}

uint8_t Countimer::getCurrentSeconds()
{
    return _currentCountTime / 1000ul % 3600ul % 60ul % 60ul;
}

char *Countimer::getCurrentTime()
{
    sprintf(_formatted_time, "%02d:%02d:%02d", getCurrentHours(), getCurrentMinutes(), getCurrentSeconds());
    return _formatted_time;
}

bool Countimer::isCounterCompleted()
{
    return _isCounterCompleted;
}

bool Countimer::isStopped()
{
    return _isStopped;
}

bool Countimer::isCounterRunning()
{
    return !_isStopped;
}

void Countimer::start()
{
    _isStopped = false;
    if (_isCounterCompleted)
        _isCounterCompleted = false;
}

void Countimer::pause()
{
    _isStopped = true;
}

void Countimer::stop()
{
    _isStopped = true;
    _isCounterCompleted = true;
    _currentCountTime = _countTime;

    if (_countType == COUNT_UP)
    {
        _currentCountTime = 0;
    }
}

void Countimer::restart()
{
    _currentCountTime = _startCountTime;
    _isCounterCompleted = false;
    _isStopped = false;

    start();
}

void Countimer::run()
{
    // timer is running only if is not completed or not stopped.
    if (_isCounterCompleted || _isStopped)
        return;

    if (millis() - _previousMillis >= _interval)
    {

        if (_countType == COUNT_DOWN)
        {
            countDown();
        }
        else if (_countType == COUNT_UP)
        {
            countUp();
        }
        else
        {
            callback();
        }
        _previousMillis = millis();
    }
}

void Countimer::countDown()
{
    if (_currentCountTime > 0)
    {
        callback();
        _currentCountTime -= _interval;
    }
    else
    {
        stop();
        complete();
    }
}

void Countimer::countUp()
{
    if (_currentCountTime < _countTime)
    {
        callback();
        _currentCountTime += _interval;
    }
    else
    {
        stop();
        complete();
    }
}

void Countimer::callback()
{
    if (_callback != NULL)
        _callback();
}

void Countimer::complete()
{
    if (_onComplete != NULL)
        _onComplete();
	if(_onComplete != NULL)
		_onComplete();
        // if (_countType == COUNT_UP)
        // {
            // this->restart();
        // }
        
}

#endif
