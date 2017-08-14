---
title:  "Understanding ADL: Argument dependent lookup with logging (26/06/2015)"
---

# Understanding ADL: Argument dependent lookup with logging
**(JP 26/06/2015 originally presented during a live coding of the supporting code using BOOST_LOG_TRIVIAL)**

ADL is there to enable working with namespaces seamlessly.
What it means is that the set of overload for a function will include the overloads
* Defined in the namespace the argument types are defined in.
* Defined in the namespace the template parameter of the argument types are defined in.
* Many more obscure rules.
* For Example:
  * look for overload in std for std::vector, std::set, std::pair.
  * look for overload in geo for geo::Point, geo::Circle, std::vector< geo::Point > ...
  * look for overload in the global namespace for object defined in the global namespace.
  * For built in types, no extra overload are added.

[Sample code](https://github.com/jeanphilippeD/training/tree/master/docs/_posts/samples/AdlDemo)
```c++
{% include_relative samples/AdlDemo/adldemo.cpp %}
```


-----
Presented at [IndigoVision](https://www.indigovision.com) during a training session on 26/06/2015.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons Licence" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This <span xmlns:dct="http://purl.org/dc/terms/" href="http://purl.org/dc/dcmitype/Text" rel="dct:type">work</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://jeanphilipped.github.io/training/" property="cc:attributionName" rel="cc:attributionURL">Jean-Philippe DUFRAIGNE</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
