# [PL] ciekawostki, nowinki w C++ [EN] fun facts, novelties in C++

any 
---
[PL] Przykład użycia `std::any`. Porównaj z przykładem `variant and visit`.

[EN] An example of usage of `std::any`. Compare with the example `variant and visit`.

concepts
--------
[PL] przykład użycia konceptów

Implementacja operatora << dla różnych kontenerów. 
Koncepty precyzują, który szablon będzie użyty dla klasy-argumentu.

[EN] example of application of concepts

Implementation of the operator << for different containers.
The concepts specify which template will be used for an argument class.

coroutines
----------
[PL] Przykłady użycia korutyn.

Przykłady `co_return`, `co_yield` i `co_await` mają pełną implementację własnego typu `promise_type`.
Przykład `generator` korzysta z gotowego typu `std::generator` (C++23).

[EN] Examples of usage of coroutines.

Examples of `co_return`, `co_yield` and `co_await` have a full implementation of their own `promise_type`.
The `generator` example uses the ready-made type `std::generator` (C++23).

### coroutine-co_yield

[PL] Przykład generowania liczb pierwszych przy użyciu korutyn i `co_yield`.

[EN] An example of generating prime numbers using coroutines and `co_yield`.

### coroutine-co_return 

[PL] Przykład użycia korutyn i `co_return` do zwracania wartości z funkcji asynchronicznej.

[EN] An example of using coroutines and `co_return` to return a value from an asynchronous function.

### coroutine-co_await 

[PL] Rozwinięcie przykładu z `co_return` o `co_await` do oczekiwania na zakończenie funkcji asynchronicznej (wątku).

[EN] An extension of the example with `co_return` with `co_await` to wait for the completion of an asynchronous function (thread).

### coroutine-generator

[PL] Przykład generatora liczb z wykorzystaniem `std::generator` (C++23) i `co_yield`.

[EN] An example of a number generator using `std::generator` (C++23) and `co_yield`.

decorator-lambda
----------------
[PL] Funkcja lambda opakowująca inną przekazaną funkcję. 

[EN] Lambda function wrapping another function.

dynamic and static polymorphism 
-------------------------------
[PL] Ten sam problem rozwiązny za pomocą polimorfizmu dynamicznego (wirtualne metody w hierarchii klas) i polimorfizmu statycznego (szablony klas). 

[EN] The same problem solved with dynamic polimorphism (virtual method in a class hierarchy) and static polimorphism (class templates).

filesystem
----------

[PL] Przykład użycia biblioteki `std::filesystem`.

[EN] An example of application of the `std::filesystem` library.

futures
-------

[PL] Przykład użycia `std::future` i wątków. Porównaj z przykładem `promise and future`.

[EN] An example of usage of `std::future` and threads. Compare with the example `promise and future`.

hashing
-------
[PL] Przykłady haszowania.

[EN] Examples of hashing.

inheritance vs composition
--------------------------

[PL] Ten sam problem rozwiązany przez dziedziczenie i przez kompozycję. 

Dziedzieczenie:
Głęboka hierarchia klas sprawia pewne problemy, np. przy wielu metodach
trudno może być znaleźć, która implementacja metody jest wywoływana.

Kompozycja: 
Zamiast implementować metody w klasach pochodnych, jest jedna klasa, która 
jest zbudowana z obiektów implementujących odpowiednią wersję metody.
W poniższych przykładzie zastosowane jest odwrócenie zależności
i dostęp do składowych poprzez interfejsy. Zamiast dziedziczenia
mamy kompozycję i realizację interfejsów. 

[EN] The same problem solved using inheritance and composition.

Inheritance:
A deep class hierarchy causes certain issues; for example, with many methods,
it can be difficult to find which implementation of a method is being called.

Composition:
Instead of implementing methods in derived classes, there is a single class
built from objects that implement the appropriate version of the method.
The example below uses dependency inversion and accesses members
through interfaces. Instead of inheritance, we have composition
and interface implementation.

literals
--------

[PL] Przykład literałów w bibliotekach `chrono`, `string`, `string_view`, `complex` i własnych literałów.

[EN] An example of literals in the libraries `chrono`, `string`, `string_view`, `complex`, and user-defined literals.

matrix traversal
----------------
[PL] Porównanie czasu zsumowania elementów macierzy przy przechodzeniu wierszami i kolumnami.  

[EN] Comparision of element summing with row-wise and column-wise matrix traversal.

optional 
--------
[PL] Przykład użycia `std::optional`. 

[EN] An example of the `std::optional`.

promise and future
------------------
[PL] Przykład użycia obietnicy (`std::promise`) i przyszłości (`std::future`). Porównaj z przykładem `futures`.

[EN] An example of an `std::promise` and an `std::future`. Compare with the example `futures`.

ranges and views
----------------
[PL] Trochę przykładów zakresów i widoków (ranges and views). 

[EN] Some examples of ranges and views

ratio
-----
[PL] Metaprogramowanie: przykład użycia biblioteki arytmetyki stosunków liczb całkowitych `std::ratio`. 

[EN] Metaprogramming: an example of application of compile-time rational arithmetic library `std::ratio`.

regex
-----
[PL] Przykład użycia wyrażeń regularnych (`std::regex`).

[EN] An example of usage of regular expressions (`std::regex`).

variant and visit
-----------------
[PL] Przykład użycia `std::variant` i `std::visit`. Porównaj z przykładem `any`.

[EN] An example of usage of `std::variant` and `std::visit`. Compare with the example `any`.


