---
title:  "C++11 struct and class: Part 2 Resource (27/06/2017)"
---

# C++11 struct and class: Part 2 Resource
**(JP 27/06/2017 originally presented during a live coding of the supporting code)**

**Writing a resource class:**
* A class is by convention an object in which member variables hold a specific invariant
* A resource class will have ([Rule of 3/5](http://en.cppreference.com/w/cpp/language/rule_of_three)):
  * hand-rolled destructor
  * hand-rolled copy constructor and operators deleted or given proper semantic
* A resource class may have:
  * hand-rolled constructors (or =default)
  * [move constructor](http://en.cppreference.com/w/cpp/language/move_constructor) and operators given proper semantic (make the class easier to use (like std::unique_ptr vs boost::scoped_ptr))
* C++11 allow for well-behaved class using generated default constructor:
  * Either use well-behaved members
  * Use built-in members with in-class initialization
* Semi Regular vs Regular
  * By default these are non-regular type (cannot copy or compare)
  * They can be made semi-regular types with default construction, and copy constructor & operator
  * They can be made regular with a adding operator == and !=


[Sample code](https://github.com/jeanphilippeD/training/tree/master/docs/_posts/samples/Cpp11ResourceStructClass)

Non Movable:
```c++
{% include_relative samples/Cpp11ResourceStructClass/resource_non_movable.cpp %}
```


Movable:
```c++
{% include_relative samples/Cpp11ResourceStructClass/resource_movable.cpp %}
```


Semi-Regular:
```c++
{% include_relative samples/Cpp11ResourceStructClass/resource_semi_regular.cpp %}
```


Regular:
```c++
{% include_relative samples/Cpp11ResourceStructClass/resource_regular.cpp %}
```


-----
Presented at [IndigoVision](https://www.indigovision.com) during a training session on 27/06/2017.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons Licence" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This <span xmlns:dct="http://purl.org/dc/terms/" href="http://purl.org/dc/dcmitype/Text" rel="dct:type">work</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://jeanphilipped.github.io/training/" property="cc:attributionName" rel="cc:attributionURL">Jean-Philippe DUFRAIGNE</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
