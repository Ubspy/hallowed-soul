# Defect Tracking

We used two different methods to keep track of bugs and assign the fixing of them. The most useful was probably our ordinary meeting minutes,
because that was where members could bring up any and every issue they saw, the team could take care of assigning fixes as part of the
timeline, and every meeting we checked in to see if last meeting's bugs had been fixed. We also kept excellent records of meetings and
referred to these records often when completing our work. As a secondary method, we had a Discord channel for reporting bugs.

In addition to these two sources, our code review was a valuable source of defects. Some defects listed are also from the code review.

### Spawning waves takes too long

* Reported by: Andrew Lauderback
* Reported on: 10-29-2021
* Assignee: Andrew Lauderback
* Fixed on: 11-02-2021
* Fix: Random Number Generator was being initialized with a new seed every generation, which is slow. Use one seed for the duration of the game.

### Player flies off the screen when dodging

* Reported by: Jack Moren
* Reported on: 10-29-2021
* Assignee: Jack Moren
* Fixed on: 11-11-2021
* Fix: Continue decelerating when space key is released.

### Loose camera view glitches on map borders

* Reported by: Andrew Riachi
* Reported on: 10-29-2021
* Assignee: Andew Riachi
* Fixed on: 11-11-2021
* Fix: Don't use loose camera view; strictly place player in center of screen

### Enemy hit indicators display for wrong amount of time

* Reported by: Hayden Myers
* Reported on: 11-09-2021
* Assignee: Hayden Myers
* Fixed on: 
* Fix: 

### Getting unit vectors and getting vector magnitude should be utility functions

* Reported by: Jack Moren
* Reported on: 11-04-2021
* Assignee: Jack Moren
* Fixed on: 11-09-2021
* Fix: Wrote VectorUtil class

### Ammo is unused by the Entity class

* Reported by: Jack Moren
* Reported on: 11-04-2021
* Assignee: 
* Fixed on: 
* Fix: 

### Texture of entities should be set by a setter function

* Reported by: Jack Moren
* Reported on: 11-04-2021
* Assignee: Jack Moren
* Fixed on: 11-09-2021
* Fix: Created a setter function

### No Game Over Screen

* Reported by: Jack Moren
* Reported on: 11-04-2021
* Assignee: Hayden Myers
* Fixed on: 11-17-2021
* Fix: Make a game over screen

### Enemies may not be deleted when Wave is deleted

* Reported by: Jack Moren
* Reported on: 11-04-2021
* Assignee: Hayden Myers
* Fixed on: 11-11-2021
* Fix: Call `endWave()` in WaveManager destructor

### GameManager cluttered with UI code

* Reported by: Jackson Morphew
* Reported on: 11-09-2021
* Assignee: Jackson Morphew
* Fixed on: 11-11-2021
* Fix: Make a UIManager class

### Enemies attack too slow

* Reported by: Andrew Lauderback
* Reported on: 11-16-2021
* Assignee: Andrew Lauderback
* Fixed on: 11-18-2021
* Fix: Decrease the interval between enemy attacks

### Player health bar should be more clear that it's the player's health bar

* Reported by: Jackson Morphew
* Reported on: 11-09-2021
* Assignee: Jackson Morphew
* Fixed on: 11-16-2021
* Fix: Add a little heart by the health bar to show it's a health bar

### Hit indicators display "40" instead of actual damage value done

* Reported by: Hayden Myers
* Reported on: 11-11-2021
* Assignee: Hayden Myers
* Fixed on: 11-18-2021
* Fix: Randomize attack damage under GameManager, that way this damage value can be passed to hit indicator

### Attack Animations do not play

* Reported by: Andrew Riachi
* Reported on: 11-15-2021
* Assignee: Andrew Riachi
* Fixed on: 11-16-2021
* Fix: Use break statements inside switch statements so that animation states are properly discriminated

### Attack animation is not smooth for Enemies

* Reported by: Andrew Riachi
* Reported on: 11-17-2021
* Assignee: 
* Fixed on: 
* Fix: 

### Enemies can attack from above you at very large ranges

* Reported by: Andrew Lauderback
* Reported on: 11-12-2021
* Assignee: Jack Moren
* Fixed on: 11-17-2021
* Fix: Check if player is within attack range before dealing damage

### High score does not display on death screen

* Reported by: Hayden Myers
* Reported on: 11-18-2021
* Assignee: Andrew Riachi
* Fixed on: 11-18-2021
* Fix: Refactor `drawDeathScreen()` to display the right variable

### Corrupted highscore.txt not handled gracefully by the game

* Reported by: Hayden Myers
* Reported on: 11-18-2021
* Assignee: Andrew Riachi
* Fixed on: 11-18-2021
* Fix: Check the ifstream failbit when reading the high score. If it is set, use a default high score value and overwrite the file.

### Test suite does not run many of the written tests

* Reported by: Andrew Lauderback
* Reported on: 11-18-2021
* Assignee: Andrew Lauderback
* Fixed on: 11-18-2021
* Fix: Put the written tests in the top-level runTests() method.

### New player sprites animate too fast when attacking

* Reported by: Jack Moren
* Reported on: 11-18-2021
* Assignee: Andrew Riachi
* Fixed on: 11-18-2021
* Fix: Make `getSecondsPerFrame()` a virtual method that can be overridden by player, allowing us to define a longer period of time for which
the frame is shown.