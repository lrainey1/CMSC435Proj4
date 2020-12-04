# CMSC435Proj4
Basic implementation of Mesh Fairing, shamelessly stolen from class examples.
Compile with make, might cause issues with the eigen path since I wrote all of this on Debian.
Follows sample input format, no error checking beyond if the file opens. 
Horrible attempt at subdividing, it completely destroys the mesh. Would need to check for adjacency and update edges while also adding additional points.
