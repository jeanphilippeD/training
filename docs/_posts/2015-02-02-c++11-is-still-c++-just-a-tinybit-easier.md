---
title:  "C++11 is still C++ just a tiny bit easier (JP 02/02/2015)"
---

# C++11 is still C++ just a tiny bit easier
**(JP 02/02/2015 originally presented with supporting slides from Herb Sutter Back To Basics)**

Go through some of the C++11 feature and look at how it should impact our coding:
* Limited impact on how to write function and objects (Move is generally automatic).
* Biggest impact: We can now return big types instead of passing them as non const pointer or reference.
* Parameter as const reference is still the strongly preferred default.
* const pointer and reference are still the preferred way to give argument to function without ownership.


## Supporting material: CppCon 2014: Herb Sutter "Back to the Basics! Essentials of Modern C++ Style"
* [Back to the basics slides](https://github.com/CppCon/CppCon2014/blob/master/Presentations/Back%20to%20the%20Basics!%20Essentials%20of%20Modern%20C%2B%2B%20Style/Back%20to%20the%20Basics!%20Essentials%20of%20Modern%20C%2B%2B%20Style%20-%20Herb%20Sutter%20-%20CppCon%202014.pdf)
* [Video CppCon 2014: Herb Sutter "Back to the Basics! Essentials of Modern C++ Style" 1h40min](https://www.youtube.com/watch?v=xnqTKD8uD64)

### Some Highlights
* Using pointers:
  * [http://youtu.be/xnqTKD8uD64?=12m8s From 12m8s until 28m22s(Page 5-6)]
    * Use reference and raw pointer for non owning pointer as function arguments
  * [http://youtu.be/xnqTKD8uD64?t=22m59s From 22m59s until 28m22s (Page 9-10)]
    * How to safely pointer from shared_ptr without risking dangling pointer
 
* Passing/ returning arguments
  * [http://youtu.be/xnqTKD8uD64?t=51m5s From 51m5s until 59m (after that advance tools to avoid unless you write STL or Boost)(Page 22, 23, 24)]
    * C++98 still mostly good default: Use return by value more often but don't overuse pass by value
  * [http://youtu.be/xnqTKD8uD64?t=57m32s From 57m32s until 59m]
    * Summary table('''Page 23/24)'''=> C++98 vs C++11/14  guideline for passing an returning values
    * Mostly the same, just more case of returning by value

### Conclusion
* C++11 code will look a lot like C++98, do not throw away your good habits.
* Good benefit of C++11 move semantic is to make good looking code that return by value more efficient.


-----
Presented at [IndigoVision](https://www.indigovision.com) during a training session on 02/02/2015 with supporting slides from Herb Sutter.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons Licence" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This <span xmlns:dct="http://purl.org/dc/terms/" href="http://purl.org/dc/dcmitype/Text" rel="dct:type">work</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://jeanphilipped.github.io/training/" property="cc:attributionName" rel="cc:attributionURL">Jean-Philippe DUFRAIGNE</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
