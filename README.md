# ACGSSE
Welcome to the: ***A Clicker Gaem: Sega Saturn Edition*** Repository!

A Clicker Gaem: Sega Saturn Edition (or A Clicker Gaem) is a game made for the ***Sega Saturn*** using the [***Saturn Ring Library (SRL)***](https://github.com/ReyeMe/SaturnRingLib), and is meant to be the continuation of the *A Clicker Gaem Scratch Series that lasted from 2021-2023*.

# Building
(***This only works for VSC***)

First, Put ACGSSE into the SRL *Projects* Directory!

***(IMPORTANT!!!)*** before building, go to fxp.hpp (*SRLDIR/modules/SaturnMathPP/impl/fxp.hpp*), then line ***134*** (or until you see *"consteval Fxp(const T& value) : value(value * 65536.0) {}"*), then replace consteval with constexpr so the game can build.

Then, just run one of build tasks to compile!
