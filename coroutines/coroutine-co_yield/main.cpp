
#include <coroutine>
#include <iostream>
#include <exception>


/////////////////////////
// [PL] przykład korutyny  
//      Korutyna to funkcja, która może być wstrzymywana i wznawiana.
// [EN] example of a coroutine
//      A coroutine is a function that can be suspended and resumed.
/////////////////////////


// [PL] typ zwracany przez korutynę 
// [EN] return type of the coroutine 
struct Generator 
{
    // [PL] wymagana struktura promise_type
    // [EN] required promise_type structure 
    struct promise_type 
    {
        int current_value = 0; // [PL] przechowuje aktualną wartość | [EN] stores the current value

        // [PL] Metoda tworzy obiekt Generator zwracany do wywołującego.
        // [EN] The method creates a Generator object returned to the caller.
        Generator get_return_object() 
        {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        // [PL] Metoda wywoływana na początku korutyny. 
        //      Definiuje, czy korutyna ma być od razu wstrzymana, czy nie.
        // [EN] The method is called at the beginning of the coroutine. 
        //      It defines whether the coroutine should be suspended immediately or not.
        auto initial_suspend() 
        { 
           return std::suspend_always(); // [PL] wstrzymuje korutynę na początku | [EN] suspends the coroutine at the beginning
           // return std::suspend_never(); // [PL] nie wstrzymuje korutyny na początku | [EN] does not suspend the coroutine at the beginning
        }

        // [PL] Metoda wywoływana na końcu korutyny. 
        //      Definiuje, czy korutyna ma być wstrzymana na końcu, czy nie.
        // [EN] The method is called at the end of the coroutine.
        //      It defines whether the coroutine should be suspended at the end or not.
        std::suspend_always final_suspend() noexcept 
        { 
           return {}; 
        }

        // [PL] Metoda wywoływana, gdy korutyna zwraca wartość (co_yield).
        // [EN] The method is called when the coroutine returns a value (co_yield).
        std::suspend_always yield_value(int value) 
        {
            current_value = value;
            return {}; // [PL] Zawiesza korutynę po zapisaniu wartości.
                       // [EN] Suspends the coroutine after saving the value.
        }

        // [PL] Metoda wywoływana, gdy korutyna kończy się bez wartości (co_return lub koniec funkcji).
        // [EN] The method is called when the coroutine ends without a value (co_return or end of function).
        void return_void() 
        {}

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

   explicit Generator(std::coroutine_handle<promise_type> h) : handle(h) 
   {}
    
    // [PL] Destruktor zwalnia pamięć ramki korutyny.
    // [EN] Destructor frees the memory of the coroutine frame.
    ~Generator() 
    {
        if (handle) 
            handle.destroy();
    }

    // [PL] Metoda pomocnicza dla użytkownika do pobierania kolejnych liczb.
    // [EN] Auxilliary method for the user to get the next numbers.
    bool get_next_value() 
    {
        if (not handle || handle.done()) 
           return false;
        handle.resume(); // [PL] Wznawia korutynę aż do kolejnego co_yield lub końca.
                         // [EN] Resumes the coroutine until the next co_yield or end.
        return not handle.done();
    }

    int value() const 
    {
        return handle.promise().current_value;
    }
};

// [PL] korutyna 
// [EN] coroutine 
Generator count_down(int start) 
{
    while (start > 0) 
    {
        co_yield start; // [PL] Wywołuje promise.yield_value(start) i zawiesza funkcję.
                        // [EN] Calls promise.yield_value(start) and suspends the function.
        start--;
    }
    co_return; // [PL] Wywołuje promise.return_void() i kończy funkcję. Nie musi tego być.
               // [EN] Calls promise.return_void() and ends the function. It does not have to be there.

    // [PL] Jeżeli nie będzie co_return, to koniec funkcji niejawnie wywołuje promise.return_void().
    // [EN] If co_return is absent, the end of the function implicitly calls promise.return_void(). 
}

int main() 
{
    // [PL] Wywołanie korutyny. Dzięki initial_suspend() jeszcze nie wykonuje pętli.
    // [EN] Calling the coroutine. Thanks to initial_suspend() it does not execute the loop yet.
    Generator gen = count_down(10);
    // [PL] W tym momencie alokowana jest ramka korutyny. 
    //      W niej jest umieszczany obiekt promise_type.
    //      Następnie zwracany jest obiekt Generator, który przechowuje uchwyt do ramki korutyny.
    // [EN] At this point, the coroutine frame is allocated.
    //      The promise_type object is placed in it.
    //      Then, a Generator object is returned, which holds a handle to the coroutine frame.

    // [PL] Kompilator wywołuje initial_suspend(), która zwraca std::suspend_always, więc korutyna jest wstrzymana.
    // [EN] The compiler calls initial_suspend(), which returns std::suspend_always, so the coroutine is suspended.
    
    // [PL] Ręczne wznawianie korutyny krok po kroku.
    // [EN] Manually resuming the coroutine step by step.
    
    // [PL] Metoda get_next_value() uruchamia resume() w uchwycie do korutyny.
    //      Korutyna wykonuje się aż do kolejnego co_yield lub końca funkcji.
    // [EN] The get_next_value() method calls resume() on the coroutine handle.
    //      The coroutine executes until the next co_yield or the end of the function.
    while (gen.get_next_value()) 
    {
        std::cout << gen.value() << " "; // [PL] Wyświetla aktualną wartość przechowywaną w promise_type.
                                         // [EN] Displays the current value stored in promise_type.
    }
    // [PL] Po zakończeniu pętli w korutynie wywoływana jest metoda final_suspend(), 
    //      która zwraca std::suspend_always, więc korutyna jest wstrzymana.
    //      Dzięki temu handle.done() zwraca true.
    // [EN] After the loop ends, the final_suspend() method is called in the coroutine,
    //      which returns std::suspend_always, so the coroutine is suspended.
    //      Thanks to this, handle.done() returns true.
    std::cout << std::endl;

    // [PL] Destruktor Generator() wywołuje handle.destroy(), który zwalnia pamięć ramki korutyny.
    // [EN] The Generator() destructor calls handle.destroy(), which frees the memory of the coroutine frame.

    return 0;
}


