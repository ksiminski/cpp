/** [PL] Przykład użycia wyrażeń regularnych (std::regex).
 *  [EN] An example of application of regular expressions (std::regex).
 *  @author Krzysztof Siminski
 *  @date 2024-06-19
 */ 

#include <fstream>
#include <iostream>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>



// [PL] Funkcja wczytuje całość pliku do łańcucha znakowego. 
// [EN] The function reads the whole file into a string. 
std::string read_file (const std::string & file_name)
{
   std::ifstream file (file_name);
   if (file)
   {
      std::stringstream sos;
      sos << file.rdbuf();
      return sos.str();
   }
   return {};
}

/////////////////////////////////////////////
int main ()
{
   // [PL] std::regex_match dopasowuje cały napis. 
   // [EN] std::regex_match matches the whole string. 
   {
      std::cout << "=======================" << std::endl;
      std::cout << "[PL] dopasowanie wzorca" << std::endl;
      std::cout << "[EN] pattern match"      << std::endl;
      std::cout << "std::regex_match"        << std::endl;
      std::cout << "=======================" << std::endl;
      std::cout << std::endl;

      std::vector<std::string> words {"read_me.md", "text.txt", "main.cpp", "regex.cpp", "regex.h", "train_test.cpp", "ten.txt", "then.txt", "than.txt" };

      {
         std::cout << "cpp files" << std::endl;
         std::cout << "---------" << std::endl;
         std::regex regex {".*\\.cpp"};  // [PL] plik z rozszerzeniem cpp | [EN] file with cpp extention
         for (const auto word : words)
         {
            if (std::regex_match(word, regex))
               std::cout << word << std::endl;
         }
         std::cout << std::endl;
      }
      {
         std::cout << "txt files" << std::endl;
         std::cout << "---------" << std::endl;
         std::regex regex {".*\\.txt"}; // [PL] plik z rozszerzeniem cpp | [EN] file with cpp extention
         for (const auto word : words)
         {
            if (std::regex_match(word, regex))
               std::cout << word << std::endl;
         }
         std::cout << std::endl;
      }
      {
         std::cout << R"(files with '_')" << std::endl;
         std::cout <<   "--------------" << std::endl;
         std::regex regex {".*_.*"};// [PL] plik z podreślnikiem | [EN] file with an underscore
         for (const auto word : words)
         {
            if (std::regex_match(word, regex))
               std::cout << word << std::endl;
         }
         std::cout << std::endl;
      }
      {
         std::cout << "th?en files" << std::endl;
         std::cout << "-----------" << std::endl;
         std::regex regex {"th?en\\..*"};// [PL] plik z nazwą ten lub then | [EN] file with name ten or then
         for (const auto word : words)
         {
            if (std::regex_match(word, regex))
               std::cout << word << std::endl;
         }
         std::cout << std::endl;
      }
      {
         std::cout << "th[ae]n files" << std::endl;
         std::cout << "-------------" << std::endl;
         std::regex regex {"th[ae]n\\..*"};// [PL] plik z nazwa than lub then | [EN] file with name than or then
         for (const auto word : words)
         {
            if (std::regex_match(word, regex))
               std::cout << word << std::endl;
         }
         std::cout << std::endl;
      }
   }

   // [PL] użycie wyrażenia regularnego jako filtra dla widoku
   // [EN] regex as a filter for a view  
   {
      std::vector<std::string> words {"read_me.md", "text.txt", "hamlet.txt", "main.cpp", "regex.cpp", "regex.h", "train_test.cpp", "ten.txt", "then.txt", "than.txt" };

      {
         std::cout << "--------------------------" << std::endl;
         std::regex regex {".*\\.cpp"};
         auto range = std::views::all(words) | std::views::filter([regex](const std::string & word) 
               { return std::regex_match(word, regex); });
         for (const auto word : range)
            std::cout << word << std::endl;
      }
   }

   // [PL] wczytanie całego pliku do następnych przykładów 
   // [EN] read the whole file for the following examples  
   const std::string file_name {"main.cpp"};
   const std::string text = read_file(file_name);

   std::cout << "======================" << std::endl;
   std::cout << "[PL] wyszukanie wzorca" << std::endl;
   std::cout << "[EN] pattern search"    << std::endl;
   std::cout << "std::regex_search"      << std::endl;
   std::cout << "======================" << std::endl;
   std::cout << std::endl;
   {
      std::cout << "--------------------------" << std::endl;
      std::cout << "[PL] wyszukanie \"string\" | [EN] search for \"string\""  << std::endl;

      std::regex regex {"string"};
      if (std::regex_search(text, regex))
      {
         std::cout << "\"string\" found!" << std::endl;
      }
   }

   {
      std::cout << "--------------------------" << std::endl;
      std::cout << "[PL] wyszukanie słowa z prefiksem \"str\" | [EN] search for aword with \"str\" prefix"  << std::endl;
      std::cout << std::endl;

      std::regex regex {"str.*"};
      std::smatch pattern_match;

      if (std::regex_search(text, pattern_match, regex))
      {
         for (const auto m : pattern_match)
            std::cout << m << std::endl;
      }
   }
   {
      std::cout << "--------------------------" << std::endl;
      std::cout << "[PL] wyszukanie wszystkich słów | [EN] search for all words"  << std::endl;
      std::cout << std::endl;

      std::regex regex {"std::[a-z]*"};
      std::smatch pattern_match;
      std::string copy = text;
      while (std::regex_search(copy, pattern_match, regex))
      {
         for (const auto m : pattern_match)
            std::cout << m << std::endl;
         copy = pattern_match.suffix(); // [PL] wyszukaj w pozostałym tekscie | [EN] search in the remaining text 
      }

      std::cout << std::endl;
   }
   {
      std::cout << "--------------------------" << std::endl;
      std::cout << "[PL] wyłuskanie podwzorców | [EN] subpattern extraction" << std::endl;
      std::cout << std::endl;

      std::regex regex {"(regex_)([a-z]+)"};
      std::smatch pattern_match;
      std::string copy = text;
      while (std::regex_search(copy, pattern_match, regex))
      {
         std::cout << "pattern: " << pattern_match[0] << std::endl;
         for (std::size_t i = 1; i < pattern_match.size(); ++i)
         {
            std::cout << "   subpattern: " << pattern_match[i] << std::endl;
         }
         copy = pattern_match.suffix(); 
      }

      std::cout << std::endl;
   }
   {
      std::cout << "--------------------------" << std::endl;
      std::cout << "[PL] wyłuskanie podwzorców | [EN] subpattern extraction" << std::endl;
      std::cout << std::endl;

      std::regex regex {"(std::string)([ ]+)([a-z]+)"};
      std::smatch pattern_match;
      std::string copy = text;
      std::cout << "std::string variables:" << std::endl;
      while (std::regex_search(copy, pattern_match, regex))
      {
         std::cout << pattern_match[3] << std::endl;
         copy = pattern_match.suffix(); 
      }

      std::cout << std::endl;
   }
   {
      std::cout << "--------------------------" << std::endl;
      std::cout << "[PL] zamiana | [EN] replacement" << std::endl;
      std::cout << std::endl;

      std::string hamlet = "To be or not to be.";      
      {
         std::regex regex {"be"}; 
         std::cout << std::regex_replace(hamlet, regex, "sing") << std::endl;
      }
      {
         std::regex regex {R"([a-z]+)"}; 
         std::cout << std::regex_replace(hamlet, regex, "[$&]") << std::endl;
         // [PL] $& jest dopasowanym napisem
         // [EN] $& is the matched string
      }

      std::cout << std::endl;
   }
   {
      std::cout << "--------------------------" << std::endl;
      std::cout << "[PL, EN] std::sregex_iterator" << std::endl;
      std::cout << std::endl;

      std::regex regex {"(std::regex_)([a-zA-Z0-9]+)"}; // one line comment 
      std::string copy = text;      // copy the text 
      auto matched_patterns = std::sregex_iterator(copy.begin(), copy.end(), regex);

      // [PL] Świeżo skonstruowany std::sregex_iterator ma wartość end.
      // [EN] Freshly constructed std::sregex_iterator has end value.
      for (std::sregex_iterator it = matched_patterns; it != std::sregex_iterator(); ++it)
      {
         std::cout << it->str() << std::endl;
      }

      std::cout << std::endl;
   }
   {
      std::cout << "--------------------------" << std::endl;
      std::cout << "[PL] wyrażenia regularne ECMA i POSIX | [EN] ECMA and POSIX regexes" << std::endl;
      std::cout << std::endl;

      std::string copy = R"(abc <p> in first p </p> def <p> in second p </p> ghi)"; 
      std::regex regex_ecma  {"<p>.*?</p>"}; // ECMA syntax 
      std::regex regex_posix {"<p>.*?</p>", std::regex::extended}; // POSIX syntax 

      std::smatch s;
      std::regex_search(copy, s, regex_ecma);
      std::cout << "ECMA (depth first) : [" << s[0] << "]" << std::endl;
      std::regex_search(copy, s, regex_posix);
      std::cout << "POSIX (greedy)     : [" << s[0] << "]" << std::endl;

      std::cout << std::endl;
   }
   return 0;
}

