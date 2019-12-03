# online-cpp-libface
An online of the data structures presented in duckduckgo/cpp-libface. It was done for my pregrade thesis.

Compile
=======
```bash
cd src/
g++ -std=c++11 -O4 -DACMTUYO main.cpp
```

Run
===
```bash
./a.out dataset.txt
```


```bash
./a.out dataset.txt < commands.txt
```

Use
===
- Add new entries to the dictionary 
```
A keword weight
```

- Update an entry in the dictionary 
```
U keyword weight
```

- Query top K entries with that `prefix`
```
Q prefix K
```

**NOTE**: Actually it only accept uppercase `keyword` and `prefix`
