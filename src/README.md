Compile
=======
```bash
g++ -std=c++0x main.cpp
```

Run
===
```bash
./a.out ../dataset/big/bigDataSet.txt


Data Structure builded using ../dataset/big/bigDataSet.txt file.
204812 strings builded in 183 milliseconds.

Queries format:
Q PREFIX K
Example:
Q HELL 5

Add format:
A STRING VALUE
Example:
A HELL 1232

Update format:
U STRING VALUE
Example:
U HELL 8765
>
```
