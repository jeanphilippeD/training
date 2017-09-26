---
title:  "C++11 struct and class: Part 1 Non-resource (20/06/2017)"
---

# C++11 struct and class: Part 1 Non-resource
**(JP 20/06/2017 originally presented during a live coding of the supporting code)**

**Writing a C++11 struct:**
* A struct is by convention an aggregate of public variables: There is no invariant
* A struct should have neither hand-rolled constructors nor destructor
* C++11 allow for well-behaved struct without constructor:
  * Either use well-behaved members
  * Use built-in members with in-class initialization
* These structs can be initialized with aggregate initialization (using initializer list)
* Semi Regular vs Regular
  * By default these are semi-regular types (miss operator == and !=, may miss default construction, copy or move depending on member types)
  * They can be made regular with a adding operator == and != (as hand-rolled inlined friend or [using C++14/17 library techniques](https://github.com/apolukhin/magic_get))


**Writing a non-resource class:**
* A class is by convention an object in which member variables hold a specific invariant
* A non-resource struct should have neither hand-rolled default constructor nor destructor
* C++11 allow for well-behaved class using generated default constructor:
  * Either use well-behaved members
  * Use built-in members with in-class initialization
* These class constructor can be invoked using initializer list
* Use 'explicit' to constrain implicit conversion (generally not desirable)
  * On constructors with single argument (conversion constructors)
  * On conversion operators
  * explicit can be used on every constructors to avoid implicit conversion from initializer list, but this is not recommended
* Semi Regular vs Regular
  * By default these are semi-regular types (miss operator == and !=, may miss default construction, copy or move depending on member types)
  * They can be made regular with a adding operator == and != (as hand-rolled inlined friend or [using C++14/17 library techniques](https://github.com/apolukhin/magic_get) if organized as nested struct)


[Sample code](https://github.com/jeanphilippeD/training/tree/master/docs/_posts/samples/Cpp11ResourceStructClass)
```c++
{% include_relative samples/Cpp11ResourceStructClass/non_resource.cpp %}
```


-----
Presented at [IndigoVision](https://www.indigovision.com) during a training session on 20/06/2017.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons Licence" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This <span xmlns:dct="http://purl.org/dc/terms/" href="http://purl.org/dc/dcmitype/Text" rel="dct:type">work</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://jeanphilipped.github.io/training/" property="cc:attributionName" rel="cc:attributionURL">Jean-Philippe DUFRAIGNE</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
