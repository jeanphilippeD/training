---
title:  "Tips for writing maintainable tests (JP 31/01/2017)"
---

# Tips for writing maintainable tests
**(JP 31/01/2017 originally presented with real test refactor)**

Having tests is a pre-requisite for improving them so having imperfect tests is always better than not having test.

Having well factored test allow for easier maintenance, so when writing test we should strive for the following:

* Use sub functions in your tests, in particular, for top level test function (the one registered in test suite) we should:
  * Make simple to read
  * Keep as short as possible
  * Focus on the 'What' and 'Why'
  * Use named function to implement 'How' if it reduce clarity (member or free function)
* Use member initialized/destroyed in setup/teardown:
  * Hide common initialization code
  * Provide helper member variable for often used varialble
* Use AAA(Arrange/Act/Assert) Pattern:
  * This constrains tests to some simplicity that allow future reader to:
    * Understand the intent
    * Understand the scope of the tests, and potential gaps in testing
    * Update them
  * Regular structure also speed up reading/understanding
  

-----
Presented at [IndigoVision](https://www.indigovision.com) during a training session on 31/01/2017 with supporting code change to our internal code base.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons Licence" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This <span xmlns:dct="http://purl.org/dc/terms/" href="http://purl.org/dc/dcmitype/Text" rel="dct:type">work</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://jeanphilipped.github.io/training/" property="cc:attributionName" rel="cc:attributionURL">Jean-Philippe DUFRAIGNE</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
