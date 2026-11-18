/** [PL] Przykład użycia  przyszłości (std::future).
 *  [EN] An example of  an std::future.
 *  @author Krzysztof Siminski
 *  */

#include <future>
#include <syncstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

////////////////////////////////////
// [PL] Zwraca wartość losową.
// [EN] Returns a random value.
std::size_t get_random_value ()
{
   const std::size_t mini {  100 };  
   const std::size_t Maxi { 5000 }; 

   static std::default_random_engine engine (std::chrono::system_clock::now().time_since_epoch().count());
   static std::uniform_int_distribution<std::size_t> distribution (mini, Maxi);
   return distribution(engine);
}

int long_operation (int n)
{
   auto random_value = get_random_value();
   std::this_thread::sleep_for(std::chrono::milliseconds(random_value)); 

   return n * n; 
}

////////////////////////////////////
int main()
{
   std::cout << "[PL] Przyklad uzycia  przyszkosci (std::future)" << std::endl;
   std::cout << "[EN] An example of an std::future" << std::endl;

   std::cout << "================================" << std::endl;

   {
      std::cout << "[PL] Uruchamiam dlugotrwala operacje w tle..." << std::endl;
      std::cout << "[EN] I am running a long operation in the background..." << std::endl;

      int parameter = 10;
      std::future<int> future = std::async(std::launch::async, long_operation, parameter);

      std::cout << "[PL] Tymczasem moge wykonywac inne operacje..." << std::endl;
      std::cout << "[EN] In the meantime, I can perform other operations..." << std::endl;

      // [PL] Odczytuje wynik długotrwałej operacji.
      // [EN] I read the result of a long operation.

      int value = future.get(); 

      std::cout << "[PL] Wynik dlugotrwalej operacji: " << value << std::endl;
      std::cout << "[EN] The result of a long operation: " << value << std::endl;
   }

   std::cout << "================================" << std::endl;
   {
      int parameter = 15;

      std::cout << "[PL] Uruchamiam " << parameter << " dlugotrwalych operacji w tle..." << std::endl;
      std::cout << "[EN] I am running " << parameter << " long operations in the background..." << std::endl;

      std::vector<std::future<int>> futures;
      int number_of_operations = 5;
      for (int i = 0; i < number_of_operations; ++i)
      {
         futures.push_back(std::async(std::launch::async, long_operation, parameter + i));
      }

      std::cout << "[PL] Tymczasem moge wykonywac inne operacje..." << std::endl;
      std::cout << "[EN] In the meantime, I can perform other operations..." << std::endl;

      // [PL] Odczytuje wynik długotrwałej operacji.
      // [EN] I read the result of a long operation.

      std::vector<int> values; 
      for (int i = 0; i < number_of_operations; ++i)
      {
         values.push_back(futures[i].get()); 
      }

      std::cout << "[PL] Wynik dlugotrwalych operacji: "  << std::endl;
      std::cout << "[EN] The result of long operations: " << std::endl;

      for (int n : values)
      {
         std::cout << n << " ";
      }
      std::cout << std::endl;
   }
   return 0;
}
////////////////////////////////////

