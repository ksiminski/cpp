/** [PL] Przykład użycia obietnicy (std::promise) i przyszłości (std::future).
 *  [EN] An example of an std::promise and an std::future.
 *  @date 2024-04-05
 *  @author Krzysztof Siminski
 *  */

#include <future>
#include <syncstream>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <random>

////////////////////////////////////
typedef std::vector<int>           my_container; 
typedef std::promise<my_container> my_promise;
typedef std::future<my_container>  my_future;

// [PL] Funkcja wątkowa wypełnia kontener i go zwraca.
// [EN] The tread function fills a container and returns it.
void function (my_promise & ob, const int Max)
{
   std::osyncstream(std::cout) << "START (" << Max << ")" << std::endl;
   my_container l;
   for (int i = 0; i < Max; ++i)
      l.push_back(i);
   // [PL] Do obietnicy się pisze. [EN] You write into a promise.
   ob.set_value(l);  // [PL] Zapisz wynik do obietnicy. | [EN] Store the result into a promise.
   std::osyncstream(std::cout) << "END   (" << Max << ")" << std::endl;
}

// [PL] Zwraca wartość losową.
// [EN] Returns a random value.
std::size_t random_value ()
{
   const std::size_t mini {  100 };  
   const std::size_t Maxi { 2000 }; 

   static std::default_random_engine engine (std::chrono::system_clock::now().time_since_epoch().count());
   static std::uniform_int_distribution<std::size_t> distribution (mini, Maxi);
   return distribution(engine);
}

////////////////////////////////////
int main()
{
   const int number_of_threads {5};

   // [PL] Do obietnicy się pisze. [EN] You write into a promise.
   std::vector<my_promise> my_promises(number_of_threads);
   // [PL] Z przyszłości się czyta. [EN] You read from a future.
   std::vector<my_future> my_futures;

   for (std::size_t i = 0; i < number_of_threads; ++i)
   {
      // [PL] połączenie obietnicy (pisania) i przyszłości (czytania)
      // [EN] match a promise (writing) and a future (reading)
      my_futures.push_back(my_promises[i].get_future());
   }

   std::vector<std::jthread> threads;
   for (std::size_t i = 0; i < number_of_threads; ++i)
   {
      // [PL] Uruchom funkcje w wątkach.
      // [EN] Start functions in threads.
      threads.push_back(std::jthread(function, std::ref(my_promises[i]), random_value()));
   }

   std::vector<my_container> results;
   for (std::size_t i = 0; i < number_of_threads; ++i)
   {
      // [PL] Z przyszłości się czyta. [EN] You read from a future.
      results.push_back(my_futures[i].get());
   }

   // [PL] Wypisz wyniki. [EN] Printd the results.
   std::cout << "[PL] wyniki | [EN] results" << std::endl;
   for (std::size_t i = 0; i < number_of_threads; ++i)
   {
      std::cout << results[i].size() << std::endl;
   }

   return 0;

   // [PL] std::jthread nie wymaga join, std::thread wymaga.
   // [EN] std::jthread does not need to join and std::thread does.
   for (std::size_t i = 0; i < number_of_threads; ++i)
   {
      threads[i].join();
   }

   return 0;
}
////////////////////////////////////

