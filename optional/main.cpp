/** [PL] Przykład użycia std::optional.
 *  [EN] An example of the std::optional.
 *  @author Krzysztof Siminski
 *  @date 2024-04-23
 */ 

#include <iostream>
#include <limits>
#include <limits>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

/////////////////////////////////

void numbers()
{
   std::cout << "-------------------" << std::endl;
   std::cout << "NUMBERS" << std::endl; 

   // [PL] Funkcja zwraca wartość typu double zapisaną jako tekst. Jeżeli test nie jest liczbą, zwraca pusty optional.
   // [EN] The function parses a string and returns a double. If the text is not a double, it returns an empty optional.
   auto correct_value = [] (const std::string & s) -> std::optional<double>
   {
      try 
      {
         return std::stof(s);
      }
      catch (...)
      {
         return std::nullopt;
      }
      return std::numeric_limits<double>::quiet_NaN(); 
   };

   // [PL] Funkcja przycina wartości do 1 od góry i do zera od dołu.
   // [EN] The function cuts a value to fit the [0, 1] interval.
   auto cut = [] (const double d) -> std::optional<double>
   {
      if (d > 1)
         return 1.0;
      else if (d < 0)
         return 0.0;
      else 
         return d;
   };

   
   std::vector<std::string> values { "0.456", "-45.4", "1.23", "0.541", "many", "two", "0.71"   };

   for (const auto & s : values)
   {
      std::cout << "\"" << s << "\"" << "\t" ;

      double value = 
         // [PL] Sprawdź, czy poprawna wartość. 
         //      Jeżeli niepoprawna, zwróć pusty optional (std::nullopt).
         // [EN] Test if correct value. 
         //      If incorrect, return an empty optional (std::nullopt).
         correct_value(s)
         // [PL] Jeżeli poprawna, przytnij.
         //      Jeżeli niepoprawna, zwróć pusty optional (std::nullopt).
         // [EN] If correct, cut.
         //      If incorrect, return an empty optional (std::nullopt).
         .and_then(cut)
         // [PL] Jeżeli jest wartość, zwróć ją; w przeciwnym razie: -1.
         // [EN] If correct value, return it, otherwise return -1. 
         .value_or(-1);

      std::cout << value << std::endl; 
   }
}

///////////////////////////
void persons()
{
   std::cout << "-------------------" << std::endl;
   std::cout << "PERSONS" << std::endl; 

   // [PL] Trzy „bazy danych” przechowujące wiek osób. | [EN] Three “data bases” with ages of persons.
   std::unordered_map<std::string, int> list_1
   {
      {"John", 19},
         {"Anne", 23},
         {"David", 26},
         {"Helen", 18}
   };
   std::unordered_map<std::string, int> list_2
   {
      {"Dago", 29},
         {"Thym", 25},
         {"Alda", 19},
         {"Haela", 21},
         {"Fran", 16}
   };

   std::unordered_map<std::string, int> list_3
   {
      {"Majk", 23},
         {"Dajk", 26},
         {"Bajk", 21},
         {"Naik", 20},
         {"Xajk", 15}
   };

   // [PL] Jeżeli osoba jest w bazie, funkcja zwraca jej wiek. W przeciwnym razie zwraca std::nullopt.
   // [EN] If a person exists in a database, their age is return, otherwise it returns std::nullopt. 
   auto get_cache = [] (const std::unordered_map<std::string, int> & cache, const std::string & name) -> std::optional<int> 
   {
      auto it = cache.find(name);
      if (it == cache.end())
         return std::nullopt;
      else 
         return it->second;
   };

   // [PL] Jeżeli osoba jest wieku studenckim, funkcja zwraca wiek. Jeżeli nie, zwraca std::nullopt.
   // [EN] If a person age is a student's age, the function returns the age. Otherwise -- std::nullopt.
   auto student_age = [] (const int n) -> std::optional<int>
   {
      if (n < 19 or n > 24)
         return std::nullopt;
      else 
         return n;
   };

   // [PL] Funkcja zwraca rok studiów na podstawie wieku osoby.
   // [EN] The function returns a year of study basing on the person's age.  
   auto year = [] (const int n) 
   {
      return n - 18;
   };

   for (const std::string name : {"John", "Chris", "Dago", "Ala", "Naik", "Maik", "Gajk", "Alda", "Bajk"})
   {
      int age = 
         // [PL] Odczytaj z pierwszej bazy wiek zadanej osoby.
         //      Funkcja zwraca std::optional<int>.
         // [EN] Get age of a person with a given name from the first database. 
         //      The function returns std::optional<int>.
         get_cache(list_1, name)
         // [PL] Jeżeli nie było osoby w pierwszej liście (optional jest pusty), czytaj z drugiej,
         // [EN] If the person is missing from the 1st list (the optional is empty), read from the second list.
         .or_else([=]{ return get_cache(list_2, name);})
         // [PL] Jeżeli znowu optional jest pusty, czytaj z trzeciej listy.
         // [EN] If the optional is empty again, read from the third list.
         .or_else([=]{ return get_cache(list_3, name);})
         // [PL] I następnie uruchom funkcję student_age dla osoby. Funkcja zwraca pusty optional (std::nullopt), gdy wiek jest niepoprawny. 
         // [EN] And then call student_age for a person. The function returns an empty optional (std::nullopt) for incorrect age.
         .and_then(student_age)
         // [PL] Przeształć wiek na rok studiów.
         // [EN] Transform the age into a year of studies.
         .transform(year)
         // [PL] Gdy optional nie jest pusty, wzróć tego wartość. W przeciwnym wypadku, zwróć -1. 
         // [EN] If the optional is not empty, return it, otherwise return -1. 
         .value_or(-1);

      std::cout << name << " " << age << std::endl;
   }
}

///////////////////////////
int main()
{
   numbers();
   persons();
}

