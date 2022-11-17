# TestMatch

## Description
Involves the creation of a Social Manager to handle friends' connection status,
Using (for now) 3 components:
* Services: working as component inside GameMode, handle Friends DataTable loading 
* Social: another component attached to the PlayerController, gets notified via a Service delegate.
* SocialOverlay: a simple UserWidget inside the ScreenHUD grouping all sub-widgets regarding friends status.
* If you want a fast population of the initial friends list uncomment the line 28 in SocialComponent.cpp

```
//FriendsDataCache = ReFillDataCache(ATMGameMode->Services->ProvideFriendsData());
```

###Developed with Unreal Engine 5
------------

### Tasks Breakdown
- [x] 1> ~~Prepare and Fillup  a Mockup DataTable with all Fields to be included: 6h~~
 - ~~Avatar pic.~~
 - ~~Nickname.~~
 - ~~Level.~~
 - ~~Achievements amount.~~
 - ~~bIsConnected.~~


 - [x] 2> ~~Create an intermediary Controller or “View-model” class to connect the Widgets (view) with the Model (DataTable) the simplest option seems to create an ActorComponent Class & attach it to the Character. **6H**~~
- ~~consider inside PlayerController, GameInstance or using a GameState Component as a better option (Need some research to grasp it) **+6H.**~~


 - [x] 3> ~~(Un)Connected Lists Widget Creation.~~
	* ~~Widget Skeleton **6H.**~~
	* ~~(Widget Logic (DataTable query) **12H.**~~


 - [x] 4> ~~Add the fold/unfold Feature for each list with the proper button control. **6h.**~~


 - [x] 5> ~~Create Timer Simulation. Randomly Update Source table  with Friends  availability & Notify Our Controller class **12H.**~~


 - [ ] 6> Create Toast Widget, which pops up when a friend gets connected & fade out after a while. **9H.**


- [ ] 7> Create Widget Tooltip showing Friends information when player hovers over the friend list items. **9H**


- [x] 8> ~~Take care of list update everytime friends status change Related with “5” ** 6H.**~~


- [ ] 9> Create Additional animations to improve user experience.
 * Fold/Unfolding.
 * List fade-in.
 * Toast popup fade in/out.
 * Etc.


- [ ] 10> Check the implementation of a local basic pool of widgets in case of not using the listviews. **12H?**


- [ ] 11> Make sure that key parts are handled on native side C++ and expose events to BP’s to handle tasks that technical artist should work later. **6~12H?**


- [x] 12> ~~Avoid direct View – model communication skipping the control class.~~


