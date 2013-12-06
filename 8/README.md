# Geometry Rendering

## Changes
No changes other than those previously mentioned.

## Entity Component System
In our implementation, each key press destroys all existing entities and creates
a new one.  This could be modified to create a single entity upon first
keypress, updating it with subsequent keypresses.

### Entities
An entity is simply an integer, which indexes into the entities' components and
mask field.  The mask field tracks which components are attached to the
entity.

### Components
#### Graphic
The graphic component holds the filename for the components image file.
#### Position
This component holds the x and y coordinate of the entity.  For graphic
components, this is the upper left corner location.
#### Size
Holds the height and width dimensions of the entity.  For entites that are also
graphics, this is the size of the bounding box.
#### Color
Holds the rgba values for color
#### Line
Holds the starting and ending (x,y) coordinates.

### Systems
#### Entity Manager System (world.c)
Contains entities and their components, and defines methods for creating and
destroying them.
#### Input System (input\_system.c)
Only contains method that operates on the Entity Manager System, creating and
destroying entities, based on user input.
#### Render system (renderer.c)
The render system is responsible for drawing entities (those with textures and
primitives, such as points, lines, rectangles) onto the screen.  If an entity has a size, position, or color components, these
are also taken into account where appropriate.  Graphic components without size and position
components are stretched to
cover the entire window.  This system interfaces with the cache system, below.
#### Cache system (cache.c)
The cache system takes care of loading and fetching SDL\_Textures.
