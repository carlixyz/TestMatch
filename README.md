# TestMatch

Involves the creation of a Social Manager to handle friends' connection status
Using (for now) 3 components:
	- Services: working as component inside GameMode, handle Friends DataTable loading 
	- Social: another component attached to the PlayerController, gets notified via a Service delegate.
	- SocialOverlay: a simple UserWidget inside the ScreenHUD grouping all sub-widgets regarding friends status.

* Developed with Unreal Engine 5
