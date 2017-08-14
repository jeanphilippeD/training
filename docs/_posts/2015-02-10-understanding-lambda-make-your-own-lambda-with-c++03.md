---
title:  "Understanding lambda: Make your own lambda with C++03 (10/02/2015)"
---

# Understanding lambda: Make your own lambda with C++03
**(JP 10/02/2015 originally presented during a live coding of the supporting code)**

* When to use lambda, rough guidelines:
  * Unnamed lambda: very short, obvious and not reused.
  * Named as local variable: similar constraint to a function, used only in one function.
  * Otherwise, prefer function or function objects that can be called from anywhere.

By using lambda in your code, you will find yourself writing more function objects as well, they are still a very powerful tool.

[Sample code](https://github.com/jeanphilippeD/training/tree/master/docs/_posts/samples/LambdaDemo)
```c++
{% include_relative samples/LambdaDemo/lambdademo.cpp %}
```


-----
Presented at [IndigoVision](https://www.indigovision.com) during a training session on 10/02/2015.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons Licence" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This <span xmlns:dct="http://purl.org/dc/terms/" href="http://purl.org/dc/dcmitype/Text" rel="dct:type">work</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://jeanphilipped.github.io/training/" property="cc:attributionName" rel="cc:attributionURL">Jean-Philippe DUFRAIGNE</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
