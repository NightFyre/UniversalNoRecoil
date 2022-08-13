# UniversalNoRecoil
<p align="center">
<img src="https://i.ibb.co/18P0ph2/ezgif-com-gif-maker.gif">
</p>

## FEATURES
There are 3 presets , only 1 can be selected at a time. (use numpad 1-3)
> 1. Close Range
> 2. Medium Range
> 3. Long Range

*a tone will sound to let you know the patch is active*  
*as a safety precaution there is the option to require ADS , toggle the flag with "INSERT" (Enabled by default)*  
*At any time you can press END to remove the patch and close the application entirely*

## Console Version Compiling Instructions
**C#**: Clone and build  
**C++**: When cloning make sure to put all files in the same directory , everything is in folders for organization purposes only.

Customize recoil presets by changing the integers within the **Recoil Events** in MAIN.CPP or MAIN.CS
> 1. `_UniCoil(*, *);`
> 2. `_flaggedCOIL(*, *);`
> 3. `helpers._uniCoilF(keyLMB, *, *);`
> 4. `helpers._uniCoil(keyRMB, keyLMB, *, *);`

## WARNING
Having this program running while ModernWarfare, Warzone, BOCW or Vanguard running will result in an immediate ban whether or not you use it.  
Any program running which uses Dear ImGui will typically automatically ban you while those games are running.  
If you would like to use this program on any of the mentioned games , I suggest you use the console app as they do not detect it.  
They detect strings in Dear ImGui and I have no intention of making this version of ImGui sig proof. That is not what this repository is for.  
You have been warned, Do not bother me with your ban complaints because you used a cheat.
