/** [PL] Przykład literałów w bibliotekach `chrono`, `string`, `string_view`, `complex` i własnych literałów.
 *  [EN] An example of literals in the libraries `chrono`, `string`, `string_view`, `complex`, and user-defined literals.  
 *  @author Krzysztof Siminski
 *  @date 2024-06-01
 */ 

#include <chrono>
#include <complex>
#include <iostream>
#include <cstring>     // for strlen(char *)
#include <string>      // for std::string 
#include <string_view> // for std::string_view

/////////////////////////////////////////////

// [PL] literały zdefiniowane przez użytkownika
// [EN] user-defined literals 


// [PL] literał przeliczający kelwiny na stopnie Celsjusza
// [EN] a literal for conversion of kelvins into degrees Celsius 
constexpr double operator""_K (long double k)
{
   return k - 273.15; 
}

// [PL] literał przeliczający stopnie Fahrenheita na stopnie Celsjusza
// [EN] a literal for conversion of degrees Fahrenheit into degrees Celsius 
constexpr double operator""_F (long double f)
{
   return 5.0 * (f - 32.0) / 9.0;
}

/////////////////////////////////////////////
int main ()
{
   {
      // [PL] literały dla jednostek czasu 
      // [EN] literals for time units 
      // #include <chrono>

      using namespace std::literals::chrono_literals;

      std::cout << "--------------" << std::endl;
      std::chrono::day DayOK (12d);
      std::cout << DayOK << std::endl;
      std::chrono::day DayWrong (67d); // [PL] niepoprawny numer dnia | [EN] incorrect day number
      std::cout << DayWrong << std::endl;
      std::cout << "--------------" << std::endl;

      std::chrono::year YearOK (2024y);
      std::cout << YearOK << std::endl;
      std::chrono::year YearWrong (37000y); // [PL] niepoprawny rok | [EN] incorrect year
      std::cout << YearWrong << std::endl;

      std::cout << "--------------" << std::endl;

      {
         // [PL] 1.5 h w różnych formatach | [EN] 1.5 h in various formats
         std::chrono::duration<double, std::ratio<3600>> lecture_h (1.5h);
         std::cout << lecture_h << std::endl; // [PL] 1.5 h w godzinach | [EN] 1.5 h in hours
         std::chrono::duration<double, std::ratio<60>> lecture_min (1.5h);
         std::cout << lecture_min << std::endl;// [PL] 1.5 h w minutach | [EN] 1.5 h in minutes 
         std::chrono::duration<double, std::ratio<1>> lecture_s (1.5h);
         std::cout << lecture_s << std::endl;// [PL] 1.5 h w sekundach | [EN] 1.5 h in seconds
      }
      std::cout << "--------------" << std::endl;
      {
         // [PL] 90 min w różnych formatach | [EN] 90 min in various formats
         std::chrono::duration<double, std::ratio<3600>> lecture_h (90min);
         std::cout << lecture_h << std::endl; // [PL] 90 min w godzinach | [EN] 90 min in hours
         std::chrono::duration<double, std::ratio<60>> lecture_min (90min);
         std::cout << lecture_min << std::endl; // [PL] 90 min w minutach | [EN] 90 min in minutes
         std::chrono::duration<double, std::ratio<1>> lecture_s (90min);
         std::cout << lecture_s << std::endl; // [PL] 90 min w sekundach | [EN] 90 min in seconds
         std::chrono::duration<double, std::ratio<1,1000>> lecture_ms (90min);
         std::cout << lecture_ms << std::endl; // [PL] 90 min w milisekundach | [EN] 90 min in milliseconds
         std::chrono::duration<double, std::micro> lecture_us (90min);
         std::cout << lecture_us << std::endl; // [PL] 90 min w mikrosekundach | [EN] 90 min in microseconds
         std::chrono::duration<double, std::kilo> lecture_k (90min);
         std::cout << lecture_k << std::endl; // [PL] 90 min w kilosekundach | [EN] 90 min in kiloseconds
      }
      std::cout << "--------------" << std::endl;
      {
         // [PL] 3.14 milisekund w różnych formatach | [EN] 3.14 milliseconds in various formats
         std::chrono::duration<double, std::ratio<3600>> impulse_h (3.14ms);
         std::cout << impulse_h << std::endl; // [PL] 3.14 ms w godzinach | [EN] 3.14 ms in hours
         std::chrono::duration<double, std::ratio<60>> impulse_min (3.14ms);
         std::cout << impulse_min << std::endl; // [PL] 3.14 ms w minutach | [EN] 3.14 ms in minutes
         std::chrono::duration<double, std::ratio<1>> impulse_s (3.14ms);
         std::cout << impulse_s << std::endl; // [PL] 3.14 ms w sekundach | [EN] 3.14 ms in seconds
         std::chrono::duration<double, std::ratio<1,1000>> impulse_ms (3.14ms);
         std::cout << impulse_ms << std::endl; // [PL] 3.14 ms w milisekundach | [EN] 3.14 ms in milliseconds
         std::chrono::duration<double, std::micro> impulse_us (3.14ms);
         std::cout << impulse_us << std::endl; // [PL] 3.14 ms w mikrosekundach | [EN] 3.14 ms in microseconds
         std::chrono::duration<double, std::kilo> impulse_k (3.14ms);
         std::cout << impulse_k << std::endl; // [PL] 3.14 ms w kilosekundach | [EN] 3.14 ms in kiloseconds
      }
   }

   std::cout << "==============" << std::endl;
   {
      // [PL] literały dla liczb zespolonych 
      // [EN] literals for complex numbers 
      
      // #include <complex>

      using namespace std::complex_literals;

      std::complex<double> x (3.14, -2.72);
      std::cout << x << std::endl;

      std::complex<double> y = -2.3 + 9.4i;
      std::cout << y << std::endl;
   }

   std::cout << "==============" << std::endl;
   {
      // [PL] literały dla łańcuchów znakowych 
      // [EN] literals for strings 

      // #include <string>  // for std::string 

      using namespace std::literals; // or using namespace std::string_literals;
                                     // using namespace std::string_literals;
      auto text_char = "To be of not to be.";  // char * 
      auto text_str  = "To be of not to be."s; // std::string 

      std::cout << "char *,           length: " << strlen(text_char) << ": " << text_char << std::endl;
      std::cout << "std::string,      length: " << text_str.length()    << ": " << text_str  << std::endl;

      // #include <string_view>

      using namespace std::literals;

      // [PL] '\0' kończy łańcuch char * 
      // [EN] '\0' ends a char * string 
      std::string_view view_from_char_array  = "prefix\0suffix";   // string_view from an array of characters, '\0' null char

      // [PL] '\0' nie kończy string_view 
      // [EN] '\0' does not end a string_view 
      std::string_view view_from_string_view = "prefix\0suffix"sv; // string_view from a string_view 

      std::cout << "std::string_view, length: " << view_from_char_array.length()  << ": " << view_from_char_array  << std::endl;
      std::cout << "std::string_view, length: " << view_from_string_view.length() << ": " << view_from_string_view << std::endl;
   }

   std::cout << "==============" << std::endl;
   {
      // [PL] literały zdefiniowane przez użytkownika
      // [EN] user-defined literals 

      double absolute_zero = 0.0_K; 
      std::cout << absolute_zero << " C" << std::endl;

      double summer = 88.5_F;
      std::cout << summer << " C" << std::endl;
   }
   return  0;
}

