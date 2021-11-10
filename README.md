# UniversalNoRecoil
Mouse script to simulate a No Recoil Cheat

### Example
![image](https://i.ibb.co/18P0ph2/ezgif-com-gif-maker.gif)

**FEATURES**

There are 3 presets , only 1 can be selected at a time. (use numpad 1-3)
> 1. Close Range
> 2. Medium Range
> 3. Long Range
_a tone will sound to let you know the patch is active_

_as a safety precaution there is the option to require ADS , toggle the flag with "INSERT" (Enabled by default)_

**NOTE**: At any time you can press END to remove the patch and close the application entirely

## Compiling Instructions
C# => Clone and build

C++ => When cloning make sure to put all files in the same directory , everything is in folders for organization purposes only.

Customize recoil presets by changing the integers within the **Recoil Events** in MAIN.CPP or MAIN.CS
> 1. `_UniCoil(*, *);`
> 2. `_flaggedCOIL(*, *);`
> 3. `helpers._uniCoilF(keyLMB, *, *);`
> 4. `helpers._uniCoil(keyRMB, keyLMB, *, *);`
