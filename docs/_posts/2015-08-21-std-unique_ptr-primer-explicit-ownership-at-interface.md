---
title:  "std::unique_ptr primer: explicit ownership at interface (21/08/2015)"
---

# std::unique_ptr primer: explicit ownership at interface
**(JP 21/08/2015 originally presented reviewing an interface improvment in real code)**

In C++98, memory management is mostly a matter of convention: There is no difference between an owning pointer that needs to be deleted, and a non owning pointer that should not be deleted when it is not longer used.

C++11 introduced std::shared_ptr and std::unique_ptr to address this issue.
* unique_ptr should be prefered to shared_ptr when shared ownership is not required.
* unique_ptr needs to be used instead of shared_ptr when ownership transfer is required.

Because of its responsibility of being a unique owner, std::unique_ptr is can only be moved and not copied.
This can make its use cumbersome.

We will see an example of API doing transfer of ownership using unique_ptr.
This example show how the call sites are dramatically improved and classic memory managment error are eliminated.


[Sample code](https://github.com/jeanphilippeD/training/tree/master/docs/_posts/samples/ExplicitMemoryManagmentAtInterfaceWithUniquePtrDemo)
```c++
{% include_relative samples/ExplicitMemoryManagmentAtInterfaceWithUniquePtrDemo/interfacewithuniqueptrdemo.cpp %}
```


-----
Presented at [IndigoVision](https://www.indigovision.com) during a training session on 21/08/2015.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons Licence" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This <span xmlns:dct="http://purl.org/dc/terms/" href="http://purl.org/dc/dcmitype/Text" rel="dct:type">work</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://jeanphilipped.github.io/training/" property="cc:attributionName" rel="cc:attributionURL">Jean-Philippe DUFRAIGNE</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
