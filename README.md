    <div style="text-align: center;"> 
    ![ACG Logo](https://static.wikitide.net/binrayarchiveswiki/f/fe/ACGlogo.png)
    </div>

# <p align=center>ACGSSE
Welcome to the: ***A Clicker Gaem: Sega Saturn Edition*** Repository!

A Clicker Gaem: Sega Saturn Edition (or A Clicker Gaem) is a game made for the ***Sega Saturn*** using the [***Saturn Ring Library (SRL)***](https://github.com/ReyeMe/SaturnRingLib), and is meant to be the continuation of the *A Clicker Gaem Scratch Series that lasted from 2021-2023*. </p>

## <p align=center> Building </p>
**NOTE**: ***This only works for Visual Studio Code (VSC)!***

### SetUp
1. Put ACGSSE into the SRL *Projects* Directory!

### SRL Patch
*Before Compiling, you need to do a small patch to SRL!*

1. Go to 'SRLDIR/modules/SaturnMathPP/impl/fxp.hpp' (SRLDIR being the Saturn Ring Library Directory)
2. Then, Go to line *134* or search for *'consteval Fxp(const T& value) : value(value * 65536.0) {}'*
3. Replace *consteval* to *constexpr*, this is so I can change Fxp values (like position) during run time!

### Compiling
Run one of the premade build tasks (Ctrl+Shft+B) to compile (either Debug or Release)
