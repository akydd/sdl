# Event Driven Programming

## Changes
No changes other than those previously mentioned in tutorial 2.

## Entity Component System
Our system is simple, since there is no animation involved.
### Entities
An entity is simply an integer, which indexes into the entities' components and
mask field.  The mask field tracks which components are attached to the
entity.

### Components
#### Graphic
The graphic component holds the filename for the components image file.

### Systems
#### Render system
The render system is responsible for drawing entities having a graphics
component onto the screen.  It interfaces with the cache system, below.
#### Cache system
The cache system takes care of loading and fetching SDL\_Textures.
