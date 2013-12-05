# Optimized Surface Loading and SOft Stretching

This lesson was skipped.  As far as I can tell, using SDL\_Textures with
SDL\_CreateWindowAndRenderer instead of SDL\_Surfaces always produces a display
with the default bit depth of what the user is already using, and the render API
works out the differences (see here:
https://forums.libsdl.org/viewtopic.php?p=38636&sid=c3d49e47ec35f0466a3eb418bc93ddba).

I take this to mean that SDL\_CreateTexture and SDL\_CreateTextureFromSurface do
not need user input for choosing the correct bpp.  In particular, an
SDL\_Surface does not need to be coverted using SDL\_ConvertSurface before the
SDL\_Surface is passed to SDL\_CreateTextureFromSurface.
