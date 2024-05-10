## 2D Physics Simulation

![Screenshot from 2024-05-10 16-18-19](https://github.com/mehmetSuzer/PhysSim/assets/93345336/31f7e8cd-2820-4bc8-b585-f8b62981378b)

In this project, Verlet integration is used since it is a fast and easy to implement.
Particles are initialized in a pool. Therefore, if you want to use more of them, you should use a larger pool that can support your needs.

Particles can be trapped in a constraint which may have the following shapes:

1. Circle (Closed)
2. Rectangle (Closed)
3. Ellipse (Closed)
4. Arc (Open)

Particles cannot go out of a closed constraint. 
On the other hand, an open constraint has a free part where particles can pass.
Arc is the only open constraint for now. 
Be aware that constraints prevent particles from going out, not coming in. 
I am planning to implement it in the future.

An event controller is setup to deal with user inputs. 
In the main function, first particle is selected as the controllable particle.
A user can move it in 4 directions. 
Default keys are WASD.
In addition, the constraint can be rotated in CW and CCW directions. 
Defaults keys are J (CCW), K (STOP), and L (CW).

I cannot imagine a good physics simulation without a music. The following song is used in the simulation:

"Sappheiros - Embrace" is under a Creative Commons license (CC BY 3.0) \
https://www.youtube.com/c/Sappheiros \
Music promoted by BreakingCopyright: https://bit.ly/embrace-song

Those who want can turn on/off the music. 
The default key for it is M (ON), N (OFF).
All commands are configurable. You can assign different keys to commands. 

Enjoy.
