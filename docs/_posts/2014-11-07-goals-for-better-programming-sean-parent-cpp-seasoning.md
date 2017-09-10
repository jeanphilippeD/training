---
title:  "Goals For Better Programming : Sean Parent C++ Seasoning (JP 07/11/2014)"
---

# Goals For Better Programming : Sean Parent C++ Seasoning
**(JP 07/11/2014 originally presented this taster for the talk with supporting slides from Sean Parent C++ Seasoning)**

## Supporting material: Going Native 2013:Sean Parent "C++ Seasoning"
* [C++ Seasoning slides](https://github.com/sean-parent/sean-parent.github.com/wiki/presentations/2013-09-11-cpp-seasoning/cpp-seasoning.pdf)
* [Video Going Native 2013:Sean Parent "C++ Seasoning"](http://channel9.msdn.com/Events/GoingNative/2013/Cpp-Seasoning)

## Some Highlights
Goals:
* No Raw Loops
* No Raw Synchronization Primitives
* No Raw Pointers (No even unique or shared pointer: Use value types)

Why? Locality of reasoning:
* Easier to reason about
* Composable, General, Correct, Efficient

Striving with the 'no raw loops' goal:
* Know the standard algorithms (and boost ones too).
* Use algorithm to explicit what your code is doing.
* Isolate new algorithm from business logic:
  * Improve readability with proper names
  * Improve reusability / testability
* Look at Sean Parent's example with std::rotate

## Look for simple example improvments in own code base
```c++

// Fail the 'No raw loop' goal
bool HasValidProperty( const Object& object )
{
  //
  // See if object's property is currently in use.
  //
  const auto objectProp = GetObjectProperty( object );
  for( const auto& prop : CurrentProperties() )
  {
    if ( prop == objectProp )
    {
      return true;
    }
  }
  return false;
}

// Achieve the 'No raw loop' goal
bool HasValidProperty( const Object& object )
{
  return boost::algorithm::any_of_equal(
    CurrentProperties(),
    GetObjectProperty( object ) );
}
```


-----
Presented at [IndigoVision](https://www.indigovision.com) during a training session on 07/11/2014 with supporting slides from Sean Parent.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons Licence" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This <span xmlns:dct="http://purl.org/dc/terms/" href="http://purl.org/dc/dcmitype/Text" rel="dct:type">work</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://jeanphilipped.github.io/training/" property="cc:attributionName" rel="cc:attributionURL">Jean-Philippe DUFRAIGNE</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
