/*
 * GTimer.h
 *
 *  Created on: May, 2019
 *      Author: esantiago
 */

#ifndef GTIMER_H_
#define GTIMER_H_


class GTimer{

    public:

      // constructor
      GTimer();

      // destructor
      ~GTimer();

      // start timer
      void start();

      // capture elasped time
      float getElapsedTime();

    private:

      Uint32 mstartTicks;

      float melapsedTime;

};


#endif  // GTIMER_H_
