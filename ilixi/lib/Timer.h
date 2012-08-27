/*
 Copyright 2010-2012 Tarik Sekmen.

 All Rights Reserved.

 Written by Tarik Sekmen <tarik@ilixi.org>.

 This file is part of ilixi.

 ilixi is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 ilixi is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with ilixi.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ILIXI_TIMER_H_
#define ILIXI_TIMER_H_

#include <sigc++/signal.h>
#include <stdint.h>

namespace ilixi
{
//! Provides timers with milliseconds intervals.
class Timer : public sigc::trackable
{
    friend class AppBase;
public:
    /*!
     * Constructor.
     * By default, creates a timer with 500ms interval which will exec only once.
     */
    Timer();

    /*!
     * Destructor.
     */
    virtual
    ~Timer();

    /*!
     * Returns interval in milliseconds.
     */
    unsigned int
    interval() const;

    /*!
     * Returns the number of times to execute timer.
     */
    unsigned int
    repeats() const;

    /*!
     * Starts timer and sets the interval.
     */
    void
    start(unsigned int msec, unsigned int repeats = 0);

    /*!
     * Stops timer.
     */
    void
    stop();

    /*!
     * Sets the interval in milliseconds.
     */
    void
    setInterval(unsigned int msec);

    /*!
     * Sets number of times to execute timer.
     */
    void
    setRepeats(unsigned int number);

    /*!
     * User function that gets executed.
     */
    virtual void
    notify();

    int64_t
    expiry() const;

    /*!
     * This signal is emitted when timer is fired.
     */
    sigc::signal<void> sigExec;
protected:
    /*!
     * Callback functionoid which will actually fire timer.
     */
    bool
    funck();

private:
    //! Interval between consecutive executions.
    unsigned int _interval;
    //! Number of times to execute timer.
    unsigned int _repeats;
    //! Current repeat count.
    unsigned int _count;
    //! This stores next time timer fires.
    int64_t _expiry;

    // Callback uses step()
    friend bool
    timerCallback(void*);
};

} /* namespace ilixi */
#endif /* ILIXI_TIMER_H_ */
