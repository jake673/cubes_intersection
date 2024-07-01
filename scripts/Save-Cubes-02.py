# python script for Blender

import bpy
import array as arr
from pathlib import Path

# create or update a line in blender
def updateLine(name1, point1, point2):
    coords=[ point1 , point2 ]
    edges=[ (0,1) ]
    faces=[]
    
    my_mesh = bpy.data.meshes.new(name1 + "-mesh")
    my_mesh.from_pydata(coords, edges, faces)
    my_mesh.update()
    
    my_obj = bpy.data.objects.get(name1)
    if not my_obj:
        my_obj = bpy.data.objects.new(name1,my_mesh)
        bpy.context.scene.collection.objects.link(my_obj)    
    else:
        old_mesh = my_obj.data
        my_obj.data = my_mesh
        bpy.data.meshes.remove(old_mesh)
    
# save the position,rotation,dimension of an object in a text file
def saveCube(file1, name1):
    cube1 = bpy.data.objects[name1];
    if cube1:
        file1.write(cube1.name + "," +
        str(cube1.matrix_world.to_translation().x) + "," +
        str(cube1.matrix_world.to_translation().y) + "," + 
        str(cube1.matrix_world.to_translation().z) + "," +
        str(cube1.matrix_world.to_euler().x) + "," + 
        str(cube1.matrix_world.to_euler().y) + "," + 
        str(cube1.matrix_world.to_euler().z) + "," +
        str(cube1.dimensions.x) + "," + 
        str(cube1.dimensions.y) + "," + 
        str(cube1.dimensions.z) + "\n"); 
         
# save the 2 cubes in the file         
path = str(Path('~').expanduser()) + "/Downloads/cubes-01.txt"
f = open(path, "w")

saveCube( f, "Cube.001" );
saveCube( f, "Cube.002" );        

f.close()

# eventually draw some lines to confirm the position of the cubes in the code
updateLine( "C2-L1", ( 3.82803,-0.0521796,0.5 ),(3.6268,-2.04203,0.5 ) );
updateLine( "C2-L2", ( 3.82803,-0.0521796,0.5 ),(-0.151668,0.350281,0.5 ) ); 
updateLine( "C2-L3", ( 3.82803,-0.0521796,-0.5 ),(3.6268,-2.04203,-0.5 ) ); 
updateLine( "C2-L4", ( 3.82803,-0.0521796,-0.5 ),(-0.151668,0.350281,-0.5 ) ); 



    
