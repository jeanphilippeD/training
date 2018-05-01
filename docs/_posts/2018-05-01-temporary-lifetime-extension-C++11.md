---
title:  "Temporary lifetime extension in C++11 (01/05/2018)"
---

# Temporary lifetime extension in C++11
**(JP 01/05/2018 originally presented during a live coding of the supporting code using catch2)**

Temproraries are often created when returning from a function.
A temprorary lifetime ends when the expression ends: [CPP Reference: Lifetime](http://en.cppreference.com/w/cpp/language/lifetime)

Since C++11, when assigning a temporary to a const reference, its lifetime will be extended to be the lifetime of the reference.
This can be great to avoid copy, but can lead to dangling references:
* Assigning to const reference is safe if the assigned value is:
  * A temporary.
  * A reference to an object, or reference to a member of an object whose lifetime will outlive the new reference. 
* Assigning to const reference is unsafe if the assigned value is:
  * A reference to a temporary object, or reference to a member of a temporary object whose lifetime will not outlive the reference.

Alternatively, these can be used as paramter to functions:
* Because any temporary's lifetime will ends after the function is called (end of the expression), chaining functions will be safe whether they return reference or temproraries.
* It can be dangerous though as a trivial but incorrect refactoring will make this code unsafe (i.e a reference to temporary is assigned to a named const reference).
* The safe refactoring would be to assign to a const value even if this create a possible copy.

Examples of problematic code:
* const auto& ref = GetCollection().at(0);
* const auto* ptr = GetString().c_str();

[Sample code](https://github.com/jeanphilippeD/training/tree/master/docs/_posts/samples/LifeTime)
```c++
{% include_relative samples/LifeTime/test.cpp %}
```


-----
Presented at [IndigoVision](https://www.indigovision.com) during a training session on 01/05/2018.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons Licence" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This <span xmlns:dct="http://purl.org/dc/terms/" href="http://purl.org/dc/dcmitype/Text" rel="dct:type">work</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://jeanphilipped.github.io/training/" property="cc:attributionName" rel="cc:attributionURL">Jean-Philippe DUFRAIGNE</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
