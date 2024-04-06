/** [PL] Przykład użycia biblioteki std::filesystem.
 *  [EN] An example of application of the std::filesystem library.
 *  @author Krzysztof Siminski
 *  @date 2024-04-06
 */ 

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace ksi
{
   /** [PL] Funkcja wypisuje rekurencyjnie katalog.
    *  [EN] The function prints the directory recursively.
    */ 
   void print_contents (const std::filesystem::path & directory, const int indent = 0)
   {
      std::filesystem::directory_iterator iterator (directory);
      for (auto & f : iterator)
      {
         int in = indent;
         while (in--)
            std::cout << "\t";

         std::cout << f.path().filename() << std::endl; // [PL] tylko nazwa bez ścieżki | [EN] only name without path
         if (f.is_directory())
         {
            print_contents (f.path(), indent + 1);
         }
      }
   }
}

/////////////////////////////////////////////
int main ()
{
   std::filesystem::path current {"."};

   std::cout << std::endl;
   std::cout << "---------------------------------------------" << std::endl; 
   std::cout << "[PL] zawartosc katalogu:    " << current << std::endl;
   std::cout << "[EN] contents of directory: " << current << std::endl;
   std::cout << "---------------------------------------------" << std::endl; 

   std::filesystem::directory_iterator iterator (current);
   for (auto & f : iterator)
   {
      std::cout << f << std::endl;
   }

   std::cout << std::endl;
   std::cout << "----------------------------" << std::endl; 
   std::cout << "[PL] konstrukcja sciezki"    << std::endl;
   std::cout << "[EN] construction of a path" << std::endl;
   std::cout << "----------------------------" << std::endl; 

   std::filesystem::path new_txt_file_path = current;
   std::cout << new_txt_file_path << std::endl;

   std::filesystem::path new_directory {"test"};
   new_txt_file_path /= new_directory;
   std::cout << new_txt_file_path << std::endl;

   std::filesystem::path nested_directory {"nested"};
   new_txt_file_path /= nested_directory;
   std::cout << new_txt_file_path << std::endl;

   std::filesystem::path new_text_file {"file.txt"};
   new_txt_file_path /= new_text_file;
   std::cout << new_txt_file_path << std::endl;

   std::filesystem::path new_log_file {"file.log"};
   std::filesystem::path new_log_file_path = current / new_directory / nested_directory / new_log_file;
   std::cout << new_log_file_path << std::endl;

   std::cout << std::endl;
   std::cout << "----------------------------" << std::endl; 
   std::cout << "[PL] utworzenie folderu"      << std::endl;
   std::cout << "[EN] creation of a directory" << std::endl;
   std::cout << "----------------------------" << std::endl; 

   std::filesystem::path nested_directory_path = current / new_directory / nested_directory;
   if (std::filesystem::exists(nested_directory_path))
   { 
      std::cout << "[PL] Folder "    << nested_directory_path << " istnieje." << std::endl;
      std::cout << "[EN] Directory " << nested_directory_path << " exists."   << std::endl;
   }
   else
   { 
      std::cout << "[PL] Folder "    << nested_directory_path << " nie istnieje."   << std::endl;
      std::cout << "[EN] Directory " << nested_directory_path << " does not exist." << std::endl;
   }

   std::filesystem::create_directories(nested_directory_path);
   std::cout << "- - - - - -" << std::endl;

   if (std::filesystem::exists(nested_directory_path))
   { 
      std::cout << "[PL] Folder "    << nested_directory_path << " istnieje." << std::endl;
      std::cout << "[EN] Directory " << nested_directory_path << " exists."   << std::endl;
   }
   else
   { 
      std::cout << "[PL] Folder "    << nested_directory_path << " nie istnieje."   << std::endl;
      std::cout << "[EN] Directory " << nested_directory_path << " does not exist." << std::endl;
   }

   std::cout << std::endl;
   std::cout << "------------------------------" << std::endl; 
   std::cout << "[PL] wlasnosci folderu"         << std::endl;
   std::cout << "[EN] properties of a directory" << std::endl;
   std::cout << "------------------------------" << std::endl; 

   std::cout << "exists() :        " << std::boolalpha << std::filesystem::exists(nested_directory_path) << std::endl
      << "absolute(path) :  " << std::filesystem::absolute(nested_directory_path) << std::endl
      << "relative_path() : " << nested_directory_path.relative_path() << std::endl
      << "parent_path() :   " << nested_directory_path.parent_path() << std::endl
      << "filename() :      " << nested_directory_path.filename() << std::endl
      << "stem() :          " << nested_directory_path.stem() << std::endl
      << "extension() :     " << nested_directory_path.extension() << std::endl;

   std::cout << std::endl;
   std::cout << "----------------------------" << std::endl; 
   std::cout << "[PL] wlasnosci pliku"         << std::endl;
   std::cout << "[EN] properties of a file"    << std::endl;
   std::cout << "----------------------------" << std::endl; 

   std::ofstream file (new_log_file_path);

   std::cout << "exists() :        " << std::boolalpha << std::filesystem::exists(new_log_file_path) << std::endl
      << "absolute(path) :  " << std::filesystem::absolute(new_log_file_path) << std::endl
      << "relative_path() : " << new_log_file_path.relative_path() << std::endl
      << "parent_path() :   " << new_log_file_path.parent_path() << std::endl
      << "filename() :      " << new_log_file_path.filename() << std::endl
      << "stem() :          " << new_log_file_path.stem() << std::endl
      << "extension() :     " << new_log_file_path.extension() << std::endl;

   std::cout << std::endl;
   std::cout << "-------------------------------------------------------------------" << std::endl; 
   std::cout << "[PL] zawartosc katalogu " << current << " i jego podkatalogow"       << std::endl;
   std::cout << "[EN] contents of directory " << current << " and its subdirectories" << std::endl;
   std::cout << "-------------------------------------------------------------------" << std::endl; 

   ksi::print_contents(current);

   std::cout << std::endl;
   std::cout << "---------------------------------------------" << std::endl; 
   std::cout << "[PL] usuniecie utworzonych plikow i folderow"    << std::endl;
   std::cout << "[EN] removal of created files and directories" << std::endl;
   std::cout << "---------------------------------------------" << std::endl; 

   std::filesystem::remove (new_log_file_path);
   std::filesystem::remove (new_txt_file_path);
   std::filesystem::remove_all (new_directory); // [PL] usun niepusty folder | [EN] remove non empty directory

   ksi::print_contents(current);

   return 0;
}

