# edge-trigger

Attach callbacks to rising and falling edges of a variable.

**C++17 is required.**

## Usage

```c++
#include "edge_trigger.hpp"
```

given a variable `var`: pass the variable as the first argument, and for non-booleans a threshold pair as the second and third arguments. 

attach callbacks to the rising and falling edges with the `on_rising` and `on_falling` methods.

```c++
  bool var;
  auto et = edge_trigger<bool>(var)
                .on_rising([]() { std::cout << "Rising edge\n"; })
                .on_falling([]() { std::cout << "Falling edge\n"; });
                
  for (;;) {
    // do something
    et.update();
  }
```

```c++
  int var;
  auto et = edge_trigger<int>(var, 10, 20)
                  .on_rising([]() { std::cout << "Rising edge\n"; })
                  .on_falling([]() { std::cout << "Falling edge\n"; });
  for (;;) {
    // do something
    et.update();
  }
```

for custom types, as long as the type has `operator<` and `operator>` defined, the `edge_trigger` class should work.