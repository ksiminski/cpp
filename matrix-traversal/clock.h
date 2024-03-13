/** @file */

#ifndef CLOCK_H
#define CLOCK_H


#include <chrono>

namespace ksi
{
   /** This class simplifies measurement of time. 
    @date 2018-04-07
    */
   class clock
   {
      std::chrono::steady_clock _zegar;
      std::chrono::steady_clock::time_point _start {};
      std::chrono::steady_clock::time_point _stop  {};
      
   public:
      
      /** Starts the clock.
       * @return start time point
         @date 2018-04-07 */
      std::chrono::steady_clock::time_point start ();
      
      /** Stops the clock.
       * @return stop time point 
         @date 2018-04-07 
       */
      std::chrono::steady_clock::time_point stop ();
      
      /** @return elapsed seconds 
        * @date 2018-04-07 
        */
      std::size_t elapsed_seconds();

      /** @return elapsed milliseconds 
        * @date 2019-03-10 
        */
      std::size_t elapsed_milliseconds();
      
      /** @return Returns time (in seconds) without stopping the clock.
        * @date 2021-05-26 */
      std::size_t get_time_seconds();
      
      /** @return Returns time (in milliseconds) without stopping the clock.
        * @date 2021-05-26 */
      std::size_t get_time_milliseconds();
      
      /** @return Returns time (in microseconds) without stopping the clock.
        * @date 2021-05-26 */
      std::size_t get_time_microseconds();
      
      

   };
}

#endif 
