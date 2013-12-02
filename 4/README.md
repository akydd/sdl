# Key Presses

## Changes
No changes from the original, other than those applied in the previous tutorial.

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
#### Entity Manager System (world.c)
Contains entities and their components, and defines methods for creating and
destroying them.
#### Input System (input\_system.c)
Only contains method that operates on the Entity Manager System based on input.
#### Render system (renderer.c)
The render system is responsible for drawing entities having a graphics
component onto the screen.  It interfaces with the cache system, below.
#### Cache system (cache,c)
The cache system takes care of loading and fetching SDL\_Textures.
