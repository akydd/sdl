# Getting an Image on the Screen

## Changes
Using SDL2's new features, We use SDL\_Texture in favour of SDL\_Surface.  So, instead of doing this to get an image rendered to the screen,
```c
SDL_BlitSurface(hello, NULL, screen, NULL);
SDL_Flip(screen)
```
we do this:
```c
SDL_RenderCopy(sdl_renderer, texture, NULL, NULL);
SDL_RenderPresent(sdl_renderer);
```

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
