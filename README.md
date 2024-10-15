![raycaster image](https://github.com/user-attachments/assets/aad14fa1-1ae4-4677-afdc-14b4e692b326)

The purpose of this porject is to have a foundation for a much larger game project that utilizies Raycasting to it's fullest potential.

I will not spoil what this project will evolve into, because My ideas for the finalized version of this will be. 

However, I need to start small as I'm still learning the ropes on how to be a game dev and program in C++. This has been a Fantastic learning expierence for me! 

Inputs: 
*  No Mouse Button input (yet)

  Movement:
____________________________________________________
*  W:               Move Forward                   
*  S:               Move Backward                  
*  A:               Strafe Left                    
*  D:               Strafe Right                   
*  Left Arrow Key:  Rotate and Look Left           
*  Right Arrow Key: Rotate and Look Right
 __________________________________________________

  Mouse Position:
 __________________________________________________
 There are 3 Basic Raycasts from the Player's position to the mouse Position:
 *  Green Line + Purple Circle: The Green Line represnets the raycast itself and the Purple Circle represents the ray's Hit Position
 *  Yellow Line: This represents the ray's Starting Position (Player Position) and it's ending Position (Mouse Position).
 *  Red Line + Gray Circle: When the player is out of the bounds of the Tile Map, the Ray Caster System is basically disabled as the ray's x and y position are set to 0, 0 (since the source of the Ray is the player, it effectivly becomes the player's x and y position).
 __________________________________________________
