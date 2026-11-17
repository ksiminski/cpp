
#include <coroutine>
#include <iostream>
#include <exception>

/////////////////////////
// [PL] przykład korutyny zwracającej wartości
//      Korutyna to funkcja, która może być wstrzymywana i wznawiana.
// [EN] example of a coroutine returning values 
//      A coroutine is a function that can be suspended and resumed.
/////////////////////////


// [PL] typ zwracany przez korutynę 
// [EN] return type of the coroutine 
template<typename T>
struct Task
{
    // [PL] wymagana struktura promise_type
    // [EN] required promise_type structure 
    struct promise_type 
    {
        T result; // [PL] miejsce na wartość zwróconą przez co_return | [EN] place for the value returned by co_return 

        // [PL] Metoda tworzy obiekt Task zwracany do wywołującego.
        // [EN] The method creates a Task object returned to the caller.
        Task get_return_object() 
        {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        // [PL] Metoda wywoływana na początku korutyny. 
        //      Definiuje, czy korutyna ma być od razu wstrzymana, czy nie.
        // [EN] The method is called at the beginning of the coroutine. 
        //      It defines whether the coroutine should be suspended immediately or not.
        auto initial_suspend() 
        { 
           return std::suspend_never(); // [PL] nie wstrzymuje korutyny na początku | [EN] does not suspend the coroutine at the beginning
        }

        // [PL] Metoda wywoływana na końcu korutyny. 
        //      Definiuje, czy korutyna ma być wstrzymana na końcu, czy nie.
        // [EN] The method is called at the end of the coroutine.
        //      It defines whether the coroutine should be suspended at the end or not.
        std::suspend_always final_suspend() noexcept 
        { 
           return {}; // [PL] Wstrzymuje korutynę na końcu, żeby nie zniszczyć wyniku.
                      // [EN] Suspends the coroutine at the end not to destroy the result.
        }

        // [PL] Metoda wywoływana, gdy korutyna zwraca wartość (co_return).
        // [EN] The method is called when the coroutine returns a value (co_return).
        void return_value(T value) 
        {
            result = value;
        }

        // [PL] Obsługa nieprzechwyconych wyjątków wewnątrz korutyny.
        // [EN] Handling uncaught exceptions inside the coroutine.
        void unhandled_exception() 
        { 
           std::terminate(); // [PL] kończy program w przypadku nieprzechwyconego wyjątku 
                             // [EN] terminates the program in case of an uncaught exception
        }
    };

    // [PL] Uchwyt pozwalający sterować korutyną z zewnątrz (wznawiać ją i niszczyć).
    // [EN] Handle that allows controlling the coroutine from the outside (resuming and destroying it).
    std::coroutine_handle<promise_type> handle;

   explicit Task(std::coroutine_handle<promise_type> h) : handle(h) 
   {}
    
    // [PL] Destruktor zwalnia pamięć ramki korutyny.
    // [EN] Destructor frees the memory of the coroutine frame.
    ~Task() 
    {
        if (handle) 
            handle.destroy();
    }

    // [PL] Metoda pomocnicza dla użytkownika do pobierania wyniku.
    // [EN] Auxilliary method for the user to get the result.
    T get_result()  const 
    {
        return handle.promise().result;
    }

    bool is_done() const 
    {
        return handle.done();
    }

    void resume() 
    {
       if (not handle.done())
           handle.resume();
    }

};

// [PL] korutyna 
// [EN] coroutine 
Task<double> convert(const double value) 
{
   std::cout << "   [PL] Sprawdzm kursy walut ..." << std::endl;
   std::cout << "   [EN] Checking exchange rates ..." << std::endl;
   std::cout << std::endl;

   // [PL] symulacja pobierania kursów walut z serwera
   // [EN] simulating fetching exchange rates from a server

   co_await std::suspend_always{}; // [PL] wstrzymuje korutynę na tym miejscu | [EN] suspends the coroutine at this point

   double rate = 0.18; // [PL] przykładowy kurs waluty | [EN] example exchange rate
   std::cout << "   [PL] Kursy walut pobrane." << std::endl;                                
   std::cout << "   [EN] Exchange rates fetched." << std::endl;
   std::cout << std::endl;

   co_return value * rate; // [PL] zwraca wynik przeliczenia | [EN] returns the conversion result                       
}

int main() 
{
   std::cout << "[PL] Tworzę korutynę." << std::endl;
   std::cout << "[EN] Creating the coroutine." << std::endl;
   std::cout << std::endl;

   // [PL] Wywołanie korutyny. Korutyna startuje i się wykonuje aż do co_wait.
   // [EN] Calling the coroutine. The coroutine starts and executes until co_wait.
   Task<double> financial_task = convert (123.45);

   std::cout << "[PL] Korutyna wstrzymana. Można wykonać inne zadania." << std::endl;
   std::cout << "[EN] Coroutine suspended. Other tasks can be performed." << std::endl; 
   std::cout << std::endl;

   // [PL] Wznowienie korutyny. Korutyna wykonuje się dalej aż do końca.
   // [EN] Resuming the coroutine. The coroutine continues executing until the end.

   if (not financial_task.is_done())
   {
      std::cout << "[PL] Wznawiam korutynę." << std::endl;
      std::cout << "[EN] Resuming the coroutine." << std::endl;
   std::cout << std::endl;
      financial_task.resume();
   }

   // [PL] Pobranie wyniku z korutyny.
   // [EN] Getting the result from the coroutine.

   double result = financial_task.get_result();
   std::cout << "[PL] Wynik przeliczenia: " << result << std::endl;
   std::cout << "[EN] Conversion result: " << result << std::endl;
   std::cout << std::endl;

   return 0;
}


